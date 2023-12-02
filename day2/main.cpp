#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <tuple>

using std::cout;
using std::fstream;
using std::getline;
using std::map;
using std::string;
using std::stringstream;
using std::tuple;
using std::vector;

/**
 * Return the number of cubes per extraction
 *
 * @param token token which to extract the number
 * of cubes.
 *
 * @return Tuple containing the number of:
 * - red cubes
 * - green cubes
 * - blue cubes
 */
vector<int> getValues(string token) {
  int red    = 0;
  int green  = 0;
  int blue   = 0;

  size_t pos = token.find("red");
  if (pos != std::string::npos) {
    pos = pos - 3;
    red = stoi(token.substr(pos, 2));
  }

  pos = token.find("green");
  if (pos != string::npos) {
    pos   = pos - 3;
    green = stoi(token.substr(pos, 2));
  }

  pos = token.find("blue");
  if (pos != string::npos) {
    pos  = pos - 3;
    blue = stoi(token.substr(pos, 2));
  }

  return {red, green, blue};
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

  int idsSum     = 0;
  int powerCubes = 0;
  string line;

  map<string, int> maxValues{
    {"red",   12},
    {"green", 13},
    {"blue",  14},
  };

  int index  = 1;

  bool valid = true;

  while (getline(input, line)) {
    vector<string> games;
    size_t pos = 0;

    string token;

    stringstream ss(line);

    int max_red   = 1;
    int max_green = 1;
    int max_blue  = 1;

    while (getline(ss, token, ';')) {
      vector<int> game = getValues(token);

      valid            = valid && game[0] <= maxValues["red"] && game[1] <= maxValues["green"] && game[2] <= maxValues["blue"];

      max_red          = std::max(max_red, game[0]);
      max_green        = std::max(max_green, game[1]);
      max_blue         = std::max(max_blue, game[2]);
    }

    if (valid) {
      idsSum += index;
    }
    valid = true;
    ++index;

    powerCubes += max_red * max_green * max_blue;
  }

  input.close();

  cout << "Part 1: " << idsSum << '\n';
  cout << "Part 2: " << powerCubes << '\n';
  return 0;
}
