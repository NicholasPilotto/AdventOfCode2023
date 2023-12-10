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

bool areAllZeros(const vector<int>& test) {
  for (const int v : test) {
    if (v != 0) {
      return false;
    }
  }

  return true;
}

int getPrediction(vector<int> values) {
  int diff          = -1;
  int value         = 0;
  bool stop         = false;
  vector<int> diffs = values;

  while (!areAllZeros(diffs)) {
    int cut = 0;
    for (int i = 1; i < diffs.size(); ++i) {
      diffs[i - 1] = diffs[i] - diffs[i - 1];
      cut          = i;
    }

    diffs = {diffs.begin(), diffs.begin() + cut};

    if (diffs[diffs.size() - 1] == 0) {
      stop = true;
    }

    value += diffs[diffs.size() - 1];
  }

  return values[values.size() - 1] + value;
}

int getPredictionReverse(vector<int> values) {
  std::reverse(values.begin(), values.end());
  return getPrediction(values);
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

  vector<int> values;
  vector<int> valuesReversed;

  vector<vector<int>> history;

  int index = 0;
  for (string line; getline(input, line);) {
    vector<string> readValues = helper::split_string(line);

    history.emplace_back(vector<int>());

    for (const auto& read : readValues) {
      int v = stoi(read);
      history[index].emplace_back(stoi(read));
    }

    values.emplace_back(getPrediction(history[index]));
    valuesReversed.emplace_back(getPredictionReverse(history[index]));
    ++index;
  }

  int sum         = 0;
  int sumReversed = 0;

  for (const int value : values) {
    sum += value;
  }

  for (const int value : valuesReversed) {
    sumReversed += value;
  }

  cout << "Part 1: " << sum << '\n';
  cout << "Part 2: " << sumReversed << '\n';

  input.close();
  return 0;
}
