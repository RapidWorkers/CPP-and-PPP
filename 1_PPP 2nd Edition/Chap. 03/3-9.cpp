#include "std_lib_facilities.h"

int main(){
	cout << "���� ���� ����� �̸���? :";
	string name;
	cin >> name;
	cout << "�� ����� ���̴�? :";
	int age;
	cin >> age;
	cout << "�ٸ� ģ���� �̸���? :";
	string friend_name;
	cin >> friend_name;
	cout << "���� �̸���? :";
	string my_name;
	cin >> my_name;
	cout << "�� ģ���� ������?(m or f) :";
	char friend_sex;
	cin >> friend_sex;

	cout << "ģ���ϴ�" << name << ",\n"
		 << "�� ��������?\n"
		 << "�� " << friend_name << "���Ⱑ ������ ������ ���׿�\n";

	if (friend_sex == 'm')
	{
		cout << "�� ������ ���� �����϶�� ���ּ��� \n";
	}

	if (friend_sex == 'f')
	{
		cout << "�� ������ ���� �����϶�� ���ּ��� \n";
	}

	return 0;
}