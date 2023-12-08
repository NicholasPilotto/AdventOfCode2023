#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <tuple>

#include "../helper.hpp"

using namespace npilotto;

using std::array;
using std::cout;
using std::fstream;
using std::get;
using std::getline;
using std::map;
using std::set;
using std::string;
using std::stringstream;
using std::tuple;
using std::vector;

using couple = tuple<string, string>;

vector<string> getValues(string& line) {
  vector<string> result;
  vector<string> tokens = helper::split_string(line, '=');

  helper::rtrim(tokens[0]);

  result.emplace_back(tokens[0]);

  tokens = helper::split_string(tokens[1], ',');

  tokens[0].erase(0, 2);
  result.emplace_back(tokens[0]);

  tokens[1].erase(0, 1);
  tokens[1].erase(tokens[1].length() - 1);
  result.emplace_back(tokens[1]);

  return result;
}

string getValueFromCouple(couple c, char i) {
  return i == 'L' ? get<0>(c) : get<1>(c);
}

int getSteps(map<string, couple>& map, string directions) {
  bool found     = false;
  int index      = 0;
  couple element = map["AAA"];
  int steps      = 1;

  while (!found) {
    string value = getValueFromCouple(element, directions[index]);
    if (value == "ZZZ") {
      found = true;
    } else {
      element = map[value];
      ++steps;
    }

    index = index == directions.length() - 1 ? 0 : ++index;
  }

  return steps;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    throw std::invalid_argument("Missing input file argument.");
  }

  fstream input;
  input.open(argv[1]);

  if (!input.is_open()) {
    cout << "Failed to open the input file\n";
    return -1;
  }

  string directions;

  getline(input, directions);

  map<string, couple> map;

  int i = 0;
  for (string line; getline(input, line); ++i) {
    if (i < 2) {
      continue;
    }

    vector<string> values = getValues(line);

    map[values[0]]        = std::make_tuple(values[1], values[2]);
  }

  input.close();

  int steps = getSteps(map, directions);

  cout << "Part 1: " << steps << '\n';

  return 0;
}
