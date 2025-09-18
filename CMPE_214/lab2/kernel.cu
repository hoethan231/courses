#include <stdio.h>
#include <cuda.h>

__global__ void VecAdd(const float *A, const float *B, float* C, int n) {
  int id = blockIdx.x * blockDim.x + threadIdx.x;

  if (id < n) {
    C[id] = A[id] + B[id];
  }

}