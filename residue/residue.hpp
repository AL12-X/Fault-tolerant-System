#include <iostream>
#include <vector>

class ResidueULLInt {
public:
    using Type = unsigned long long int;

    ResidueULLInt() = default;

    ResidueULLInt(const Type& val) {
        for (const auto& mod: moduli) {
            remainders.push_back(val % mod);
        }
    }

    operator Type() {
        // remainders -> number

        // Пример: пусть задана система модулей (3, 5, 7), найдем значения Mi и bi (0 < i <= 3)
        // M = 3*5*7 = 105
        // M1 = 105/3 = 35
        // M2 = 105/5 = 21
        // M3 = 105/7 = 15
        // (35*b1)%3 = 1 => b1 = 2
        // (21*b2)%5 = 1 => b2 = 1
        // (15*b3)%7 = 1 => b3 = 1
        // Теперь преобразуем какое-нибудь число в системе остаточных классов. Положим 
        // X = (2, 3, 1) = (2*35*2 + 3*21*1 + 1*15*1)%105 = (140 + 63 + 15)%105 = 218%105 = 8

        return Type(); 
    }

    void printRemainders() {
        for (const auto& rem: remainders) {
            std::cout << rem << " ";
        }
        std::cout << std::endl;
    }

    ResidueULLInt operator*(const ResidueULLInt& val) {
        ResidueULLInt res;

        for (size_t i = 0; i < remainders.size(); ++i) {
            res.remainders.push_back((remainders[i] * val.remainders[i]) % moduli[i]);
        }

        return res;
    }

    static const std::vector<int> moduli;

private:
    std::vector<int> remainders;
};

const std::vector<int> ResidueULLInt::moduli({2, 3, 5, 7, 11, 13, 17, 19, 23, 29}); // Moduli list for int



ResidueULLInt operator"" _re(const ResidueULLInt::Type val) {
    return ResidueULLInt(val);
}