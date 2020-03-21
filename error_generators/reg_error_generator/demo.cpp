// -ffixed-ebx -pthread

#include <time.h>       /* time */

#include "reg_error_generator.hpp"

int main() {
    srand(time(NULL));

    std::thread t1(registerErrorGenerator, ErrorType::randomArithmeticDev, 16, 10, 0, true);    

    int counter = 0;
    for (int i = 0; i < 1000; ++i) {
        counter++;
        std::cout << "Count: " << counter << std::endl;
    }

    t1.join();

    return 0;
}