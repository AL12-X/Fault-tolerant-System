#include <iostream>
#include "main.hpp"

int main(int argc, char** argv) {
    double a = 2;
    double b = 8;
    FT::ErrorStatus err;
    std::cout << FT::div(a, b, err) << '\n';
    std::cout << (err == FT::ErrorStatus::caughtError) << std::endl;
    return 0;
}