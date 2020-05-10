#include <iostream>

#include "../src/common.hpp"
#include "../templates/current_function.hpp"

void foo(FT::Function caller) {
    if (FT::currentFunction != FT::Function::foo) throw std::runtime_error("IP register error");

    std::cout << "Function 'foo' called" << std::endl;

    FT::currentFunction = caller;
}

void bar(FT::Function caller) {
    if (FT::currentFunction != FT::Function::bar) throw std::runtime_error("IP register error");

    std::cout << "Function 'bar' called" << std::endl;

    FT::currentFunction = caller;
}

int main() {
    FT::currentFunction = FT::Function::main;
    std::cout << "Program started" << std::endl;

    FT::currentFunction = FT::Function::foo;
    foo(FT::Function::main);
    if (FT::currentFunction != FT::Function::main) throw std::runtime_error("IP register error");

    FT::currentFunction = FT::Function::bar;
    bar(FT::Function::main);
    if (FT::currentFunction != FT::Function::main) throw std::runtime_error("IP register error");

    std::cout << "Program finished" << std::endl;
    FT::currentFunction = FT::Function::none;
}