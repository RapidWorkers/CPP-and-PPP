#include "std_lib_facilities.h"
//4�� ���� 4
//���� : https://www.khanacademy.org/computing/computer-science/algorithms/intro-to-algorithms/a/a-guessing-game
//����� ���� Ž�� ������.

int main(){
	int maxnum = 1;
	int min = 1;

	cout << "ã�� ������ �ִ밪: ";
	cin >> maxnum;

	while(true){
		char yesno;
		
		cout << "ã�� ���ڰ� " << (maxnum + min) / 2 << "���� ū����? (y/n): ";
		cin>>yesno;

		if(yesno == 'y')
			min = (maxnum + min) / 2 + 1;
		else
			maxnum = (maxnum + min) / 2;

		if (maxnum - min == 1)
		{
			cout << "ã�� ���ڰ� " << maxnum << "�ΰ���? (y/n)\n";
			cin>>yesno;
			
			if(yesno == 'y'){
				cout << "ã�� ���ڴ� " << maxnum << "\n";
				return 0;
			}else{
				cout << "ã�� ���ڴ� " << min << "\n";
				return 0;
			}
		}
	}
	return 0;
}