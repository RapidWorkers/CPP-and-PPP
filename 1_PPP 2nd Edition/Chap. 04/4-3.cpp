#include "std_lib_facilities.h"
//4장 실습문제 7~11번.

int main(){

	double num;
	string unit;
	double max;
	double min;
	double sum = 0;
	vector<double> v;

	while (cin>>num)
	{
		cin >> unit;
		
		if (unit == "m")
		{
			v.push_back(num);
		}else if (unit == "cm")
		{
			v.push_back(num/100);
		}else if (unit == "in")
		{
			v.push_back(num*2.54/100);
		}else if (unit == "ft")
		{
			v.push_back(num*12*2.54/100);
		}else{
			cout << "그런 단위는 모름! \n";
		}
	}

	if(v.size() == 0){
		cout << "입력한 값이 없습니다. 종료.\n";
		return 0;
	}else{
		cout << "입력값 : \n";
		sort(v);
		max = v[v.size()-1];
		min = v[0];
		for (double x : v){
			cout << x << "\n";
			sum += x;
		}
		cout << "최대값 : " << max
			 << " 최소값 : " << min
			 << " 값의 합 : " << sum
			 << " 값의 개수 : " << v.size();
		return 0;
	}
}