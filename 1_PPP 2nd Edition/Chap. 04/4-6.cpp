#include "std_lib_facilities.h"
//4장 연습 4
//참고 : https://www.khanacademy.org/computing/computer-science/algorithms/intro-to-algorithms/a/a-guessing-game
//비재귀 이진 탐색 구현임.

int main(){
	int maxnum = 1;
	int min = 1;

	cout << "찾을 숫자의 최대값: ";
	cin >> maxnum;

	while(true){
		char yesno;
		
		cout << "찾을 숫자가 " << (maxnum + min) / 2 << "보다 큰가요? (y/n): ";
		cin>>yesno;

		if(yesno == 'y')
			min = (maxnum + min) / 2 + 1;
		else
			maxnum = (maxnum + min) / 2;

		if (maxnum - min == 1)
		{
			cout << "찾을 숫자가 " << maxnum << "인가요? (y/n)\n";
			cin>>yesno;
			
			if(yesno == 'y'){
				cout << "찾은 숫자는 " << maxnum << "\n";
				return 0;
			}else{
				cout << "찾은 숫자는 " << min << "\n";
				return 0;
			}
		}
	}
	return 0;
}