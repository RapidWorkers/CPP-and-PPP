#include "std_lib_facilities.h"
//4장 연습 8~9번

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

		cout << "현재 쌀 개수: " << currentrice << "개 , 현재 체스칸: " << currentchess << " 번째 칸 총 쌀 개수: "<< sum << "\n"; 
		currentchess++;
	}

	cout << num1 << "만큼 주는데는 " << currentchess - 1 << "칸 만큼 필요 \n";
	return 0;
}