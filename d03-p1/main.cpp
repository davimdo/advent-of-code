#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Clame {
  int id, px, py, tx, ty;

  string to_string() {
    return "#" + std::to_string(id) + " @ " + std::to_string(px) + "," +
           std::to_string(py) + ": " + std::to_string(tx) + "x" +
           std::to_string(ty);
  }
};

vector<Clame> load_data(string file_name) {
  FILE *file = fopen(file_name.c_str(), "r");
  vector<Clame> clames;

  string line = "";
  char c = getc(file);
  do {
    if (c != '\n') {
      line += c;
    } else {
      Clame clame;
      sscanf(line.c_str(), "#%d @ %d,%d: %dx%d", &clame.id, &clame.px,
             &clame.py, &clame.tx, &clame.ty);
      clames.push_back(clame);
      line = "";
    }
    c = getc(file);
  } while (c != EOF);
  fclose(file);
  return clames;
}

int main() {
  auto clames = load_data("index.txt");

  // for (int i = 0; i < clames.size(); i++) {
  //   cout << clames[i].to_string() << endl;
  // }

  int num = 0;
  vector<vector<int>> area(1000, vector<int>(1000, 0));
  for (auto clame : clames) {
    for (int i = clame.px; i < (clame.px+clame.tx); i++) {
      for (int j = clame.py; j < (clame.py+clame.ty); j++){
        int *point = &area[i][j];
        if (*point != -1) {
          if (*point == 0){
            *point = clame.id;
          } else {
            num++;
            *point = -1;
          }
        }
      }
    }
  }

  cout << num << endl;

  // for (auto line : area ) {
  //   for (auto p : line) {
  //     if (p != 0) {
  //       cout << p << endl;
  //     }
  //   }
  // }
}
