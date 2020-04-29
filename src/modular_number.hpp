namespace FT {
    template <typename UI,
              class = typename std::enable_if<std::is_integral<UI>::value && std::is_unsigned<UI>::value>::type>
    class ModularNumber {
    public:
        using Type = UI;

        ModularNumber() {
            remainders.resize(moduli.size());
            calculateProduct();
        }

        ModularNumber(const Type& val) {
            remainders.resize(moduli.size());
            calculateProduct();

            for (int i = 0; i < moduli.size(); ++i) {
                remainders[i] = val % moduli[i];
            }
        }

        operator Type() {
            std::vector<unsigned long long> M(moduli.size());
            for (int i = 0; i < moduli.size(); ++i) {
                M[i] = moduliProduct / moduli[i];
            }

            std::vector<int> B(moduli.size());
            for (int i = 0; i < moduli.size(); ++i) {
                int b = 1;

                while ((M[i] * b) % moduli[i] != 1) b++;

                B[i] = b;
            }

            unsigned long long sum = 0;
            for (int i = 0; i < moduli.size(); ++i) {
                sum += remainders[i] * M[i] * B[i];
            }

            return sum % moduliProduct;
        }

        std::vector<int> getRemainders() const {
            return remainders;
        }

        ModularNumber& operator=(const ModularNumber& num) {
            remainders = num.remainders;
        }

        ModularNumber operator*(const ModularNumber& val) {
            ModularNumber res;

            for (int i = 0; i < moduli.size(); ++i) {
                res.remainders[i] = (remainders[i] * val.remainders[i]) % moduli[i];
            }

            return res;
        }

    private:
        void calculateProduct() {
            moduliProduct = 1;
            for (int i = 0; i < moduli.size(); ++i) {
                moduliProduct *= moduli[i];
            }
        }

        const std::vector<int> moduli = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53}; // max 8-byte
        unsigned long long moduliProduct; // ??? ull not enough
        
        std::vector<int> remainders;
    };

    ModularNumber<unsigned long long> operator"" _mo(const ModularNumber<unsigned long long>::Type val) {
        return ModularNumber<unsigned long long>(val);
    }
}