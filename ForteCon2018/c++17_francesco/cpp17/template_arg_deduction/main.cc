// A simple program that computes the square root of a number
#include <iostream> // std::cout
#include <numeric>  // std::iota
#include <tuple>    // std::tuple
#include <vector>   // std::vector

#include "../../type_name.h"

int main(int, char **) {
  // access the variables in a tuple (copy)

  // in C++11
  std::pair<int, double> p1(2, 3.1415);

  // in C++17
  auto p2 = std::pair(2, 3.1415);
  // or
  std::pair p3(2, 3.1415);

  std::cout << "\nfirst = " << p3.first << ", second = " << p3.second << std::endl;

  std::cout << "\ndecltype(p3) is " << type_name<decltype(p3)>() << '\n';

  return 0;
}

std::tuple<int, int, int> mytuple1(int i) {
  return std::make_tuple(i - 1, i, i + 1);
}

auto mytuple2(int i) {
  return std::tuple(i - 1, i, i + 1); // Types deduced automatically
}
