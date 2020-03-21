#include <iostream>
#include "main.hpp"

int main(int argc, char** argv) {
    int a = 5;
    double b = 8;
    FT::ErrorStatus err;
    std::cout << FT::lxor(a, 2, err) << std::endl;
    std::cout << (err == FT::ErrorStatus::caughtError) << std::endl;
    std::cout << FT::land(a, 4, err) << std::endl;
    std::cout << (err == FT::ErrorStatus::caughtError) << std::endl;
    return 0;
}