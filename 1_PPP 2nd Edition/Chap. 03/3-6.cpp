#include "std_lib_facilities.h"

int main()
{
	int num_of_words = 0;
	string prev = " ";
	string curr;

	while(cin>>curr){
	++num_of_words;

	if (prev == curr)
		cout << "�ܾ� ��ȣ " << num_of_words
		<< " �ݺ� �ܾ�: " << curr << "\n";
	prev = curr;
	}

	keep_window_open();
	return 0;
}