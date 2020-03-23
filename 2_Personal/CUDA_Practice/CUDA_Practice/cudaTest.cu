#include <cuda_runtime.h>

__global__ void MatrixMul(float *M, float *N, float *P, int width)
{
	int size = width * width*width;
	float *Md, *Nd, *Pd;

	cudaMalloc((void**)Md, size);
	cudaMemcpy(Md, M, size, cudaMemcpyHostToDevice);
	cudaMalloc((void**)Nd, size);
	cudaMemcpy(Nd, N, size, cudaMemcpyHostToDevice);


	cudaMalloc((void**)Pd, size);


}