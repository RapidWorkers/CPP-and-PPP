#include "std_lib_facilities.h"
//4�� ���� 3
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
	cout << "�ִ� �Ÿ� : " << distance[distance.size()-1] << "\n";
	cout << "�ּ� �Ÿ� : " << distance[0] << "\n";
	cout << "��� �Ÿ� : " << sum / distance.size() << "\n";


	return 0;
}