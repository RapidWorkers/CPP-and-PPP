#include "std_lib_facilities.h"

int main(){
	
	cout << "���� �� �ϳ� : \n";
	int p;
	cin >> p;

	cout << "n == " << p
		<< "\n3���ϱ� n = " << 3 * p
		<< "\nn�� �ι� = " << 2 * p
		<< "\nn�� ���� = " << p*p
		<< "\nn ������ 2" << p / 2
		<< "\nn�� ������ == " << sqrt((double)p)
		<< "\n";

	keep_window_open();
	return 0;
}