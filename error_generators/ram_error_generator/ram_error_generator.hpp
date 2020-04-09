#include <iostream>
#include <thread>
#include <climits>
#include <mutex>
#include <stdlib.h>     /* srand, rand */

enum class ErrorType {
    randomBitFlip
};

std::mutex mutex;

template<typename T>
void ramErrorGenerator(ErrorType errType, T* ptr, int size, int numIterations, int period, bool enableLogging) {
    for (int i = 0; i < numIterations; ++i) {
        switch (errType) {
            case ErrorType::randomBitFlip:
                int typeSizeInBits = sizeof(T) * CHAR_BIT;
                int erroneousBitIndex = rand() % (typeSizeInBits * size);
                int elementIndex = erroneousBitIndex / typeSizeInBits;
                int offsetInElement = erroneousBitIndex % typeSizeInBits;
                
                ptr[elementIndex] ^= (1 << offsetInElement);

                if (enableLogging) {
                    std::lock_guard<std::mutex> lock(mutex);

                    std::cout << "[RAM error on addr " << (ptr + offsetInElement)
                        << " (element " << elementIndex << ", bit " << (typeSizeInBits - offsetInElement)
                        << ")]" << std::endl;
                }
                break;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(period));
    }
}