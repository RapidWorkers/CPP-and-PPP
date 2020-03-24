#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

using namespace std;

int main(int argc, char* argv[])
{
	char mgHead[] = { 0x42, 0x4D, 0x36, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0xC4, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	
	vector<vector<int>> edgeFilter = { vector<int>{1,0,-1}, vector<int>{0,0,0}, vector<int>{-1,0,1} };
	vector<vector<float>> boxBlur = { vector<float>{0.1111111111,0.1111111111,0.1111111111}, vector<float>{0.1111111111,0.1111111111,0.1111111111}, vector<float>{0.1111111111,0.1111111111,0.1111111111} };

	ifstream inBMP{ "./Lenna.bmp" , ios::binary};
	ofstream out1{ "./Edge.bmp", ios::binary};
	ofstream out2("./Boxblur.bmp", ios::binary);

	//write bmp head
	out1.write(mgHead, 54);
	out2.write(mgHead, 54);

	vector<unsigned char> R, G, B;

	//read width, height
	inBMP.seekg(18, ios::beg);
	
	int width, height;
	inBMP.read((char*)&width, 4);
	inBMP.read((char*)&height, 4);

	//skip header
	inBMP.seekg(54, ios::beg);

	char BGR_buf[3];
	while (true) {
		if (inBMP.eof()) break;
		inBMP.read(BGR_buf, 3);
		B.push_back(BGR_buf[0]);
		G.push_back(BGR_buf[1]);
		R.push_back(BGR_buf[2]);
	}

	//add padding and convert to matrix
	vector<vector<unsigned char>> R_mat;
	vector<vector<unsigned char>> G_mat;
	vector<vector<unsigned char>> B_mat;
	R_mat.push_back(vector<unsigned char>(width + 2));
	G_mat.push_back(vector<unsigned char>(width + 2));
	B_mat.push_back(vector<unsigned char>(width + 2));

	for (int i = 0; i < height; i++) {
		vector<unsigned char>R_line_tmp;
		vector<unsigned char>G_line_tmp;
		vector<unsigned char>B_line_tmp;
		R_line_tmp.push_back(0);
		G_line_tmp.push_back(0);
		B_line_tmp.push_back(0);
		for (int j = 0; j < width; j++) {
			R_line_tmp.push_back(R[i*width + j]);
			G_line_tmp.push_back(G[i*width + j]);
			B_line_tmp.push_back(B[i*width + j]);
		}
		R_line_tmp.push_back(0);
		G_line_tmp.push_back(0);
		B_line_tmp.push_back(0);
		R_mat.push_back(R_line_tmp);
		G_mat.push_back(G_line_tmp);
		B_mat.push_back(B_line_tmp);
	}

	R_mat.push_back(vector<unsigned char>(width + 2));
	G_mat.push_back(vector<unsigned char>(width + 2));
	B_mat.push_back(vector<unsigned char>(width + 2));
	
	vector<unsigned char> newR, newG, newB;

	//apply convolution filter
	for (int i = 0; i < height; i++) {
		int convRes = 0;
		for (int j = 0; j < width; j++) {
			convRes = R_mat[i + 0][j + 0] * edgeFilter[0][0] + R_mat[i + 0][j + 1] * edgeFilter[0][1] + R_mat[i + 0][j + 2] * edgeFilter[0][2];
			convRes += R_mat[i + 1][j + 0] * edgeFilter[1][0] + R_mat[i + 1][j + 1] * edgeFilter[1][1] + R_mat[i + 1][j + 2] * edgeFilter[1][2];
			convRes += R_mat[i + 2][j + 0] * edgeFilter[2][0] + R_mat[i + 2][j + 1] * edgeFilter[2][1] + R_mat[i + 2][j + 2] * edgeFilter[2][2];
			newR.push_back(convRes);
			convRes = G_mat[i + 0][j + 0] * edgeFilter[0][0] + G_mat[i + 0][j + 1] * edgeFilter[0][1] + G_mat[i + 0][j + 2] * edgeFilter[0][2];
			convRes += G_mat[i + 1][j + 0] * edgeFilter[1][0] + G_mat[i + 1][j + 1] * edgeFilter[1][1] + G_mat[i + 1][j + 2] * edgeFilter[1][2];
			convRes += G_mat[i + 2][j + 0] * edgeFilter[2][0] + G_mat[i + 2][j + 1] * edgeFilter[2][1] + G_mat[i + 2][j + 2] * edgeFilter[2][2];
			newG.push_back(convRes);
			convRes = B_mat[i + 0][j + 0] * edgeFilter[0][0] + B_mat[i + 0][j + 1] * edgeFilter[0][1] + B_mat[i + 0][j + 2] * edgeFilter[0][2];
			convRes += B_mat[i + 1][j + 0] * edgeFilter[1][0] + B_mat[i + 1][j + 1] * edgeFilter[1][1] + B_mat[i + 1][j + 2] * edgeFilter[1][2];
			convRes += B_mat[i + 2][j + 0] * edgeFilter[2][0] + B_mat[i + 2][j + 1] * edgeFilter[2][1] + B_mat[i + 2][j + 2] * edgeFilter[2][2];
			newB.push_back(convRes);
		}
	}

	for (int i = 0; i < height*width; i++) {
		out1.put(newB[i]);
		out1.put(newG[i]);
		out1.put(newR[i]);
	}

	newR.clear();
	newG.clear();
	newB.clear();

	//apply convolution filter
	for (int i = 0; i < height; i++) {
		int convRes = 0;
		for (int j = 0; j < width; j++) {
			convRes = R_mat[i + 0][j + 0] * boxBlur[0][0] + R_mat[i + 0][j + 1] * boxBlur[0][1] + R_mat[i + 0][j + 2] * boxBlur[0][2];
			convRes += R_mat[i + 1][j + 0] * boxBlur[1][0] + R_mat[i + 1][j + 1] * boxBlur[1][1] + R_mat[i + 1][j + 2] * boxBlur[1][2];
			convRes += R_mat[i + 2][j + 0] * boxBlur[2][0] + R_mat[i + 2][j + 1] * boxBlur[2][1] + R_mat[i + 2][j + 2] * boxBlur[2][2];
			newR.push_back(convRes);
			convRes = G_mat[i + 0][j + 0] * boxBlur[0][0] + G_mat[i + 0][j + 1] * boxBlur[0][1] + G_mat[i + 0][j + 2] * boxBlur[0][2];
			convRes += G_mat[i + 1][j + 0] * boxBlur[1][0] + G_mat[i + 1][j + 1] * boxBlur[1][1] + G_mat[i + 1][j + 2] * boxBlur[1][2];
			convRes += G_mat[i + 2][j + 0] * boxBlur[2][0] + G_mat[i + 2][j + 1] * boxBlur[2][1] + G_mat[i + 2][j + 2] * boxBlur[2][2];
			newG.push_back(convRes);
			convRes = B_mat[i + 0][j + 0] * boxBlur[0][0] + B_mat[i + 0][j + 1] * boxBlur[0][1] + B_mat[i + 0][j + 2] * boxBlur[0][2];
			convRes += B_mat[i + 1][j + 0] * boxBlur[1][0] + B_mat[i + 1][j + 1] * boxBlur[1][1] + B_mat[i + 1][j + 2] * boxBlur[1][2];
			convRes += B_mat[i + 2][j + 0] * boxBlur[2][0] + B_mat[i + 2][j + 1] * boxBlur[2][1] + B_mat[i + 2][j + 2] * boxBlur[2][2];
			newB.push_back(convRes);
		}
	}

	for (int i = 0; i < height*width; i++) {
		out2.put(newB[i]);
		out2.put(newG[i]);
		out2.put(newR[i]);
	}

	out1.flush();
	out2.flush();

	return 0;
}
