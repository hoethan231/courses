#include <cuda_runtime.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <inttypes.h>

static inline void ck(cudaError_t e, const char *where)
{
    if (e != cudaSuccess)
    {
        fprintf(stderr, "CUDA error @ %s: %s\n", where, cudaGetErrorString(e));
        std::exit(1);
    }
}

// Serial CPU
long long cpu_reduce(const int *a, size_t n)
{
    long long s = 0;
    for (size_t i = 0; i < n; i++)
        s += a[i];
    return s;
}

// Kernels
template <int BLOCK>
__global__ void reduce_naive(const int *__restrict__ in, long long *__restrict__ block_sums, size_t n)
{
    __shared__ long long smem[2 * BLOCK];
    const unsigned int t = threadIdx.x;
    const unsigned int start = 2 * blockIdx.x * blockDim.x;
    unsigned int i0 = start + t;
    unsigned int i1 = start + BLOCK + t;

    long long v0 = (i0 < n) ? (long long)in[i0] : 0LL;
    long long v1 = (i1 < n) ? (long long)in[i1] : 0LL;
    smem[t] = v0;
    smem[BLOCK + t] = v1;

    // naive solution
    for (unsigned int stride = 1; stride <= BLOCK; stride <<= 1)
    {
        __syncthreads();
        if ((t % stride) == 0)
        {
            unsigned int idx = 2 * t;
            if (idx + stride < 2 * BLOCK)
                smem[idx] += smem[idx + stride];
        }
    }
    __syncthreads();
    if (t == 0)
        block_sums[blockIdx.x] = smem[0];
}

template <int BLOCK>
__global__ void reduce_optimized(const int *__restrict__ in, long long *__restrict__ block_sums, size_t n)
{
    __shared__ long long s[BLOCK];
    const unsigned int t = threadIdx.x;
    unsigned int i = blockIdx.x * blockDim.x * 2 + t;
    long long sum = 0;
    if (i < n)
        sum += in[i];
    if (i + BLOCK < n)
        sum += in[i + BLOCK];
    s[t] = sum;
    __syncthreads();

    // optimized version
    for (unsigned int stride = BLOCK / 2; stride > 0; stride >>= 1)
    {
        if (t < stride)
            s[t] += s[t + stride];
        __syncthreads();
    }
    if (t == 0)
        block_sums[blockIdx.x] = s[0];
}

// timings
struct Timer
{
    cudaEvent_t a, b;
    Timer()
    {
        cudaEventCreate(&a);
        cudaEventCreate(&b);
    }
    ~Timer()
    {
        cudaEventDestroy(a);
        cudaEventDestroy(b);
    }
    float run_ms(std::function<void()> f)
    {
        cudaDeviceSynchronize();
        cudaEventRecord(a);
        f();
        cudaEventRecord(b);
        cudaEventSynchronize(b);
        float ms = 0;
        cudaEventElapsedTime(&ms, a, b);
        return ms;
    }
};

static void init_data(std::vector<int> &h)
{
    for (size_t i = 0; i < h.size(); ++i)
        h[i] = int(i & 0xFFFF);
}

int main(int argc, char **argv)
{
    if (argc < 6)
    {
        fprintf(stderr, "Usage: %s <N> <mode:0=CPU,1=GPU-naive,2=GPU-opt> <blocks> <threads> <iters>\n", argv[0]);
        return 64;
    }
    size_t N = strtoull(argv[1], nullptr, 10);
    int mode = atoi(argv[2]);
    int blocks = atoi(argv[3]);
    int threads = atoi(argv[4]);
    int iters = atoi(argv[5]);

    std::vector<int> h(N);
    init_data(h);
    long long gold = cpu_reduce(h.data(), N);

    int *d_in = nullptr;
    long long *d_part = nullptr;
    ck(cudaMalloc(&d_in, N * sizeof(int)), "cudaMalloc d_in");
    ck(cudaMemcpy(d_in, h.data(), N * sizeof(int), cudaMemcpyHostToDevice), "H2D");
    ck(cudaMalloc(&d_part, blocks * sizeof(long long)), "cudaMalloc d_part");

    auto launch_and_time = [&](auto KERNEL)
    {
        Timer T;
        KERNEL<<<blocks, threads>>>(d_in, d_part, N);
        ck(cudaDeviceSynchronize(), "warmup sync");

        float best = 1e30f;
        for (int r = 0; r < iters; r++)
        {
            float ms = T.run_ms([&]()
                                {
        KERNEL<<<blocks, threads>>>(d_in, d_part, N);
        cudaDeviceSynchronize(); });
            if (ms < best)
                best = ms;
        }
        std::vector<long long> part(blocks);
        ck(cudaMemcpy(part.data(), d_part, blocks * sizeof(long long), cudaMemcpyDeviceToHost), "D2H");
        long long total = 0;
        for (int b = 0; b < blocks; b++)
            total += part[b];

        bool ok = (total == gold);
        printf("{\"Mode\":\"%s\",\"N\":%llu,\"Blocks\":%d,\"TPB\":%d,\"Best_ms\":%.6f,\"OK\":%s}\n",
               (mode == 0 ? "cpu-serial" : mode == 1 ? "gpu-naive"
                                                     : "gpu-optimized"),
               (unsigned long long)N, blocks, threads, best, ok ? "true" : "false");
    };

    if (mode == 0)
    {
        Timer T;
        float ms = T.run_ms([&]()
                            { volatile long long s = cpu_reduce(h.data(), N); (void)s; });
        printf("{\"Mode\":\"cpu-serial\",\"N\":%llu,\"Blocks\":1,\"TPB\":1,\"Best_ms\":%.6f,\"OK\":true}\n",
               (unsigned long long)N, ms);
    }
    else
    {
        switch (threads)
        {
        case 32:
            (mode == 1 ? launch_and_time(reduce_naive<32>) : launch_and_time(reduce_optimized<32>));
            break;
        case 64:
            (mode == 1 ? launch_and_time(reduce_naive<64>) : launch_and_time(reduce_optimized<64>));
            break;
        case 128:
            (mode == 1 ? launch_and_time(reduce_naive<128>) : launch_and_time(reduce_optimized<128>));
            break;
        case 256:
            (mode == 1 ? launch_and_time(reduce_naive<256>) : launch_and_time(reduce_optimized<256>));
            break;
        case 512:
            (mode == 1 ? launch_and_time(reduce_naive<512>) : launch_and_time(reduce_optimized<512>));
            break;
        case 1024:
            (mode == 1 ? launch_and_time(reduce_naive<1024>) : launch_and_time(reduce_optimized<1024>));
            break;
        default:
            fprintf(stderr, "TPB must be one of {32,64,128,256,512,1024}\n");
            break;
        }
    }

    cudaFree(d_part);
    cudaFree(d_in);
    return 0;
}
