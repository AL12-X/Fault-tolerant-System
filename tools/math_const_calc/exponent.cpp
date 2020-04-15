/*
as FT-lib tool



Pi:
Gauss–Legendre      https://en.wikipedia.org/wiki/Gauss%E2%80%93Legendre_algorithm
Machin-like formula https://en.wikipedia.org/wiki/Machin-like_formula
*/


#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

int main() {
    const std::string e_real = "2.71828182845904523536028747135266249775724709369995";

    //длинная арифметика
    unsigned long long factorial = 1;
    unsigned long long nextNumber = 2;
    long double e = 1;
    const int numIterations = 60;

    for (int i = 0; i < numIterations; i++) {
        e += 1.0 / factorial;
        factorial *= nextNumber;
        nextNumber++;
    }

    std::stringstream stream;
    stream.precision(std::numeric_limits<long double>::max_digits10);
    stream << e;
    std::string e_res = stream.str();

    std::cout << "e        = " << e_real << std::endl;
    std::cout << "result e = " << e_res << std::endl;
    // first error?

    return 0;
}