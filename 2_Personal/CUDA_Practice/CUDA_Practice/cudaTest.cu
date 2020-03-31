#include <cuda.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
//headers for CUDA

#include <stdlib.h>
#include <stdio.h>
#define SIZE 10

//CUDA function to run parallely
__global__ void test(int *a, int *b) {
	int i = threadIdx.x;
	b[i] = a[i] + 1;
}

int main() {

	int cnt;
	cudaGetDeviceCount(&cnt);
	printf("CUDA Devices found: %d\n", cnt);
	cudaDeviceProp prop;
	for (int i = 0; i < cnt; i++) {
		cudaGetDeviceProperties(&prop, i);
		printf("Device #%d name: %s\n", i, prop.name);
	}


	int *a, *b;
	int *d_a, *d_b;

	//allocating space for a and b
	a = (int *)malloc(SIZE * sizeof(int));
	b = (int *)malloc(SIZE * sizeof(int));

	//allocating space for a and b on GPU
	cudaMalloc(&d_a, SIZE * sizeof(int));
	cudaMalloc(&d_b, SIZE * sizeof(int));

	//setting up values
	for (int i = 0; i < SIZE; ++i)
	{
		a[i] = i;
		b[i] = 0;
	}

	//copy and launch the function
	cudaMemcpy(d_a, a, SIZE * sizeof(int), cudaMemcpyHostToDevice);//copy to GPU(device) from host
	test <<< 1, SIZE >>> (d_a, d_b); // launch test function
	cudaMemcpy(b, d_b, SIZE * sizeof(int), cudaMemcpyDeviceToHost);//copy from GPU(device) to host

	for (int i = 0; i < SIZE; i++)
		printf("b[%d] = %d\n", i, b[i]);    // print the results

	free(a);    // free the host memory spaces
	free(b);    // free the host memory spaces

	cudaFree(d_a);    // free the device memory spaces 
	cudaFree(d_b);    // free the device memory spaces 
	return 0;
}