#include <iostream>

#include "../thirdparty/bigint/bigint.cpp"

int main() {
    Dodecahedron::Bigint base = 42;
    std::cout << base.pow(42069) << std::endl;

    return 0;
}