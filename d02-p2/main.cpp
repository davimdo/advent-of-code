#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

string str_remove_letter_at(string str, int pos) {
    string str1 = str.substr(0, pos);
    string str2 = str.substr(pos+1);
    string fin = str1 + str2;
    return fin;
}

int main() {
    ifstream fis;
    fis.open("index.txt");

    vector<string> lines;
    while (fis.good()) {
        string line;
        fis >> line;
        lines.push_back(line);
    }
    
    string result = "";
    for(int i = 0; i < lines.size()-1; i++) {
        string line_1 = lines[i];
        for (int j = i+1; j < lines.size(); j++) {
            string line_2 = lines[j];
            for (int k = 1; k < line_1.size(); k++) {
                string str1 = str_remove_letter_at(line_1, k);
                string str2 = str_remove_letter_at(line_2, k);
                if (str1.compare(str2) == 0){
                // if (true) {
                    cout << str1 << endl;
                    return 0;
                }
            }
        }
    }
}