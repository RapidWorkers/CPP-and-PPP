#include "std_lib_facilities.h"
//4�� �ǽ����� 5������.

int main(){

	double num1;
	double num2;

	while (cin>>num1>>num2)
	{
		if (num1 < num2){
			cout << "�� ���� ��: " << num1 << " " << " �� ū ��: " << num2 << "\n";
			if(num2-num1<1.0/100)
				cout << "�� ���� ���� ����!\n";

		}else if(num1 > num2){
			cout << "�� ū ��: " << num1 << " " << " �� ���� ��: " << num2 << "\n";
			if(num1-num2<1.0/100)
				cout << "�� ���� ���� ����!\n";

		}else if(num1 == num2){
			cout << num1 << "==" << num2 << "\n";
		}

	}
return 0;
}