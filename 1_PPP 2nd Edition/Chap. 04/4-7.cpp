#include "std_lib_facilities.h"
//4장 연습 5~7번
//힌트 : 저자양반 ㅠㅠ
// cin이 실패한 후에는 cin.clear()을 사용해서 초기화 해야함.
// 함수를 이용해서 만들도록 하자.

int get_number(){
	vector<string> alpha_num = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

	int num;
	
	if(cin>>num) return num;
	cin.clear();
	string numstr;
	cin>>numstr;

	for (int i=0;i<alpha_num.size();++i)
	{
		if(alpha_num[i] == numstr)
			num = i;
	}
	return num;
}

int main(){
	char opera;
	int num1 = get_number();
	cin >> opera;
	int num2 = get_number();

	

	switch (opera)
	{
	case '+':
		cout << "결과 : " << num1 << " " << opera << " " << num2 << " =" << num1 + num2;
		break;
	case '-':
		cout << "결과 : " << num1 << " " << opera << " " << num2 << " =" << num1 - num2;
		break;
	case '*':
		cout << "결과 : " << num1 << " " << opera << " " << num2 << " =" << num1 * num2;
		break;
	case '/':
		cout << "결과 : " << num1 << " " << opera << " " << num2 << " =" << num1 / num2;
		break;
	default :
		cout << "나는 그런 연산자 모른다";
		break;
	}
	

	return 0;
}