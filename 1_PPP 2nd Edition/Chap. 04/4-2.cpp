#include "std_lib_facilities.h"
//4장 실습문제 6번.

int main(){

	double num;
	double min = 0.0;
	double max = 0.0;

	cin>>num;
	cout << "입력값: " << num << "\n";
	max = num;
	min = num;

	while (cin>>num)
	{
		if (num > max){
			max = num;
			cout << "입력값: " << num << "(현재 최고값: " << max << ")\n";

		}else if(num < min){
			min = num;
			cout << "입력값: " << num << "(현재 최저값: " << min << ")\n";

		}else{
			cout << "입력값: " << num << "\n";
		}

	}
return 0;
}