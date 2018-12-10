#include <algorithm>
#include <cstdio>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> load_data(string file_name) {
  FILE *fis = fopen(file_name.c_str(), "r");

  string line = "";
  vector<string> guard_log;
  char c;
  do {
    c = getc(fis);
    if (c != '\n') {
      line.push_back(c);
    } else {
      guard_log.push_back(line);
      line = "";
    }
  } while (c != EOF);

  sort(guard_log.begin(), guard_log.end());
  return guard_log;
}

/**
 * guard id -> '\[1518-(\d+)-(\d+) (\d+):(\d+)\] Guard #(\d+) begins shift'
 * wake_up -> '\[1518-(\d+)-(\d+) (\d+):(\d+)\] wakes up'
 * sleep -> '\[1518-(\d+)-(\d+) (\d+):(\d+)\] falls asleep'
 **/
int main(int argc, char *argv[]) {
  string file = "";
  if (argc != 2) {
    exit(1);
  }

  auto guard_log = load_data(argv[1]);

  static std::regex guard_rgx(
      "\\[1518-(\\d+)-(\\d+) (\\d+):(\\d+)\\] Guard #(\\d+) begins shift");
  static std::regex wake_rgx("\\[1518-(\\d+)-(\\d+) (\\d+):(\\d+)\\] wakes up");
  static std::regex sleep_rgx(
      "\\[1518-(\\d+)-(\\d+) (\\d+):(\\d+)\\] falls asleep");

  unordered_map<int, array<int, 60>> guard_sleep_map;
  int id;
  for (auto l : guard_log) {
    std::smatch matches;
    if (regex_search(l, matches, guard_rgx)) {
      id = stoi(matches[5]);
    } else if (regex_search(l, matches, sleep_rgx)) {
      array<int, 60> guard_schedule{guard_sleep_map[id]};
      int minite = stoi(matches[4]);
      for (int i = minite; i < 60; i++) {
        guard_schedule[i] += 1;
      }
      guard_sleep_map[id] = guard_schedule;
    } else if (regex_search(l, matches, wake_rgx)) {
      array<int, 60> guard_schedule{guard_sleep_map[id]};
      int minite = stoi(matches[4]);
      for (int i = minite; i < 60; i++) {
        if (guard_schedule[i] != 0) {
          guard_schedule[i] -= 1;
        }
      }
      guard_sleep_map[id] = guard_schedule;
    }
  }

  int frec_id, minute = 0, max_frec = 0;
  for (auto it = guard_sleep_map.begin(); it != guard_sleep_map.end(); it++) {
    array<int, 60> schedule = it->second;
    for (int i = 0; i < 60; i++) {
      if (schedule[i] > max_frec) {
        frec_id = it->first;
        max_frec = schedule[i];
        minute = i;
      }
    }
  }
  cout << frec_id << " " << minute << endl;
  cout << (frec_id * minute) << endl;
}
