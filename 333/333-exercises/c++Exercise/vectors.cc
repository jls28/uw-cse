#include <vector>
#include <iostream>
#include <numeric>
#include <functional>

int main() {
  std::vector<int> v;
  v.reserve(100);
  for (int i = 1; i <= 10; ++i)
  {
    v.push_back(i);
  }
  int sum = 0;
  for (int i : v) { 
    sum += i;
    std::cout << i; 
  }
  int acc = std::accumulate(v.begin(), v.end(), 1, 
      [](int x, int y){ return x * y ;});
  std::cout << std::endl;
  std::cout << sum << std::endl;
  std::cout << acc << std::endl;
}