#include "std_lib_facilities.h"

int main() {
	string prev = " ";
	string curr;
	while (cin >> curr) {
		if (prev == curr)
			cout << "반복된 단어: " << curr << "\n";
		prev = curr;
	}

	keep_window_open();
    return 0;
    }