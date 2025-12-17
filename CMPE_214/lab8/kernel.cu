#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#include <sys/time.h>

#define BLOCK_SIZE 256

// CPU Reduction
float reduction_cpu(float *data, int n)
{
    float sum = 0.0f;
    for (int i = 0; i < n; i++)
    {
        sum += data[i];
    }
    return sum;
}

// GPU Naive Reduction
__global__ void reduction_naive(float *input, float *output, int n)
{
    __shared__ float partialSum[2 * BLOCK_SIZE];

    unsigned int t = threadIdx.x;
    unsigned int start = 2 * blockIdx.x * blockDim.x;

    if (start + t < n)
        partialSum[t] = input[start + t];
    else
        partialSum[t] = 0.0f;

    if (start + blockDim.x + t < n)
        partialSum[blockDim.x + t] = input[start + blockDim.x + t];
    else
        partialSum[blockDim.x + t] = 0.0f;

    for (unsigned int stride = 1; stride <= blockDim.x; stride *= 2)
    {
        __syncthreads();
        if (t % stride == 0)
        {
            partialSum[2 * t] += partialSum[2 * t + stride];
        }
    }

    if (t == 0)
    {
        output[blockIdx.x] = partialSum[0];
    }
}

// GPU Optimized Thread Organization
__global__ void reduction_optimized_threads(float *input, float *output, int n)
{
    __shared__ float partialSum[2 * BLOCK_SIZE];

    unsigned int tid = threadIdx.x;
    unsigned int start = 2 * blockIdx.x * blockDim.x;

    if (start + tid < n)
        partialSum[tid] = input[start + tid];
    else
        partialSum[tid] = 0.0f;

    if (start + blockDim.x + tid < n)
        partialSum[blockDim.x + tid] = input[start + blockDim.x + tid];
    else
        partialSum[blockDim.x + tid] = 0.0f;

    for (unsigned int stride = blockDim.x; stride > 0; stride /= 2)
    {
        __syncthreads();
        if (tid < stride)
        {
            partialSum[tid] += partialSum[tid + stride];
        }
    }

    if (tid == 0)
    {
        output[blockIdx.x] = partialSum[0];
    }
}

// Loop Unrolling
__global__ void reduction_loop_unrolling(float *input, float *output, int n)
{
    __shared__ float partialSum[2 * BLOCK_SIZE];

    unsigned int tid = threadIdx.x;
    unsigned int start = 2 * blockIdx.x * blockDim.x;

    if (start + tid < n)
        partialSum[tid] = input[start + tid];
    else
        partialSum[tid] = 0.0f;

    if (start + blockDim.x + tid < n)
        partialSum[blockDim.x + tid] = input[start + blockDim.x + tid];
    else
        partialSum[blockDim.x + tid] = 0.0f;

    for (unsigned int stride = blockDim.x; stride > 32; stride /= 2)
    {
        __syncthreads();
        if (tid < stride)
        {
            partialSum[tid] += partialSum[tid + stride];
        }
    }

    // Loop unrolling
    if (tid < 32)
    {
        partialSum[tid] += partialSum[tid + 32];
        partialSum[tid] += partialSum[tid + 16];
        partialSum[tid] += partialSum[tid + 8];
        partialSum[tid] += partialSum[tid + 4];
        partialSum[tid] += partialSum[tid + 2];
        partialSum[tid] += partialSum[tid + 1];
    }

    if (tid == 0)
    {
        output[blockIdx.x] = partialSum[0];
    }
}

// Warp Shuffle Instructions
__global__ void reduction_warp_shuffle(float *input, float *output, int n)
{
    __shared__ float partialSum[2 * BLOCK_SIZE];

    unsigned int tid = threadIdx.x;
    unsigned int start = 2 * blockIdx.x * blockDim.x;

    if (start + tid < n)
        partialSum[tid] = input[start + tid];
    else
        partialSum[tid] = 0.0f;

    if (start + blockDim.x + tid < n)
        partialSum[blockDim.x + tid] = input[start + blockDim.x + tid];
    else
        partialSum[blockDim.x + tid] = 0.0f;

    for (unsigned int stride = blockDim.x; stride > 16; stride /= 2)
    {
        __syncthreads();
        if (tid < stride)
        {
            partialSum[tid] += partialSum[tid + stride];
        }
    }

    if (tid < 32)
    {
        float shuffle_sum = partialSum[tid];

        for (int offset = 16; offset > 0; offset /= 2)
        {
            shuffle_sum += __shfl_down_sync(0xffffffff, shuffle_sum, offset);
        }

        if (tid == 0)
        {
            output[blockIdx.x] = shuffle_sum;
        }
    }
}

