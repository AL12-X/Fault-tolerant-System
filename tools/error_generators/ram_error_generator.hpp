#include <climits>
#include <stdlib.h>

#include "../tools_common.hpp"

namespace FT::tools {
    class RamErrorGenerator {
    public:
        RamErrorGenerator() = delete;

        RamErrorGenerator(void* startPtr, int size, std::mutex& mtx, bool logging, std::ostream& out = std::cout)
                         : eng(rd()), mutex(mtx), os(out) {
            rangeStartPtr = startPtr;
            rangeSize = size;
            enableLogging = logging;
        }

        void run(RamErrorType errType, int numIterations, int timeIdle) {
            std::uniform_int_distribution<> valueDistr(0, CHAR_BIT * rangeSize - 1);

            for (int i = 0; i < numIterations; ++i) {
                switch (errType) {
                    case RamErrorType::randomBitFlip:
                        char* charPtr = (char*)rangeStartPtr;
                        int erroneousBitIndex = valueDistr(eng);
                        int elementIndex = erroneousBitIndex / CHAR_BIT;
                        int offsetInElement = erroneousBitIndex % CHAR_BIT;

                        charPtr[elementIndex] ^= (1 << offsetInElement);

                        if (enableLogging) {
                            std::lock_guard<std::mutex> lock(mutex);

                            os << "Generated: [RAM error on address " << static_cast<void*>(charPtr + elementIndex)
                               << " in bit " << (CHAR_BIT - offsetInElement - 1)
                               << "]\n";
                        }
                        break;
                }

                std::this_thread::sleep_for(std::chrono::microseconds(timeIdle));
            }
        }

    private:
        std::random_device rd;
        std::mt19937 eng;
        void* rangeStartPtr;
        int rangeSize;
        std::mutex& mutex;
        bool enableLogging;
        std::ostream& os;
    };
}
