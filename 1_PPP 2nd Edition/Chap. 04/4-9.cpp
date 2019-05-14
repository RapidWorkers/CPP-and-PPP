#include "std_lib_facilities.h"
//4�� ���� 10���� skip
//4�� ���� 11~15��

vector<int> primes;

bool isPrime(int num){
	for(int x:primes){
		if(num % x == 0) return false;
		}
	primes.push_back(num);
	return true;
}

int main(){
	
	primes.push_back(2);
	
	for(int i=3;i<=100;++i){
		if(isPrime(i)) cout << i << " is a prime\n";
		else cout << i << " is not a prime\n";
	}

	for(int x:primes){
		cout << x << " ";
	}

	return 0;
}