#pragma once

#include <vector>

using namespace std;

class ConvFilter {
private:
	vector<vector<int>> edgeFilter = { vector<int>{1,0,-1}, vector<int>{0,0,0}, vector<int>{-1,0,1} };
	void matMul();
public:
};