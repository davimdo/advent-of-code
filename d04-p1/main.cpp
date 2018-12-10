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
int main() {
  auto guard_log = load_data("index.txt");

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

  // for (auto it = guard_sleep_map.begin(); it != guard_sleep_map.end(); it++)
  // {
  //   cout << it->first << endl;
  //   for (auto i : it->second) {
  //     cout << i << " ";
  //   }
  //   cout << endl << "==================================" << endl;
  // }

  unordered_map<int, int> g_sum;
  int max_id = 0; 
  int max = 0;
  for (auto it = guard_sleep_map.begin(); it != guard_sleep_map.end(); it++) {
    int sum = 0;
    for (auto times : it->second) {
      sum += times;
    }
    cout << it->first << " - " << sum << endl;
    if (sum > max) {
      max = sum;
      max_id = it->first;
    }
  }
  
  auto max_schedule = guard_sleep_map[max_id];
  int max_times, minute = 0;
  for (int i = 0; i < 60; i++) {
    if (max_schedule[i] > max_times) {
      minute = i;
      max_times = max_schedule[i];
    }
  }
  // cout << max_id << ": " << minute << endl;
  cout << (max_id * minute) << endl;
}
