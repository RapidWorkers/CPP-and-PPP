#include "std_lib_facilities.h"

int main() {
	vector<int> numbers;
	int sum_count = -1;

	try {
		cout << "합계를 구할 숫자의 개수를 입력하세요: ";
		cin >> sum_count;
		
		if (sum_count < 1) error("NaN");

		int n;
		cout << "정수를 입력하세요 (|로 입력 종료)" << endl;
		while (cin >> n)
			numbers.push_back(n);

		if (numbers.size() < sum_count) error("too few num");

		int sum = 0;
		for (int i = 0; i < sum_count; ++i)
			sum += numbers[i];

		cout << "앞 숫자 " << sum_count << "개 (";
		for (int i = 0; i < sum_count; ++i)
			cout << numbers[i] << " ";
		cout << " )의 합은 " << sum << "입니다." << endl;

	}
	catch (runtime_error e) {
		cout << e.what() << endl;
	}

}