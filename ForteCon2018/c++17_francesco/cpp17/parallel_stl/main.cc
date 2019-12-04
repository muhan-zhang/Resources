#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
  std::vector<double> v(100'000'007, 0.5);

  {
    auto t1 = std::chrono::high_resolution_clock::now();

    double result = std::accumulate(v.begin(), v.end(), -100.0);

    auto t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> ms = t2 - t1;
    std::cout << std::fixed << "std::accumulate result " << result << " took "
              << ms.count() << " ms\n";
  }

  // when the parallel STL becomes available you will be able to call
  //
  //  #include <execution>
  // std::reduce(std::execution::par, v.begin(), v.end());
  //
  //  {
  //    auto t1 = std::chrono::high_resolution_clock::now();
  //    double result = std::reduce(std::execution::par, v.begin(), v.end());
  //    auto t2 = std::chrono::high_resolution_clock::now();
  //    std::chrono::duration<double, std::milli> ms = t2 - t1;
  //    std::cout << "std::reduce result " << result << " took " << ms.count()
  //              << " ms\n";
  //  }
}
