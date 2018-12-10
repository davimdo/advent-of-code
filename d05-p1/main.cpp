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

int main(int argc, char *argv[]) {
  string file = "";
  if (argc != 2) {
    exit(1);
  }

  string polymer = load_data(argv[1]);
  for (int i = 0; i < (int)(polymer.size() - 1); i++) {
    int a = (int)polymer[i];
    int b = (int)polymer[i + 1];

    if (abs((a - b)) == 32) {
      polymer.erase(i, 2);
      i -= 2;
    }
  }

  cout << "SOLUCION: "
       << " - " << polymer.size() << endl;
}