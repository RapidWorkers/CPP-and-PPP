#include "std_lib_facilities.h"

int main(){

cout << "이름을 두개 입력\n";
string first;
string second;

cin >> first >> second;

if (first == second)
	cout << "이름이 같습니다.";
if (first < second)
	cout << first << "가 알파벳순으로 더 앞에 위치:" << second << '\n';
if (first > second)
	cout << first << "가 알파벳순으로 더 뒤에 위치:" << second << '\n';

keep_window_open();
return 0;
}