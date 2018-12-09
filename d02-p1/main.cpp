#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;


int main() {
    ifstream fis;
    fis.open("index.txt");

    int count_2=0, count_3=0;
    while (fis.good()) {
        string line;
        fis >> line;

        unordered_map<char, int> line_char_map;
        for (int i = 0; i < line.size(); i++) {
            int count = line_char_map[line[i]];
            line_char_map[line[i]] = count+1;
        }
        bool has_count_2 = false, has_count_3 = false;
        for (auto iter = line_char_map.begin(); iter != line_char_map.end(); iter++){
            cout << iter->first << " " << iter->second << endl;
            if (iter->second == 2 && !has_count_2) {
                count_2++;
                has_count_2 = true;
            }
            if (iter->second == 3 && !has_count_3) {
                count_3++;
                has_count_3 = true;
            }
            if (has_count_2 && has_count_3) {
                break;
            }
        }
        cout << endl << count_2 << " " << count_3 << endl;
        cout << "---" << endl;
    }
    cout << (count_2*count_3) << endl;
}