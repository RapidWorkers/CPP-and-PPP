#include "std_lib_facilities.h"
//4�� �ǽ����� 7~11��.

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
			cout << "�׷� ������ ��! \n";
		}
	}

	if(v.size() == 0){
		cout << "�Է��� ���� �����ϴ�. ����.\n";
		return 0;
	}else{
		cout << "�Է°� : \n";
		sort(v);
		max = v[v.size()-1];
		min = v[0];
		for (double x : v){
			cout << x << "\n";
			sum += x;
		}
		cout << "�ִ밪 : " << max
			 << " �ּҰ� : " << min
			 << " ���� �� : " << sum
			 << " ���� ���� : " << v.size();
		return 0;
	}
}