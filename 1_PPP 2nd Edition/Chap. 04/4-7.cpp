#include "std_lib_facilities.h"
//4�� ���� 5~7��
//��Ʈ : ���ھ�� �Ф�
// cin�� ������ �Ŀ��� cin.clear()�� ����ؼ� �ʱ�ȭ �ؾ���.
// �Լ��� �̿��ؼ� ���鵵�� ����.

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
		cout << "��� : " << num1 << " " << opera << " " << num2 << " =" << num1 + num2;
		break;
	case '-':
		cout << "��� : " << num1 << " " << opera << " " << num2 << " =" << num1 - num2;
		break;
	case '*':
		cout << "��� : " << num1 << " " << opera << " " << num2 << " =" << num1 * num2;
		break;
	case '/':
		cout << "��� : " << num1 << " " << opera << " " << num2 << " =" << num1 / num2;
		break;
	default :
		cout << "���� �׷� ������ �𸥴�";
		break;
	}
	

	return 0;
}