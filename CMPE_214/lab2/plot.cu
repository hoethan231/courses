#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cuda_runtime.h>

__global__ void VecAdd(const float *A, const float *B, float *C, int n)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id < n)
        C[id] = A[id] + B[id];
}

int main(int argc, char **argv)
{ // Args: N blocks tpb iters
    if (argc < 5)
    {
        fprintf(stderr, "Usage: %s N blocks tpb iters\n", argv[0]);
        return 2;
    }
    const int N = atoi(argv[1]);
    const int blocks = atoi(argv[2]);
    const int tpb = atoi(argv[3]);
    const int iters = atoi(argv[4]);

    std::vector<float> hA(N), hB(N), hC(N);
    for (int i = 0; i < N; ++i)
    {
        hA[i] = float(i);
        hB[i] = float(i);
    }

    float *dA = nullptr, *dB = nullptr, *dC = nullptr;
    size_t bytes = size_t(N) * sizeof(float);
    cudaMalloc(&dA, bytes);
    cudaMalloc(&dB, bytes);
    cudaMalloc(&dC, bytes);

    cudaEvent_t sT, eT;
    cudaEventCreate(&sT);
    cudaEventCreate(&eT);

    double T_ms = 0;

    for (int r = 0; r < iters; ++r)
    {
        cudaMemcpy(dA, hA.data(), bytes, cudaMemcpyHostToDevice);
        cudaMemcpy(dB, hB.data(), bytes, cudaMemcpyHostToDevice);

        cudaEventRecord(sT);
        VecAdd<<<blocks, tpb>>>(dA, dB, dC, N);
        cudaEventRecord(eT);

        cudaMemcpy(hC.data(), dC, bytes, cudaMemcpyDeviceToHost);

        cudaEventSynchronize(eT);

        float tt = 0;
        cudaEventElapsedTime(&tt, sT, eT);
        T_ms += tt;
    }

    T_ms /= iters;

    printf("{\"N\":%d,\"blocks\":%d,\"tpb\":%d,\"Kernal_ms\":%.6f}\n",
           N, blocks, tpb, T_ms);

    cudaFree(dA);
    cudaFree(dB);
    cudaFree(dC);
    cudaEventDestroy(sT);
    cudaEventDestroy(eT);
    return 0;
}
