// A simple program that computes the square root of a number
#include <iostream> // std::cout
#include <numeric>  // std::iota
#include <tuple>    // std::tuple
#include <vector>   // std::vector

#include "../../type_name.h"

int myfunc(int i) { return i * i; }

int main(int, char **) {
  // access the variables in a tuple (copy)

  // in C++11
  int a = myfunc(4);
  if (a > 10) {
    std::cout << "\na = " << a << std::endl;
  }

  // in C++17
  if (auto b = myfunc(4); b > 10) {
    std::cout << "\nb = " << b << std::endl;
  }

  a += 10;
  // b += 10; does not compile

  return 0;
}
