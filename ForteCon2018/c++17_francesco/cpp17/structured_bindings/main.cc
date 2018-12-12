// A simple program that computes the square root of a number
#include <iostream>  // std::cout
#include <numeric>   // std::iota
#include <tuple>     // std::tuple
#include <vector>    // std::vector

std::tuple<int, int, int> mytuple(int i) {
  return std::make_tuple(i - 1, i, i + 1);
}

int main(int, char**) {
  // access the variables in a tuple (copy)
  auto[i, j, k] = mytuple(10);

  std::cout << "i = " << i << ", j = " << j << ", k = " << k << std::endl;

  // populate a vector of tuples
  std::vector<std::tuple<int, int, int>> list;
  list.push_back(mytuple(1));
  list.push_back(mytuple(2));
  list.push_back(mytuple(4));
  list.push_back(mytuple(8));

  std::cout << "\nMy list:\n";
  for (auto& t : list) {
    auto & [ i, j, k ] = t;  // access the variables in a tuple (by reference)
    std::cout << "i = " << i << ", j = " << j << ", k = " << k << std::endl;
    i = 10;
    j = 20;
    k = 30;
  }

  std::cout << "\nMy list:\n";
  for (const auto & [ i, j, k ] : list) {  // directly unpack the tuple
    std::cout << "i = " << i << ", j = " << j << ", k = " << k << std::endl;
  }

  return 0;
}
