#include "std_lib_facilities.h"

int main(){
	
	cout << "정수 값 하나 : \n";
	int p;
	cin >> p;

	cout << "n == " << p
		<< "\n3곱하기 n = " << 3 * p
		<< "\nn의 두배 = " << 2 * p
		<< "\nn의 제곱 = " << p*p
		<< "\nn 나누기 2" << p / 2
		<< "\nn의 제곱근 == " << sqrt((double)p)
		<< "\n";

	keep_window_open();
	return 0;
}