#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>

using std::cout;
using std::find;
using std::fstream;
using std::getline;
using std::isdigit;
using std::map;
using std::string;
using std::stringstream;
using std::vector;

vector<int> getValues(const string& list) {
  vector<int> result;
  stringstream ss(list);
  string token;
  while (getline(ss, token, ' ')) {
    if (token != " " && !token.empty()) {
      result.push_back(stoi(token));
    }
  }

  return result;
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

  int sum       = 0;
  int sumCopies = 0;

  vector<int> copies(1, 1);

  string line;

  int index = 0;
  while (getline(input, line)) {
    line.erase(0, line.find(':') + 2);

    ++copies[index];

    string winningListString = line.substr(0, line.find('|') - 1);
    string myNumbersString   = line.substr(line.find('|') + 2, line.length());

    vector<int> winningList  = getValues(winningListString);
    vector<int> myNumbers    = getValues(myNumbersString);

    int count                = 0;
    for (auto it = winningList.cbegin(); it != winningList.cend(); ++it) {
      if (find(myNumbers.cbegin(), myNumbers.cend(), *it) != myNumbers.cend()) {
        ++count;
      }
    }

    for (int i = index + 1; i < index + count; ++i) {
      if (i < copies.size()) {
        copies[i] += 2;
      } else {
        copies.push_back(1);
      }
    }

    sum += (0x1 << count) / 2;
    ++index;
  }

  for (auto it = copies.cbegin(); it != copies.cend(); ++it) {
    sumCopies += *it;
  }

  cout << "Part 1: " << sum << '\n';
  cout << "Part 2: " << sumCopies << '\n';

  return 0;
}
