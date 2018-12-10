#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string load_data(string file_name) {
  FILE *fis = fopen(file_name.c_str(), "r");
  string line = "";
  char c = '\0';
  do {
    c = getc(fis);
    if (c != '\n') {
      line += c;
    }
  } while (c != '\n');
  return line;
}

int get_final_polymer_length(string polymer) {
  for (int i = 0; i < (int)(polymer.size() - 1); i++) {
    int a = (int)polymer[i];
    int b = (int)polymer[i + 1];

    if (abs((a - b)) == 32) {
      polymer.erase(i, 2);
      i -= 2;
    }
  }
  return polymer.size();
}

string remove_unit_type(string polymer, char unit_type) {
  for (auto it = polymer.begin(); it != polymer.end(); it++) {
    int c_it = (int)*it;
    if (c_it == (int)unit_type || c_it == ((int)unit_type-32)) {
      polymer.erase(it);
      it--;
    }
  }
  return polymer;
}

int main(int argc, char *argv[]) {
  string file = "";
  if (argc != 2) {
    exit(1);
  }

  string polymer = load_data(argv[1]);

  int max = INT_MAX;
  for (char i = 'a'; i <= 'z'; i++) {
    string p = polymer;
    p = remove_unit_type(p, i);
    int size = get_final_polymer_length(p);
    if (size < max) {
      max = size;
    }
  }
  cout << max << endl;
}