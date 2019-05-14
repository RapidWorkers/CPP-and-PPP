#include "std_lib_facilities.h"

int main() {
	int a = 20000;
	char c = a;
	int b = c;

	if (a != b)
		cout << "Oops!: " << a << "!=" << b << "\n";

	keep_window_open();
	return 0;
}