#include <iostream>
#include "main.hpp"

int main(int argc, char** argv) {
    int a = 45;
    int b = 9;
    FT::ErrorStatus err;

    std::cout << FT::lAnd(a, b, err) << '\n';
    std::cout << (err == FT::ErrorStatus::withError) << std::endl;

    return 0;
}