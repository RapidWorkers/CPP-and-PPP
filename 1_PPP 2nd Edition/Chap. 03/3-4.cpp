#include "std_lib_facilities.h"

int main(){

cout << "�̸��� �ΰ� �Է�\n";
string first;
string second;

cin >> first >> second;

if (first == second)
	cout << "�̸��� �����ϴ�.";
if (first < second)
	cout << first << "�� ���ĺ������� �� �տ� ��ġ:" << second << '\n';
if (first > second)
	cout << first << "�� ���ĺ������� �� �ڿ� ��ġ:" << second << '\n';

keep_window_open();
return 0;
}