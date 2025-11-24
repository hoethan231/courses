#include <cuda_runtime.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <inttypes.h>

static inline void die(const char *msg)
{
  fprintf(stderr, "%s\n", msg);
  std::exit(1);
}
static inline void ck(cudaError_t e, const char *what)
{
  if (e != cudaSuccess)
  {
    fprintf(stderr, "CUDA error at %s: %s\n", what, cudaGetErrorString(e));
    std::exit(2);
  }
}

__global__ void vec_add(const int *__restrict__ A, const int *__restrict__ B, int *__restrict__ C, size_t n)
{
  size_t i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i < n)
    C[i] = A[i] + B[i];
}

struct Timer
{
  cudaEvent_t s, e;
  Timer()
  {
    cudaEventCreate(&s);
    cudaEventCreate(&e);
  }
  ~Timer()
  {
    cudaEventDestroy(s);
    cudaEventDestroy(e);
  }
  float time_ms(std::function<void()> f)
  {
    cudaDeviceSynchronize();
    cudaEventRecord(s);
    f();
    cudaEventRecord(e);
    cudaEventSynchronize(e);
    float ms = 0.f;
    cudaEventElapsedTime(&ms, s, e);
    return ms;
  }
};

enum Mode
{
  PAGEABLE = 0,
  PINNED = 1,
  UVM_NOHINT = 2,
  UVM_ADVISE_ACCESSED = 3,
  UVM_ADVISE_PREFERRED = 4
};

static const char *mode_name(Mode m)
{
  switch (m)
  {
  case PAGEABLE:
    return "pageable+memcpy";
  case PINNED:
    return "pinned+memcpy";
  case UVM_NOHINT:
    return "uvm-nohint";
  case UVM_ADVISE_ACCESSED:
    return "uvm-advise-accessedby";
  case UVM_ADVISE_PREFERRED:
    return "uvm-advise-preferred";
  default:
    return "unknown";
  }
}

