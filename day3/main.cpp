#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;

int main() {
  ifstream file("input.txt");
  vector<string> lines = {istream_iterator<string>(file), {}};

  vector<pair<int, int>> mat;
  vector<pair<int, int>> dirs = {
    {-1, -1},
    {1,  1 },
    {1,  -1},
    {-1, 1 },
    {-1, 0 },
    {1,  0 },
    {0,  -1},
    {0,  1 }
  };

  int row = 0;
  for (string line = lines[row]; row < lines.size(); ++row, line = lines[row]) {
    vector<char> chars = {line.begin(), line.end()};
    for (int col = 0; col < chars.size(); ++col) {
      char c = chars[col];
      if (c != '.' && !isdigit(c)) {
        for (auto& dir : dirs) {
          mat.push_back({row + dir.first, col + dir.second});
        }
      }
    }
  }

  int sum                                    = 0;
  row                                        = 0;
  size_t sym_idx                             = -1;
  bool ispart                                = false;
  unordered_map<int, vector<int>> gear_parts = {};
  for (string line = lines[row], part_num = ""; row < lines.size(); ++row, line = lines[row]) {
    vector<char> chars = {line.begin(), line.end()};
    for (int col = 0; col < chars.size(); ++col) {
      char c = chars[col];
      if (isdigit(c)) {
        auto found = find_if(mat.begin(), mat.end(), [&row, &col](auto& xy) {
          return (xy.first == row && xy.second == col);
        });
        if (found != mat.end()) {
          ispart  = true;
          sym_idx = (found - mat.begin()) / 8;
        }
        part_num += c;
      }
      if (!isdigit(c) || col == chars.size() - 1) {
        if (!part_num.empty()) {
          if (ispart) {
            sum += stoi(part_num);
            gear_parts[(int)sym_idx].push_back(stoi(part_num));
          }
        }
        ispart   = false;
        part_num = "";
      }
    }
  }

  printf("part1: %d\n", sum);
  int gear_ration = 0;
  for (auto& gear : gear_parts) {
    if (gear.second.size() > 1) {
      gear_ration += accumulate(gear.second.begin(), gear.second.end(), 1, multiplies<int>());
    }
  }

  printf("part2: %d\n", gear_ration);
  return (0);
}
