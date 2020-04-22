////
////    Matrix Multiplication using CUDA
////    2018202024 ±è ¼ö Çö
////


#include <cuda_runtime.h>
#include <device_launch_parameters.h>
//essential cuda headers

#include <iostream>
#include <iomanip>

using namespace std;

__global__ void cudaMatrixMul(int* A, int* B, int* C);

int main()
{
	//width(size) of matrix
	constexpr unsigned int WIDTH = 16;

	//size of Tile
	constexpr unsigned int TILE_WIDTH = 4;

	int matA[WIDTH][WIDTH];
	int matB[WIDTH][WIDTH];
	int matC[WIDTH][WIDTH] = { 0, };

	//initialize matrix
	for (int y = 0; y < WIDTH; y++) {
		for (int x = 0; x < WIDTH; x++) {
			matA[y][x] = y * 10 + x;
			matB[y][x] = (y * 10 + x) * 100;
		}
	}
	//end of initializing

	//print matrix
	cout << "Matrix A" << endl;
	for (int y = 0; y < WIDTH; y++) {
		for (int x = 0; x < WIDTH; x++) {
			cout << setw(5) << matA[y][x] << ' ';
		}
		cout << endl;
	}

	cout << "Matrix B" << endl;
	for (int y = 0; y < WIDTH; y++) {
		for (int x = 0; x < WIDTH; x++) {
			cout << setw(5) << matB[y][x] << ' ';
		}
		cout << endl;
	}

	//allocate space for CUDA (GPU Device)
	int *matA_dev, *matB_dev, *matC_dev;
	cudaMalloc(&matA_dev, sizeof(int) * WIDTH * WIDTH);
	cudaMalloc(&matB_dev, sizeof(int) * WIDTH * WIDTH);
	cudaMalloc(&matC_dev, sizeof(int) * WIDTH * WIDTH);

	//Copy data to device
	cudaMemcpy(matA_dev, matA, sizeof(int) * WIDTH * WIDTH, cudaMemcpyHostToDevice);
	cudaMemcpy(matB_dev, matB, sizeof(int) * WIDTH * WIDTH, cudaMemcpyHostToDevice);

	//launch kernel function
	dim3 tileConf{ WIDTH / TILE_WIDTH, WIDTH / TILE_WIDTH };//block configuratio
	dim3 threadConf{ TILE_WIDTH, TILE_WIDTH };//thread configuration inside block
	cudaMatrixMul << < tileConf, threadConf >> > (matA_dev, matB_dev, matC_dev);

	//Synchronize Device
	cudaDeviceSynchronize();

	//Gather data from device
	cudaMemcpy(matC, matC_dev, sizeof(int) * WIDTH * WIDTH, cudaMemcpyDeviceToHost);

	//print result
	cout << "\nMultiplication Result" << endl;
	for (int y = 0; y < WIDTH; y++) {
		for (int x = 0; x < WIDTH; x++) {
			cout << setw(8) << matC[y][x] << ' ';
		}
		cout << endl;
	}

	//deallocate CUDA(GPU Deivce) space
	cudaFree(matA_dev);
	cudaFree(matB_dev);
	cudaFree(matC_dev);

	return 0;
}

/*
	@name cudaMatrixMul
	@brief matrix parallel multiplication function for square matrix
	@params int *A Matrix A
	@params int *B Matrix B
	@params int *c Result Matrix
*/
__global__ void cudaMatrixMul(int* A, int* B, int* C)
{
	//OK, we need current multiplication target
	//Calculate using CUDA builtin index

	//local thread index
	int x = threadIdx.x;
	int y = threadIdx.y;

	//block index
	int b_x = blockIdx.x;
	int b_y = blockIdx.y;

	//global index
	int gx = b_x * blockDim.x + x;
	int gy = b_y * blockDim.y + y;

	//reset memory
	C[gy * blockDim.y * gridDim.y + gx] = 0;

	//do multiplication
	for (int k = 0; k < blockDim.x * gridDim.x; k++) {//iterate for width of matrix
		int mulR = (gy * blockDim.x * gridDim.x) + k; // = [y][k]
		int mulC = (k * blockDim.x * gridDim.x) + gx; // = [k][x]

		C[gy * blockDim.y * gridDim.y + gx] += A[mulR] * B[mulC];//accumulate result
	}

}