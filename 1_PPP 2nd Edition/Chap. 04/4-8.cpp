#include "std_lib_facilities.h"
//4�� ���� 8~9��

int main(){
	int num1 = 1;
	cin >> num1;
	
	int sum = 0;
	int currentrice = 1;
	int currentchess = 1;

	while(num1 > sum)
	{
		if(currentchess==1) currentrice = 1;
		else currentrice *= 2;
		
		sum += currentrice;

		cout << "���� �� ����: " << currentrice << "�� , ���� ü��ĭ: " << currentchess << " ��° ĭ �� �� ����: "<< sum << "\n"; 
		currentchess++;
	}

	cout << num1 << "��ŭ �ִµ��� " << currentchess - 1 << "ĭ ��ŭ �ʿ� \n";
	return 0;
}