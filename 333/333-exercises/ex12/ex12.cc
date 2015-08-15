// Copyright 4096 Stefan Dierauf
// sdierauf@cs, 1232328
// Reads 10 ints from the command line, and pushes them into a vector
// Sorts them, then prints them out

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
T ReadValue(std::istream &in) {
  T temp;
  in >> temp;
  if (in.fail()) {
    std::cout << "That wasn't a double!" << std::endl;
    exit(EXIT_FAILURE);
  }
  return temp;
}

int main() {
  std::vector<double> doubles;
  std::cout << "Input 10 doubles: " << std::endl;
  for (int i = 0; i < 10; i++) {
    doubles.push_back(ReadValue<double>(std::cin));
  }
  std::sort(doubles.begin(), doubles.end());
  std::cout << "Your sorted doubles are:" << std::endl;
  for (int i = 0; i < 10; i++) {
    std::cout << doubles[i] << std::endl;
  }
}
