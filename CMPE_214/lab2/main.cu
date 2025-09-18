#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include "kernel.cu"

int main (int argc, char *argv[]){

    float *A_h, *B_h, *C_h;
    float *A_d, *B_d, *C_d;    
    unsigned VecSize;
   
    if (argc == 1) {
        VecSize = 256;
    } else if (argc == 2) {
      VecSize = atoi(argv[1]);
    } else {
        printf("Usage: ./vecAdd <Size>");
        exit(0);
    }
	
    A_h = (float*) malloc( sizeof(float) * VecSize );
	  B_h = (float*) malloc( sizeof(float) * VecSize );
	  C_h = (float*) malloc( sizeof(float) * VecSize );
	
    for (unsigned int i=0; i < VecSize; i++) {
      A_h[i] = i;
      B_h[i] = i;
    }

    cudaDeviceSynchronize();

    //INSERT Memory CODE HERE
    int size = VecSize*sizeof(float);
    float *d_A, *d_B, *d_C;

    cudaMalloc((void **) &d_A, size);
    cudaMalloc((void **) &d_B, size);
    cudaMalloc((void **) &d_C, size);
    cudaMemcpy(d_A, A_h, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, B_h, size, cudaMemcpyHostToDevice);

    int blockSize = 1024;
    int gridSize = (int)ceil((float)VecSize/blockSize);

    cudaDeviceSynchronize();

    //INSERT kernel launch CODE HERE
    VecAdd<<<gridSize, blockSize>>>(d_A, d_B, d_C, VecSize);

    cudaDeviceSynchronize();

    //INSERT Memory CODE HERE
    cudaMemcpy(C_h, d_C, size, cudaMemcpyDeviceToHost);
    for(int i=0; i<VecSize; i++) {
      printf(" %f",C_h[i]);
    }

    cudaDeviceSynchronize();

    free(A_h);
    free(B_h);
    free(C_h);
    cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);

    return 0;
}
