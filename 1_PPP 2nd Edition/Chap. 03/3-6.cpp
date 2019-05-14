#include "std_lib_facilities.h"

int main()
{
	int num_of_words = 0;
	string prev = " ";
	string curr;

	while(cin>>curr){
	++num_of_words;

	if (prev == curr)
		cout << "단어 번호 " << num_of_words
		<< " 반복 단어: " << curr << "\n";
	prev = curr;
	}

	keep_window_open();
	return 0;
}