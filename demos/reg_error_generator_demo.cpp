// Flags: -w -ffixed-edx -fomit-frame-pointer

#include "../tools/tools_common.hpp"
#include "../tools/error_generators/reg_error_generator.hpp"

int main() {
    std::mutex mutex;
    FT::tools::RegErrorGenerator errGen(mutex, true, std::cout);
    std::thread t1(&FT::tools::RegErrorGenerator::run, &errGen, FT::tools::RegErrorType::randomArithmeticDev,
                   16, 10, 0);

    int counter = 0;
    for (int i = 0; i < 100; ++i) {
        std::lock_guard<std::mutex> lock(mutex);

        counter++;
        std::cout << "Count: " << counter << std::endl;
    }

    t1.join();

    return 0;
}