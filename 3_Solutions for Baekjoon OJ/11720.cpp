#include <iostream>
#include <string>

using namespace std;

int main() {
	string num;
	int count, sum = 0;

	cin >> count >> num;

	for (int i = 0; i < count; i++)
	{
		sum += num[i] - '0';
	}

	cout << sum;
}