double get_time()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
}

float final_reduction_cpu(float *partial_results, int n)
{
    float sum = 0.0f;
    for (int i = 0; i < n; i++)
    {
        sum += partial_results[i];
    }
    return sum;
}

int main(int argc, char **argv)
{
    // Array sizes to test
    int sizes[] = {1000000, 10000000, 50000000, 100000000};
    int num_sizes = 4;

    printf("Lab 8: Reduction Performance Comparison\n");
    printf("========================================\n\n");
    printf("%-15s %-15s %-15s %-15s %-15s %-15s %-15s\n",
           "Size", "CPU (ms)", "Naive (ms)", "Optimized (ms)",
           "Unrolled (ms)", "Shuffle (ms)", "Result");
    printf("----------------------------------------------------------------------------------------------------\n");

    for (int s = 0; s < num_sizes; s++)
    {
        int n = sizes[s];
        size_t bytes = n * sizeof(float);

        float *h_input = (float *)malloc(bytes);

        for (int i = 0; i < n; i++)
        {
            h_input[i] = 1.0f;
        }

        double cpu_start = get_time();
        float cpu_result = reduction_cpu(h_input, n);
        double cpu_time = get_time() - cpu_start;

        float *d_input, *d_output;
        int num_blocks = (n + (2 * BLOCK_SIZE) - 1) / (2 * BLOCK_SIZE);
        float *h_output = (float *)malloc(num_blocks * sizeof(float));

        cudaMalloc(&d_input, bytes);
        cudaMalloc(&d_output, num_blocks * sizeof(float));
        cudaMemcpy(d_input, h_input, bytes, cudaMemcpyHostToDevice);

        cudaEvent_t start, stop;
        cudaEventCreate(&start);
        cudaEventCreate(&stop);

        cudaEventRecord(start);
        reduction_naive<<<num_blocks, BLOCK_SIZE>>>(d_input, d_output, n);
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);

        float naive_time;
        cudaEventElapsedTime(&naive_time, start, stop);

        cudaMemcpy(h_output, d_output, num_blocks * sizeof(float), cudaMemcpyDeviceToHost);
        float naive_result = final_reduction_cpu(h_output, num_blocks);

        // GPU Optimized Threads
        cudaEventRecord(start);
        reduction_optimized_threads<<<num_blocks, BLOCK_SIZE>>>(d_input, d_output, n);
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);

        float optimized_time;
        cudaEventElapsedTime(&optimized_time, start, stop);

        cudaMemcpy(h_output, d_output, num_blocks * sizeof(float), cudaMemcpyDeviceToHost);
        float optimized_result = final_reduction_cpu(h_output, num_blocks);

        // GPU Loop Unrolling
        cudaEventRecord(start);
        reduction_loop_unrolling<<<num_blocks, BLOCK_SIZE>>>(d_input, d_output, n);
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);

        float unrolled_time;
        cudaEventElapsedTime(&unrolled_time, start, stop);

        cudaMemcpy(h_output, d_output, num_blocks * sizeof(float), cudaMemcpyDeviceToHost);
        float unrolled_result = final_reduction_cpu(h_output, num_blocks);

        // GPU Warp Shuffle
        cudaEventRecord(start);
        reduction_warp_shuffle<<<num_blocks, BLOCK_SIZE>>>(d_input, d_output, n);
        cudaEventRecord(stop);
        cudaEventSynchronize(stop);

        float shuffle_time;
        cudaEventElapsedTime(&shuffle_time, start, stop);

        cudaMemcpy(h_output, d_output, num_blocks * sizeof(float), cudaMemcpyDeviceToHost);
        float shuffle_result = final_reduction_cpu(h_output, num_blocks);

        // Print Results
        printf("%-15d %-15.3f %-15.3f %-15.3f %-15.3f %-15.3f %.0f\n",
               n, cpu_time, naive_time, optimized_time,
               unrolled_time, shuffle_time, cpu_result);

        // Cleanup
        cudaFree(d_input);
        cudaFree(d_output);
        free(h_input);
        free(h_output);
        cudaEventDestroy(start);
        cudaEventDestroy(stop);
    }

    printf("\n");
    printf("Performance Summary:\n");
    printf("====================\n");
    printf("1. CPU: Baseline sequential implementation\n");
    printf("2. Naive GPU: Thread divergence (t %% stride == 0)\n");
    printf("3. Optimized Threads: Consecutive active threads\n");
    printf("4. Loop Unrolling: Unrolled last warp iterations\n");
    printf("5. Warp Shuffle: Register-based communication within warps\n\n");

    return 0;
}
