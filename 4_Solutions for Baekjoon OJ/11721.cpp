#include <iostream>

using namespace std;

int main() {
	int a;
	char str[101] = {'\0'};
	cin >> str;
	for (int i = 0; str[i] != '\0'; i++) {
		cout << str[i];
		if (i % 10 == 9)
			cout << endl;
	}
}