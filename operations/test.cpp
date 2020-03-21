#include <iostream>
#include "main.hpp"

int main(int argc, char** argv) {
<<<<<<< HEAD
    int a = 5;
    double b = 8;
    FT::ErrorStatus err;
    std::cout << FT::lxor(a, 2, err) << std::endl;
    std::cout << (err == FT::ErrorStatus::caughtError) << std::endl;
    std::cout << FT::land(a, 4, err) << std::endl;
    std::cout << (err == FT::ErrorStatus::caughtError) << std::endl;
=======
    int a = 45;
    int b = 9;
    FT::ErrorStatus err;

    std::cout << FT::lAnd(a, b, err) << '\n';
    std::cout << (err == FT::ErrorStatus::withError) << std::endl;

>>>>>>> 595d334b53d1ea3465b06a89d8f4778696c4cb9c
    return 0;
}