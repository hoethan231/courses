#include <cuda_runtime.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void die(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

static void ck(cudaError_t e, const char *where)
{
    if (e != cudaSuccess)
    {
        fprintf(stderr, "CUDA error at %s: %s\n", where, cudaGetErrorString(e));
        exit(1);
    }
}

static void fill_matrix(int *m, int N)
{
    for (int i = 0; i < N * N; ++i)
    {
        m[i] = (rand() % 10) + 1;
    }
}

// naive CPU
static void matmul_cpu_naive(const int *A, const int *B, int *C, int N)
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            long long sum = 0;
            for (int k = 0; k < N; ++k)
            {
                sum += (long long)A[i * N + k] * (long long)B[k * N + j];
            }
            C[i * N + j] = (int)sum;
        }
    }
}

// optimized CPU
static void matmul_cpu_opt(const int *A, const int *B, int *C, int N)
{
    for (int i = 0; i < N * N; ++i)
        C[i] = 0;

    for (int i = 0; i < N; ++i)
    {
        for (int k = 0; k < N; ++k)
        {
            int a_ik = A[i * N + k];
            for (int j = 0; j < N; ++j)
            {
                C[i * N + j] += a_ik * B[k * N + j];
            }
        }
    }
}


// naive GPU kernel
__global__ void matmul_naive_gpu(const int *A, const int *B, int *C, int N)
{
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < N && col < N)
    {
        long long sum = 0;
        for (int k = 0; k < N; ++k)
        {
            sum += (long long)A[row * N + k] * (long long)B[k * N + col];
        }
        C[row * N + col] = (int)sum;
    }
}

// tiled GPU kernel using shared memory
__global__ void matmul_tiled_gpu(const int *A, const int *B, int *C, int N, int tile)
{
    extern __shared__ int sh[];
    int *As = sh;
    int *Bs = sh + tile * tile;

    int tx = threadIdx.x;
    int ty = threadIdx.y;

    int row = blockIdx.y * tile + ty;
    int col = blockIdx.x * tile + tx;

    long long sum = 0;

    int numTiles = (N + tile - 1) / tile;

    for (int t = 0; t < numTiles; ++t)
    {
        int Acol = t * tile + tx;
        int Brow = t * tile + ty;

        if (row < N && Acol < N)
        {
            As[ty * tile + tx] = A[row * N + Acol];
        }
        else
        {
            As[ty * tile + tx] = 0;
        }

        if (Brow < N && col < N)
        {
            Bs[ty * tile + tx] = B[Brow * N + col];
        }
        else
        {
            Bs[ty * tile + tx] = 0;
        }

        __syncthreads();

        for (int k = 0; k < tile; ++k)
        {
            sum += (long long)As[ty * tile + k] * (long long)Bs[k * tile + tx];
        }

        __syncthreads();
    }

    if (row < N && col < N)
    {
        C[row * N + col] = (int)sum;
    }
}

static double cpu_time_ms(void (*f)(const int *, const int *, int *, int),
                          const int *A, const int *B, int *C, int N)
{
    clock_t start = clock();
    f(A, B, C, N);
    clock_t end = clock();
    double sec = (double)(end - start) / CLOCKS_PER_SEC;
    return sec * 1000.0;
}

static double gpu_time_ms_naive(const int *A_h, const int *B_h, int *C_h,
                                int *C_ref, int N, int tile, int iters, int *out_ok)
{
    size_t bytes = (size_t)N * N * sizeof(int);
    int *A_d = NULL, *B_d = NULL, *C_d = NULL;

    ck(cudaMalloc(&A_d, bytes), "cudaMalloc A_d");
    ck(cudaMalloc(&B_d, bytes), "cudaMalloc B_d");
    ck(cudaMalloc(&C_d, bytes), "cudaMalloc C_d");

    ck(cudaMemcpy(A_d, A_h, bytes, cudaMemcpyHostToDevice), "H2D A");
    ck(cudaMemcpy(B_d, B_h, bytes, cudaMemcpyHostToDevice), "H2D B");

    dim3 block(tile, tile);
    dim3 grid((N + tile - 1) / tile, (N + tile - 1) / tile);

    matmul_naive_gpu<<<grid, block>>>(A_d, B_d, C_d, N);
    ck(cudaDeviceSynchronize(), "warmup sync");

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    float best = 1e30f;
    for (int r = 0; r < iters; ++r)
    {
        cudaEventRecord(start);
        matmul_naive_gpu<<<grid, block>>>(A_d, B_d, C_d, N);
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        float ms = 0.0f;
        cudaEventElapsedTime(&ms, start, stop);
        if (ms < best)
            best = ms;
    }

    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    ck(cudaMemcpy(C_h, C_d, bytes, cudaMemcpyDeviceToHost), "D2H C");

    int ok = 1;
    for (int i = 0; i < N * N; ++i)
    {
        if (C_h[i] != C_ref[i])
        {
            ok = 0;
            break;
        }
    }
    *out_ok = ok;

    cudaFree(C_d);
    cudaFree(B_d);
    cudaFree(A_d);

    return (double)best;
}

