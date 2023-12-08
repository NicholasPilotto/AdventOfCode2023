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

enum cardtype {
  HIGH     = 1,
  ONE_PAIR = 2,
  TWO_PAIR = 3,
  THREE    = 4,
  HOUSE    = 5,
  FOUR     = 6,
  FIVE     = 7,
};

using Hand = std::tuple<std::string, cardtype, int>;  //cards, cardtype, bid

cardtype hand(string& cards) {
  cards.erase(std::remove(cards.begin(), cards.end(), '1'), cards.end());
  int jokers = 5 - cards.length();

  std::map<char, int> counts;

  for (char card : cards) {
    ++counts[card];
  }
  int most = std::max_element(counts.begin(), counts.end(), [](auto a, auto b) {
               return a.second < b.second;
             })->second;

  switch (std::set(cards.begin(), cards.end()).size()) {
    case 5:
      return HIGH;
    case 4:
      return ONE_PAIR;
    case 3:
      return most + jokers == 3 ? THREE : TWO_PAIR;
    case 2:
      return most + jokers == 4 ? FOUR : HOUSE;
    default:
      return FIVE;
  }
}

bool compare(Hand a, Hand b) {
  if (std::get<1>(a) == std::get<1>(b)) {
    return std::get<0>(a) < std::get<0>(b);
  }

  return std::get<1>(a) < std::get<1>(b);
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

  vector<Hand> hands;

  for (string line; getline(input, line);) {
    vector<string> values = helper::split_string(line);

    std::replace(values[0].begin(), values[0].end(), 'T', 'a');
    std::replace(values[0].begin(), values[0].end(), 'J', '1');
    std::replace(values[0].begin(), values[0].end(), 'Q', 'c');
    std::replace(values[0].begin(), values[0].end(), 'K', 'd');
    std::replace(values[0].begin(), values[0].end(), 'A', 'e');

    hands.emplace_back(values[0], hand(values[0]), stoi(values[1]));
  }

  std::sort(hands.begin(), hands.end(), compare);

  int sum = 0;
  for (unsigned i = 0; i < hands.size(); i++) {
    sum += std::get<2>(hands[i]) * (i + 1);
  }
  std::cout << "Part 2: " << sum << std::endl;

  input.close();
  return 0;
}