int main(int argc, char **argv)
{
  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s <bytes_per_array> <mode:0..4> [iters=10] [threads_per_block=256]\n", argv[0]);
    fprintf(stderr, "Modes: 0=pageable+memcpy, 1=pinned+memcpy, 2=uvm-nohint, 3=uvm-advise-accessedby, 4=uvm-advise-preferred\n");
    return 64;
  }
  size_t bytes = strtoull(argv[1], nullptr, 10);
  int mode_i = atoi(argv[2]);
  int iters = (argc >= 4) ? atoi(argv[3]) : 10;
  int block = (argc >= 5) ? atoi(argv[4]) : 256;

  if (mode_i < 0 || mode_i > 4)
    die("mode must be 0..4");
  Mode mode = static_cast<Mode>(mode_i);

  size_t n = std::max<size_t>(1, bytes / sizeof(int));
  int grid = int((n + block - 1) / block);

  int *hA = nullptr, *hB = nullptr, *hC = nullptr;
  int *dA = nullptr, *dB = nullptr, *dC = nullptr;

  Timer T;

  auto init_host = [&](int *A, int *B)
  {
    for (size_t i = 0; i < n; i++)
    {
      A[i] = int(i & 0x7ffff);
      B[i] = int((i * 7) & 0x7ffff);
    }
  };

  float best_ms = 1e30f;

  if (mode == PAGEABLE)
  {
    hA = (int *)malloc(n * sizeof(int));
    hB = (int *)malloc(n * sizeof(int));
    hC = (int *)malloc(n * sizeof(int));
    if (!hA || !hB || !hC)
      die("malloc failed");
    init_host(hA, hB);

    ck(cudaMalloc(&dA, n * sizeof(int)), "cudaMalloc dA");
    ck(cudaMalloc(&dB, n * sizeof(int)), "cudaMalloc dB");
    ck(cudaMalloc(&dC, n * sizeof(int)), "cudaMalloc dC");
  }

  // pinned
  if (mode == PINNED)
  {
    ck(cudaHostAlloc((void **)&hA, n * sizeof(int), cudaHostAllocDefault), "cudaHostAlloc hA");
    ck(cudaHostAlloc((void **)&hB, n * sizeof(int), cudaHostAllocDefault), "cudaHostAlloc hB");
    ck(cudaHostAlloc((void **)&hC, n * sizeof(int), cudaHostAllocDefault), "cudaHostAlloc hC");
    init_host(hA, hB);

    ck(cudaMalloc(&dA, n * sizeof(int)), "cudaMalloc dA");
    ck(cudaMalloc(&dB, n * sizeof(int)), "cudaMalloc dB");
    ck(cudaMalloc(&dC, n * sizeof(int)), "cudaMalloc dC");

    (void)T.time_ms([&]()
                    {
      cudaMemcpy(dA, hA, n*sizeof(int), cudaMemcpyHostToDevice);
      cudaMemcpy(dB, hB, n*sizeof(int), cudaMemcpyHostToDevice);
      vec_add<<<grid, block>>>(dA,dB,dC,n);
      cudaMemcpy(hC, dC, n*sizeof(int), cudaMemcpyDeviceToHost);
      cudaDeviceSynchronize(); });

    for (int r = 0; r < iters; r++)
    {
      float ms = T.time_ms([&]()
                           {
        cudaMemcpy(dA, hA, n*sizeof(int), cudaMemcpyHostToDevice);
        cudaMemcpy(dB, hB, n*sizeof(int), cudaMemcpyHostToDevice);
        vec_add<<<grid, block>>>(dA,dB,dC,n);
        cudaMemcpy(hC, dC, n*sizeof(int), cudaMemcpyDeviceToHost);
        cudaDeviceSynchronize(); });
      if (ms < best_ms)
        best_ms = ms;
    }
  }

  auto uvm_alloc = [&](int *&A, int *&B, int *&C)
  {
    ck(cudaMallocManaged(&A, n * sizeof(int)), "cudaMallocManaged A");
    ck(cudaMallocManaged(&B, n * sizeof(int)), "cudaMallocManaged B");
    ck(cudaMallocManaged(&C, n * sizeof(int)), "cudaMallocManaged C");
    init_host(A, B);
    std::memset(C, 0, n * sizeof(int));
  };

  // no hint UVM
  if (mode == UVM_NOHINT)
  {
    uvm_alloc(hA, hB, hC);
    for (int r = 0; r < iters; r++)
    {
      float ms = T.time_ms([&]()
                           {
        vec_add<<<grid, block>>>(hA,hB,hC,n);
        cudaDeviceSynchronize(); });
      if (ms < best_ms)
        best_ms = ms;
    }
    cudaFree(hA);
    cudaFree(hB);
    cudaFree(hC);
    hA = hB = hC = nullptr;
  }

  // UVM with accessed by
  if (mode == UVM_ADVISE_ACCESSED)
  {
    uvm_alloc(hA, hB, hC);
    int dev = 0;
    cudaGetDevice(&dev);
    cudaMemAdvise(hA, n * sizeof(int), cudaMemAdviseSetAccessedBy, dev);
    cudaMemAdvise(hB, n * sizeof(int), cudaMemAdviseSetAccessedBy, dev);
    cudaMemAdvise(hC, n * sizeof(int), cudaMemAdviseSetAccessedBy, dev);

    (void)T.time_ms([&]()
                    {
      vec_add<<<grid, block>>>(hA,hB,hC,n);
      cudaDeviceSynchronize(); });
    for (int r = 0; r < iters; r++)
    {
      float ms = T.time_ms([&]()
                           {
        vec_add<<<grid, block>>>(hA,hB,hC,n);
        cudaDeviceSynchronize(); });
      if (ms < best_ms)
        best_ms = ms;
    }
    cudaFree(hA);
    cudaFree(hB);
    cudaFree(hC);
    hA = hB = hC = nullptr;
  }

  // UVM with prefered location
  if (mode == UVM_ADVISE_PREFERRED)
  {
    uvm_alloc(hA, hB, hC);
    int dev = 0;
    cudaGetDevice(&dev);
    cudaMemAdvise(hA, n * sizeof(int), cudaMemAdviseSetPreferredLocation, dev);
    cudaMemAdvise(hB, n * sizeof(int), cudaMemAdviseSetPreferredLocation, dev);
    cudaMemAdvise(hC, n * sizeof(int), cudaMemAdviseSetPreferredLocation, dev);

    (void)T.time_ms([&]()
                    {
      vec_add<<<grid, block>>>(hA,hB,hC,n);
      cudaDeviceSynchronize(); });
    for (int r = 0; r < iters; r++)
    {
      float ms = T.time_ms([&]()
                           {
        vec_add<<<grid, block>>>(hA,hB,hC,n);
        cudaDeviceSynchronize(); });
      if (ms < best_ms)
        best_ms = ms;
    }
    cudaFree(hA);
    cudaFree(hB);
    cudaFree(hC);
    hA = hB = hC = nullptr;
  }

  // freeing memory after
  if (dA)
    cudaFree(dA);
  if (dB)
    cudaFree(dB);
  if (dC)
    cudaFree(dC);
  if (mode == PAGEABLE)
  {
    if (hA)
      free(hA);
    if (hB)
      free(hB);
    if (hC)
      free(hC);
  }
  if (mode == PINNED)
  {
    if (hA)
      cudaFreeHost(hA);
    if (hB)
      cudaFreeHost(hB);
    if (hC)
      cudaFreeHost(hC);
  }

  double gbps2x = (best_ms > 0) ? ((2.0 * double(bytes)) / ((best_ms / 1000.0)) / 1e9) : 0.0;

  printf("{\"Mode\":\"%s\",\"Bytes\":%" PRIu64 ",\"Total_ms\":%.6f,\"GBps_assumed_2x\":%.6f}\n",
         mode_name(mode), (unsigned long long)bytes, best_ms, gbps2x);
  return 0;
}
