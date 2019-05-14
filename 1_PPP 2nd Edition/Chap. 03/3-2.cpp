#include "std_lib_facilities.h"

int main(){
	
	cout << "부동소수점 값 하나 : \n";
	double n;
	cin >> n;

	cout << "n == " << n
		<< "\n3곱하기 n = " << 3 * n
		<< "\nn의 두배 = " << 2 * n
		<< "\nn의 제곱 = " << n*n
		<< "\nn 나누기 2" << n / 2
		<< "\nn의 제곱근 == " << sqrt(n)
		<< "\n";

	keep_window_open();
	return 0;
}