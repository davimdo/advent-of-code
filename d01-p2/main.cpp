#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;


int main() {
	vector<int> puzzle_vector;
	ifstream ifs;
	ifs.open("index.txt");
	while (ifs.good()) {
		int num;
		ifs >> num;
		puzzle_vector.push_back(num);
	}

	unordered_map<int, int> frec_map;
	int sum = 0;
	bool finish = false;
	while(true) {
		for (int i = 0; i < puzzle_vector.size(); i++) {
			sum += puzzle_vector[i];
			if (frec_map[sum] == 1){
				finish = true;
				break;
			}
			frec_map[sum] = 1;
		}
		if (finish) {
			break;
		}
	}
	cout << sum << endl;
}
