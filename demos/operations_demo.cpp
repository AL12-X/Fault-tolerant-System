#include <iostream>
#include "../src/common.hpp"
#include "../src/operations.hpp"

int main(int argc, char** argv) {
    int a = 45;
    int b = 10;
    FT::ErrorStatus err;

    std::cout << "Operand 1: " << a << std::endl;
    std::cout << "Operand 2: " << b << std::endl;

    std::cout << std::endl;

    std::cout << "mult: " << FT::mult(a, b, err) << " " << (err == FT::ErrorStatus::corrected) << std::endl;
    std::cout << "div: " << FT::div(a, b, err) << " " << (err == FT::ErrorStatus::corrected) << std::endl;
    std::cout << "lNot: " << FT::lNot(a, err) << " " << (err == FT::ErrorStatus::corrected) << std::endl;

    return 0;
}