#include "std_lib_facilities.h"
//4장 연습 3
int main(){
	double sum = 0;

	vector<double> distance;
	for (double d_temp;cin>>d_temp ; )
		distance.push_back(d_temp);

	for (double tmp : distance)
	{
		sum += tmp;
	}

	sort(distance);
	cout << "최대 거리 : " << distance[distance.size()-1] << "\n";
	cout << "최소 거리 : " << distance[0] << "\n";
	cout << "평균 거리 : " << sum / distance.size() << "\n";


	return 0;
}