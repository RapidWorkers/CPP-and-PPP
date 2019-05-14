#include "std_lib_facilities.h"
//4장 실습문제 5번까지.

int main(){

	double num1;
	double num2;

	while (cin>>num1>>num2)
	{
		if (num1 < num2){
			cout << "더 작은 값: " << num1 << " " << " 더 큰 값: " << num2 << "\n";
			if(num2-num1<1.0/100)
				cout << "두 수는 거의 같다!\n";

		}else if(num1 > num2){
			cout << "더 큰 값: " << num1 << " " << " 더 작은 값: " << num2 << "\n";
			if(num1-num2<1.0/100)
				cout << "두 수는 거의 같다!\n";

		}else if(num1 == num2){
			cout << num1 << "==" << num2 << "\n";
		}

	}
return 0;
}