// Stefan Dierauf sdierauf@cs.washington.edu 1232328
// ex8 Factorizer
// Factors a number
// Copyright Stefan Dierauf 2015

#include <iostream>
#include <cstdlib>

void factor(int input);

int main(int argc, char **argv) {
  std::string greeting =
    "Which positive integer would you like me to factorize? ";
  std::cout << greeting;
  int in;
  std::cin >> in;
  factor(in);
  return EXIT_SUCCESS;
}

void factor(int input) {
  if (input < 1) {
    std::cerr << "Invalid input!" << std::endl;
    return;
  }
  for (int i = 1; i < input; i++) {
    if (input % i == 0) {
      std::cout << i << " ";
    }
  }
  std::cout << input << std::endl;
}
