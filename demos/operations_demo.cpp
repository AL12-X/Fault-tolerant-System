#include <iostream>
#include "../src/common.hpp"
#include "../src/operations.hpp"

int main(int argc, char** argv) {
    int a = 45;
    int b = 10;
    FT::ErrorStatus err;

    std::cout << FT::mult(a, b, err) << '\n';
    std::cout << (err == FT::ErrorStatus::corrected) << std::endl;

    return 0;
}