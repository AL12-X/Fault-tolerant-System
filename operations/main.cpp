#include <iostream>
#include <math.h>

template <typename T>
void ft_mul(const T& a, const T& b, const T& param) {
    T tmp = a * b;
    T tmp_s = (a % param) * (b % param);
    if(tmp_s%param != tmp%param) {
        std::cout << "Not equal\n";
        return;
    }
    std::cout << "Equal\n";
    return;
}

template <typename T>
void ft_mul_ult(const T& a,const T& b) {
    T c1 = a * b;
    T c2 = a * (b + 1);
    T c = std::abs(c2 - c1);
    c = c - a;
    if(c != 0) {
        std::cout << "Not equal\n";
        return;
    }
    std::cout << "Equal\n";

}

template <typename T>
void ft_sub(const T& a, const T& b) {
    T c1 = a / b;
    T c2 = (a + b) / b;
    if(c2 - c1 != 1) {
        std::cout << "Not equal\n";
        return;
    }
    std::cout << "Equal\n";
}

#include <bitset>

template <typename T>
T ft_inv(const T& a, const T& b) {
    T tmp = a ^ b;
    std::bitset<sizeof(T)*8> bit_mask1;
    T ch = -1;
    tmp = tmp^ch;
    return tmp;
}

template <typename T>
T ft_xor(const T& a, const T& b) {
    T tmp = a^b;
    tmp = tmp^a^b;
    if(tmp != 0) {
        std::cout << "Not equal!\n";
    }
    else {
        std::cout << "Equal!\n";
    }
    return tmp;
}

int main() {
    int a = 3234;
    int b = 8521;
    const int p = 754;

    ft_mul(a, b, p);
    ft_mul_ult(a, b);
    ft_sub(b, a);
    return 0;
}