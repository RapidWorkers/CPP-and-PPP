#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int num, tmp, sum=0;
	vector<int> timeLst, result;

	cin >> num;

	for (int i = 0; i < num; i++) {
		cin >> tmp;
		timeLst.push_back(tmp);
	}
	sort(timeLst.begin(), timeLst.end());

	for (int i = 0; i < num; i++) {
		if (!i)
			result.push_back(timeLst[i]);
		else
			result.push_back(result[i - 1] + timeLst[i]);
		sum += result[i];
	}


	cout << sum;
}