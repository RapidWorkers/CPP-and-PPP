#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main() {
	int count;
	cin >> count;
	int aTmp, bTmp;
	string tmpStr;
	vector<string> origTxt;
	vector<int> a;
	vector<int> b;

	for (int i = 0; i < count; i++) {
		cin >> aTmp >> bTmp;
		a.push_back(aTmp);
		b.push_back(bTmp);
		cin >> tmpStr;
		origTxt.push_back(tmpStr);
	}

	for (int i = 0; i < count; i++) {
		for (int j = 0; origTxt[i][j] != '\0'; j++) {
			origTxt[i][j] = (a[i] * (origTxt[i][j]-65) + b[i]) % 26 + 65;
		}
		cout << origTxt[i] << endl;
	}
}