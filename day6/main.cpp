#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <tuple>

#include "../helper.hpp"

using std::array;
using std::cout;
using std::fstream;
using std::get;
using std::getline;
using std::map;
using std::string;
using std::stringstream;
using std::tuple;
using std::vector;

void getValues(array<long long, 1>& array, string& line) {
  int i = 0;
  line.erase(0, line.find(':') + 1);

  stringstream ss(line);
  string token;

  while (getline(ss, token, ' ')) {
    if (token != " " && !token.empty()) {
      array[i] = stoll(token);
      ++i;
    }
  }
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

  array<long long, 1> times;
  array<long long, 1> distances;
  long long tmp = 0;

  for (string line; getline(input, line); ++tmp) {
    if (tmp == 0) {
      getValues(times, line);
    } else {
      getValues(distances, line);
    }
  }
  long long result1 = 1;

  long long index   = 0;
  for (const long long t : times) {
    long long sum = 1;
    for (int i = 0; i < t; ++i) {
      long long value = t - i;
      if (i * value > distances[index]) {
        ++sum;
      }
    }

    result1 *= sum;
    ++index;
  }

  input.close();

  cout << "Part 1: " << result1 << '\n';
  cout << "Part 2: " << '\n';

  return 0;
}
