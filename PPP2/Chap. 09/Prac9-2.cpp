#include "std_lib_facilities.h"

class Name_pairs {
public:
	void read_names();
	void read_ages();
	void print();
	void sort();
	const vector<string>& get_names() const { return name; }
	const vector<double>& get_ages() const { return age; }
private:
	vector<string> name;
	vector<double> age;
};

void Name_pairs::read_names() {
	string str;
	cin >> str;
	if (!cin) error("not a string");
	this->name.push_back(str);
}

void Name_pairs::read_ages() {
	double age;
	cin >> age;
	if (!cin) error("not a number");
	this->age.push_back(age);
}

void Name_pairs::print() {
	for (int i = 0; i < this->name.size(); i++) {
		cout << "Name: " << name[i] << " Age: " << age[i] << endl;
	}
}

void Name_pairs::sort() {
	vector<string> orgName = name;
	vector<double> orgAge = age;

	std::sort(name.begin(), name.end());

	for (int i = 0; i < name.size(); i++) {
		for (int j = 0; j < name.size(); j++) {
			if (name[i] == orgName[j]) {
				age[i] = orgAge[j];
				break;
			}
		}
	}

	return;
}

ostream& operator<<(ostream& os, Name_pairs &n)
{
	for (int i = 0; i < n.get_names().size(); i++) {
		os << "Name: " << n.get_names()[i] << " Age: " << n.get_ages()[i] << endl;
	}

	return os;
};

bool operator==(Name_pairs &np1, Name_pairs &np2)
{
	//다 비교
	return 0;
}

int main() {
	Name_pairs np;

	try {
		np.read_names();
		np.read_ages();
		np.read_names();
		np.read_ages();
		np.print();
		np.sort();
		np.print();
		cout << np;
	}
	catch (exception &e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "IDONKNOW" << endl;
	}
}
