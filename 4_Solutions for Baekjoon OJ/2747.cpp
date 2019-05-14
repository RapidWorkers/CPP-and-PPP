#include <iostream>
int fibo(int n) {
	int a = 1, b = 1, tmp;
	for (int i = 1; i < n; i++) {//n-1번 반복
		tmp = b;
		b = a + b; //피보나치 수열은 이전 두 값의 합
		a = tmp;
	}
	return b;//수열의 값 반환
}
int main() {
	int n;
	std::cin >> n;
	std::cout << fibo(n-1);
}