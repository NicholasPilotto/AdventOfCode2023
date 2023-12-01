#include <iostream>
#include <fstream>
#include <stdexcept>
#include <map>

using namespace std;

int main(int argc, char** argv) {
  // Throw error if input wasn't given
  if (argc != 2) {
    throw std::invalid_argument("Missing input file argument.");
  }

  // Get file as an input stream
  fstream input;
  input.open(argv[1]);

  if (!input.is_open()) {
    cout << "Failed to open file." << endl;
    return -1;
  }

  int sum1 = 0;
  int sum2 = 0;

  map<string, int> digits;
  digits["one"] = 1;
  digits["two"] = 2;
  digits["three"] = 3;
  digits["four"] = 4;
  digits["five"] = 5;
  digits["six"] = 6;
  digits["seven"] = 7;
  digits["eight"] = 8;
  digits["nine"] = 9;

  // Loop over all strings
  while (!input.eof()) {
    string calibrate;
    input >> calibrate;
    int indFirst = 0;
    int indLast = calibrate.length() - 1;

    cout << calibrate << endl;

    // Find the first and last digits respectively (Part 1)
    while (!isdigit(calibrate[indFirst]) || !isdigit(calibrate[indLast])) {
      if (!isdigit(calibrate[indFirst]))
        indFirst++;
      if (!isdigit(calibrate[indLast]))
        indLast--;
    }

    cout << "Codes | P1: " << calibrate[indFirst] << calibrate[indLast] << " | ";

    sum1 += (calibrate[indFirst] - 48) * 10;
    sum1 += calibrate[indLast] - 48;

    bool firstFound = false;
    int d1, d2;

    // Find the first and last digits respectively (Part 2)
    for (indFirst = 0; indFirst < calibrate.length(); indFirst++) {
      // When pointing to a digit character
      if (isdigit(calibrate[indFirst])) {
        if (!firstFound) {
          d1 = calibrate[indFirst] - 48;
          firstFound = true;
        }
        d2 = calibrate[indFirst] - 48;
      } else { // When pointing to a letter (number in word form)
        if (digits.count(calibrate.substr(indFirst, 3))) {
          if (!firstFound)
          {
            d1 = digits[calibrate.substr(indFirst, 3)];
            firstFound = true;
          }
          d2 = digits[calibrate.substr(indFirst, 3)];
        }

        if (digits.count(calibrate.substr(indFirst, 4))) {
          if (!firstFound) {
            d1 = digits[calibrate.substr(indFirst, 4)];
            firstFound = true;
          }
          d2 = digits[calibrate.substr(indFirst, 4)];
        }

        if (digits.count(calibrate.substr(indFirst, 5))) {
          if (!firstFound) {
            d1 = digits[calibrate.substr(indFirst, 5)];
            firstFound = true;
          }
          d2 = digits[calibrate.substr(indFirst, 5)];
        }
      }
    }

    cout << "P2: " << d1 << d2 << endl;

    sum2 += d1 * 10 + d2;
  }
  
  input.close();

  cout << "Part 1: The sum of all calibration codes is " << sum1 << "." << endl;
  cout << "Part 2: The sum of all calibration codes is " << sum2 << "." << endl;

  return 0;
}