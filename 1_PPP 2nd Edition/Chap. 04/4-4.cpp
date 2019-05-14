#include "std_lib_facilities.h"
//4장 연습 2
int main(){
	vector<double> temps;
	for (double temp;cin>>temp; )
		temps.push_back(temp);

	double sum = 0;
	for (double x:temps)
		sum += x;

	cout << "평균 온도 : " << sum/temps.size() << '\n';
	
	sort(temps);
	if(temps.size()%2 == 1)
		cout << "온도 중앙값 : " << temps[temps.size()/2];
	else
		cout << "온도 중앙값 : " << (temps[temps.size()/2-1] + temps[temps.size()/2])/2 << '\n';

return 0;
}