#include "std_lib_facilities.h"

int main(){
	
	cout << "성씨와 나이? : \n";
	string first_name;
	double age = -1;
	cin >> first_name >> age;
	
	cout << "Hello, " << first_name << "(" << age*12 << " 개월)\n";

	keep_window_open();
    return 0;
}