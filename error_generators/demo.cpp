#include "ram_error_generator/ram_error_generator.hpp"

int main() {
    srand(time(NULL));

    const int kArrSize = 5;
    typedef int ArrElementType;

    ArrElementType* arr = new ArrElementType[kArrSize];
    for (int i = 0; i < kArrSize; i++) {
        arr[i] = i;
    }

    std::thread t1(ramErrorGenerator<ArrElementType>, ErrorType::randomBitFlip, arr, kArrSize, 10, 1, true);

    for (int i = 0; i < 20; i++) {
        std::lock_guard<std::mutex> lock(mutex);

        std::cout << "Arr: ";
        for (int i = 0; i < kArrSize; i++) {
            std::cout << arr[i] << " ";
        }

        std::cout << std::endl;
    }

    t1.join();

    return 0;
}