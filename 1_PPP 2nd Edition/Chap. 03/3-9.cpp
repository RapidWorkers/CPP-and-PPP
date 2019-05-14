#include "std_lib_facilities.h"

int main(){
	cout << "편지 받을 사람의 이름은? :";
	string name;
	cin >> name;
	cout << "그 사람의 나이는? :";
	int age;
	cin >> age;
	cout << "다른 친구의 이름은? :";
	string friend_name;
	cin >> friend_name;
	cout << "나의 이름은? :";
	string my_name;
	cin >> my_name;
	cout << "그 친구의 성별은?(m or f) :";
	char friend_sex;
	cin >> friend_sex;

	cout << "친애하는" << name << ",\n"
		 << "잘 지내시죠?\n"
		 << "이 " << friend_name << "새기가 뒤졌나 연락이 없네요\n";

	if (friend_sex == 'm')
	{
		cout << "그 놈한테 빨리 연락하라고 해주세요 \n";
	}

	if (friend_sex == 'f')
	{
		cout << "그 년한테 빨리 연락하라고 해주세요 \n";
	}

	return 0;
}