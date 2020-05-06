#include <iostream>
#include "analyser.h"
int main(int argc, const char* const argv[]) {
    //    if (argc < 2){
    //        std::cerr << "Not enough arguments\n";
    //    }
    std::ifstream source("Analyser.h");
    if (!source.is_open()) {
        std::cerr << "Can't open source file\n";
    }
    std::ofstream res("result.cpp");
    std::cout << '#';
    analyser(source, res);
    source.close();
    res.close();
    return 0;
}
