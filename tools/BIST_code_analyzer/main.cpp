#include <iostream>
#include "analyzer.hpp"

int main(int argc, const char* const argv[]) {
    // TODO:
    //    if (argc < 2){
    //        std::cerr << "Not enough arguments\n";
    //    }

    std::ifstream source("input.txt");
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
