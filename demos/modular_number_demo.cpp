#include <iostream>

#include "../src/common.hpp"
#include "../src/modular_number.hpp"

int main() {
    using ULL = unsigned long long;

    FT::ModularNumber<ULL> res;

    {
        using namespace FT;

        ModularNumber<ULL> num1 = 4_mo;
        ModularNumber<ULL> num2 = 6_mo;

        res = num1 * num2;

        std::cout << "Number: " << ULL(res) << ";" << std::endl;

        std::cout << "Remainders: ";
        std::vector<int> remainders = res.getRemainders();
        for (int i = 0; i < remainders.size(); ++i) {
            std::cout << " " << remainders[i];
        }
        std::cout << ";" << std::endl;
    }

    return 0;
}