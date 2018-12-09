#include <iostream>
#include <fstream>

using namespace std;


int main() {
	ifstream ifs;
	ifs.open("index.txt");

	int sum = 0;
	while (ifs.good()) {
		int num;
		ifs >> num;
		sum += num;
	}
	cout << sum << endl;
}
