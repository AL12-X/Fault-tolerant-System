#include <iostream>
#include "analyzer.hpp"

int main(int argc, const char* const argv[]) {
    const char* inputFileName = argc > 1 ? argv[1] : "input.txt";

    std::ifstream source(inputFileName);
    if (!source.is_open()) {
        std::cerr << "Can't open source file\n";
    }

    std::ofstream res("result.txt");
    std::cout << "Completed" << std::endl;

    analyser(source, res);
    
    source.close();
    res.close();

    return 0;
}
