#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n, k, t, s=0;
	vector<int> a;
	cin >> n >> k;
	
	for (int i = 0; i < n; i++) {
		cin >> t;
		a.push_back(t);
	}

	for (int i = n - 1; i >= 0; i--) {
		s += k / a[i];
		if(k%a[i] != k)
			k %= a[i];
	}

	cout << s;
}