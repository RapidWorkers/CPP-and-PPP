#include <iostream>

using namespace std;

int main() {
	int num, a, b;
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	cin >> num;

	int* c = new int[num];

	for (int i = 0; i < num; i++) {
		cin >> a >> b;
		c[i] = a + b;
	}
	for (int i = 0; i < num; i++)
		cout << c[i] << '\n';
}