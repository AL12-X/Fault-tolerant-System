#include <iostream>
#include <thread>
#include <random>
#include <mutex>

namespace FT::tools {
    #define _ARCH_x64

    enum RamErrorType {
        randomBitFlip
    };

    enum RegErrorType {
        randomArithmeticDev,
        stackPointer
    };
}