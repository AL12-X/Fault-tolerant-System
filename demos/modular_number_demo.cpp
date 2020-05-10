#include <iostream>

#include "../src/common.hpp"
#include "../src/modular_number.hpp"

int main() {
    using namespace FT;
    using ULL = unsigned long long;

    ModularNumber<ULL> num1 = 4635_mo;
    ModularNumber<ULL> num2 = 1154_mo;
    FT::ModularNumber<ULL> res = num1 * num2;

    std::cout << "Operand 1: " << num1 << std::endl;
    std::cout << "Operand 2: " << num2 << std::endl;
    std::cout << "Result: " << ULL(res) << std::endl;

    std::cout << std::endl;
    std::cout << "Remainders: ";
    std::vector<int> remainders = res.getRemainders();
    for (int i = 0; i < remainders.size(); ++i) {
        std::cout << " " << remainders[i];
    }
    std::cout << ";" << std::endl;

    return 0;
}