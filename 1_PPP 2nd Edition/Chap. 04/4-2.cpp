#include "std_lib_facilities.h"
//4�� �ǽ����� 6��.

int main(){

	double num;
	double min = 0.0;
	double max = 0.0;

	cin>>num;
	cout << "�Է°�: " << num << "\n";
	max = num;
	min = num;

	while (cin>>num)
	{
		if (num > max){
			max = num;
			cout << "�Է°�: " << num << "(���� �ְ�: " << max << ")\n";

		}else if(num < min){
			min = num;
			cout << "�Է°�: " << num << "(���� ������: " << min << ")\n";

		}else{
			cout << "�Է°�: " << num << "\n";
		}

	}
return 0;
}