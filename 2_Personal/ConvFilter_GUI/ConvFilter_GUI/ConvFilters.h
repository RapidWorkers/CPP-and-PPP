#pragma once

#include <vector>

using namespace std;

enum ConvFilters{FILT_BOX_BLUR, FILT_GAU_BLUR, FILT_EDGE_LIGHT, FILT_EDGE_MEDIUM, FILT_EDGE_HEAVY};

class Filtering {

	vector<vector<float>> edgeLight = { {1, 0, -1}, {0, 0, 0}, {-1, 0, 1} };
	vector<vector<float>> edgeMedium = { {0, 1, 0}, {1, -4, 1},{0, 1, 0 }};
	vector<vector<float>> edgeHeavy = { {-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1} };
	vector<vector<float>> boxBlur = { {0.111111111111, 0.111111111111, 0.111111111111}, {0.111111111111, 0.111111111111, 0.111111111111}, {0.111111111111, 0.111111111111, 0.111111111111} };
	vector<vector<float>> gauBlur = { {1.0 / 16, 1.0 / 8, 1.0 / 16}, {1.0 / 8, 1.0 / 4, 1.0 / 8}, {1.0 / 16, 1.0 / 8, 1.0 / 16} };

public:
	void maxPool2x2(const vector<unsigned char> &targetMatrix, vector<unsigned char> &resultMatrix, int width, int height, int &neww, int &newh) {
		neww = width / 2;
		newh = height / 2;

		for(int i = 0; i < height; i+=2)
			for (int j = 0; j < width; j+=2) {
				int max = targetMatrix[(i + 0)*width + (j + 0)];
				max = (max < targetMatrix[(i + 0)*width + (j + 1)]) ? targetMatrix[(i + 0)*width + (j + 1)] : max;
				max = (max < targetMatrix[(i + 1)*width + (j + 0)]) ? targetMatrix[(i + 1)*width + (j + 0)] : max;
				max = (max < targetMatrix[(i + 1)*width + (j + 1)]) ? targetMatrix[(i + 1)*width + (j + 1)] : max;
				resultMatrix.push_back(max);
			}
	}

	void apply(const vector<unsigned char> &targetMatrix, vector<unsigned char> &resultMatrix, int width, int height, ConvFilters filterType) {

		vector<unsigned char> paddedMat;
		for (int i = 0; i < width + 2; i++)
			paddedMat.push_back(0);
		for (int i = 0; i < height; i++) {
			paddedMat.push_back(0);
			for (int j = 0; j < width; j++) paddedMat.push_back(targetMatrix[i*width + j]);
			paddedMat.push_back(0);
		}
		for (int i = 0; i < width + 2; i++)
			paddedMat.push_back(0);

		//clean result matrix
		resultMatrix.clear();

		//select filter
		vector<vector<float>> selectedFilter;

		switch (filterType) {
		case FILT_BOX_BLUR:
			selectedFilter = boxBlur;
			break;
		case FILT_GAU_BLUR:
			selectedFilter = gauBlur;
			break;
		case FILT_EDGE_LIGHT:
			selectedFilter = edgeLight;
			break;
		case FILT_EDGE_MEDIUM:
			selectedFilter = edgeMedium;
			break;
		case FILT_EDGE_HEAVY:
			selectedFilter = edgeHeavy;
			break;
		default:
			selectedFilter = boxBlur;
		}

		//apply convolution filter
		for (int i = 0; i < width; i++) {
			int convRes = 0;
			for (int j = 0; j < height; j++) {
				convRes =  paddedMat[(i + 0)*(width + 2) + (j + 0)] * selectedFilter[2][2] + paddedMat[(i + 0)*(width + 2) + (j + 1)] * selectedFilter[2][1] + paddedMat[(i + 0)*(width + 2) + (j + 2)] * selectedFilter[2][0];
				convRes += paddedMat[(i + 1)*(width + 2) + (j + 0)] * selectedFilter[1][2] + paddedMat[(i + 1)*(width + 2) + (j + 1)] * selectedFilter[1][1] + paddedMat[(i + 1)*(width + 2) + (j + 2)] * selectedFilter[1][0];
				convRes += paddedMat[(i + 2)*(width + 2) + (j + 0)] * selectedFilter[0][2] + paddedMat[(i + 2)*(width + 2) + (j + 1)] * selectedFilter[0][1] + paddedMat[(i + 2)*(width + 2) + (j + 2)] * selectedFilter[0][0];
				resultMatrix.push_back(convRes);
			}
		}

	//done

	}
private:

};