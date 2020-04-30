#include <iomanip>

#include "../tools/error_generators/ram_error_generator.hpp"

int main() {
    const int kArrSize = 30;
    char* charArr = new char[kArrSize];
    for (int i = 0; i < kArrSize; i++) {
        charArr[i] = 1;
    }

    std::mutex mutex;
    FT::tools::RamErrorGenerator errGen((void*)charArr, kArrSize, mutex, true, std::cout);
    std::thread t1(&FT::tools::RamErrorGenerator::run, &errGen, FT::tools::RamErrorType::randomBitFlip, 10, 0);

    std::cout.fill(' ');
    for (int i = 0; i < 20; i++) {
        std::lock_guard<std::mutex> lock(mutex);

        std::cout << " Bytes:";
        for (int i = 0; i < kArrSize; i++) {
            std::cout << " " << std::setw(3) << int(charArr[i]);
        }
        std::cout << ";" << std::endl;
    }

    t1.join();

    std::cout << "Result:";
    for (int i = 0; i < kArrSize; i++) {
        std::cout << " " << std::setw(3) << int(charArr[i]);
    }
    std::cout << ";" << std::endl;

    return 0;
}