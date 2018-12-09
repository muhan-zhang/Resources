// A simple program that computes the square root of a number
#include <iostream>     // std::cout
#include <numeric>      // std::iota
#include <vector>       // std::vector

int main (int argc, char *argv[])
{
    std::vector<double> vec(10, 0.0);
    std::iota (vec.begin(),vec.end(), 0);
    
    std::cout << "numbers:      ";
    for (double& i : vec) std::cout << ' ' << i;
    std::cout << '\n';

    for (double& i : vec){
        i += 1.5;
    }

    std::cout << "numbers + 1.5:";
    for (double& i : vec) std::cout << ' ' << i;
    std::cout << '\n';

    return 0;
}
