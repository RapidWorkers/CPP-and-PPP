#include "std_lib_facilities.h"

int main(){
	
	cout << "�ε��Ҽ��� �� �ϳ� : \n";
	double n;
	cin >> n;

	cout << "n == " << n
		<< "\n3���ϱ� n = " << 3 * n
		<< "\nn�� �ι� = " << 2 * n
		<< "\nn�� ���� = " << n*n
		<< "\nn ������ 2" << n / 2
		<< "\nn�� ������ == " << sqrt(n)
		<< "\n";

	keep_window_open();
	return 0;
}