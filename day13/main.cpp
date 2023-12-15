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

  return 0;
}