static double gpu_time_ms_tiled(const int *A_h, const int *B_h, int *C_h,
                                int *C_ref, int N, int tile, int iters, int *out_ok)
{
    size_t bytes = (size_t)N * N * sizeof(int);
    int *A_d = NULL, *B_d = NULL, *C_d = NULL;

    ck(cudaMalloc(&A_d, bytes), "cudaMalloc A_d");
    ck(cudaMalloc(&B_d, bytes), "cudaMalloc B_d");
    ck(cudaMalloc(&C_d, bytes), "cudaMalloc C_d");

    ck(cudaMemcpy(A_d, A_h, bytes, cudaMemcpyHostToDevice), "H2D A");
    ck(cudaMemcpy(B_d, B_h, bytes, cudaMemcpyHostToDevice), "H2D B");

    dim3 block(tile, tile);
    dim3 grid((N + tile - 1) / tile, (N + tile - 1) / tile);
    size_t shBytes = 2 * (size_t)tile * tile * sizeof(int);

    matmul_tiled_gpu<<<grid, block, shBytes>>>(A_d, B_d, C_d, N, tile);
    ck(cudaDeviceSynchronize(), "warmup sync");

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    float best = 1e30f;
    for (int r = 0; r < iters; ++r)
    {
        cudaEventRecord(start);
        matmul_tiled_gpu<<<grid, block, shBytes>>>(A_d, B_d, C_d, N, tile);
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);
        float ms = 0.0f;
        cudaEventElapsedTime(&ms, start, stop);
        if (ms < best)
            best = ms;
    }

    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    ck(cudaMemcpy(C_h, C_d, bytes, cudaMemcpyDeviceToHost), "D2H C");

    int ok = 1;
    for (int i = 0; i < N * N; ++i)
    {
        if (C_h[i] != C_ref[i])
        {
            ok = 0;
            break;
        }
    }
    *out_ok = ok;

    cudaFree(C_d);
    cudaFree(B_d);
    cudaFree(A_d);

    return (double)best;
}

int main(int argc, char **argv)
{
    if (argc < 5)
    {
        fprintf(stderr, "Usage: %s <N> <mode> <tile> <iters>\n", argv[0]);
        fprintf(stderr, "  N: matrix size (N x N), preferably power of 2\n");
        fprintf(stderr, "  mode: 0=cpu-naive, 1=cpu-opt, 2=gpu-naive, 3=gpu-tiled\n");
        fprintf(stderr, "  tile: tile size (for GPU blockDim.x = blockDim.y = tile)\n");
        fprintf(stderr, "  iters: number of timing iterations\n");
        return 1;
    }

    int N = atoi(argv[1]);
    int mode = atoi(argv[2]);
    int tile = atoi(argv[3]);
    int iters = atoi(argv[4]);

    if (N <= 0)
        die("N must be positive");
    if (mode < 0 || mode > 3)
        die("mode must be 0,1,2,or 3");
    if (tile <= 0)
        die("tile must be positive");
    if (tile * tile > 1024)
        die("tile*tile must be <= 1024 (max threads per block)");
    if (iters <= 0)
        die("iters must be positive");

    srand(0);

    size_t bytes = (size_t)N * N * sizeof(int);
    int *A = (int *)malloc(bytes);
    int *B = (int *)malloc(bytes);
    int *C = (int *)malloc(bytes);
    int *Cref = (int *)malloc(bytes);
    if (!A || !B || !C || !Cref)
        die("malloc failed");

    fill_matrix(A, N);
    fill_matrix(B, N);

    const char *mode_name = NULL;
    double ms = 0.0;
    int ok = 1;

    if (mode == 0)
    {
        mode_name = "cpu-naive";
        ms = cpu_time_ms(matmul_cpu_naive, A, B, C, N);
        ok = 1;
    }
    else if (mode == 1)
    {
        mode_name = "cpu-opt";
        ms = cpu_time_ms(matmul_cpu_opt, A, B, C, N);
        ok = 1;
    }
    else if (mode == 2)
    {
        mode_name = "gpu-naive";
        matmul_cpu_opt(A, B, Cref, N);
        ms = gpu_time_ms_naive(A, B, C, Cref, N, tile, iters, &ok);
    }
    else if (mode == 3)
    {
        mode_name = "gpu-tiled";
        matmul_cpu_opt(A, B, Cref, N);
        ms = gpu_time_ms_tiled(A, B, C, Cref, N, tile, iters, &ok);
    }

    printf("{\"Mode\":\"%s\",\"N\":%d,\"Tile\":%d,\"Ms\":%.6f,\"OK\":%s}\n",
           mode_name, N, tile, ms, ok ? "true" : "false");

    free(Cref);
    free(C);
    free(B);
    free(A);

    return 0;
}
