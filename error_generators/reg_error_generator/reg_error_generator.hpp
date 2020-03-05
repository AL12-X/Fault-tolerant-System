// gcc -ffixed-ebx

#include <string>
#include <iostream>
#include <thread>
#include <map>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// enum class x64_Register : char {
//     register int counter asm(errReg);
//     // rax,
//     // rcx,
//     // rdx,
//     // rbx,
//     // rsi,
//     // rdi,
//     // rsp,
//     // rbp,
//     // r8,
//     // r9,
//     // r10,
//     // r11,
//     // r12,
//     // r13,
//     // r14,
//     // r15
// };

// std::map<x64_Register, const char*> x64_RegisterMap = {
//     { x64_Register::rax, "rax" },
//     { x64_Register::rcx, "rcx" },
//     { x64_Register::rdx, "rdx" },
//     { x64_Register::rbx, "rbx" },
//     { x64_Register::rsi, "rsi" },
//     { x64_Register::rdi, "rdi" },
//     { x64_Register::rsp, "rsp" },
//     { x64_Register::rbp, "rbp" },
//     { x64_Register::r8, "r8" },
//     { x64_Register::r9, "r9" },
//     { x64_Register::r10, "r10" },
//     { x64_Register::r11, "r11" },
//     { x64_Register::r12, "r12" },
//     { x64_Register::r13, "r13" },
//     { x64_Register::r14, "r14" },
//     { x64_Register::r15, "r15" }
// };

// int registerCount = 4;
// register int rax asm("rax");
// register int rbx asm("rbx");
// register int rcx asm("rcx");
// register int rdx asm("rdx");

void regInc() {
    // const char* errReg = x64_RegisterMap[x64_Register(rand() % x64_RegisterMap.size())];
    // std::cout << "Err reg: " << errReg << std::endl;

    register int counter asm("rsp");
    counter = 0;
    
    for (int i = 0; i < 10; i++) {
        counter++;
    }
}

int main() {
    // x86 only
    // int eax, ebx, ecx, edx;
    // eax = 1;
    // __asm( "cpuid"
    //     : "+a" (eax), "+b" (ebx), "+c" (ecx), "+d" (edx));
    // int buffer = edx;
    // std::cout << "Buffer: " << buffer << std::endl;

    srand(time(NULL));

    std::thread t1(regInc);    

    int counter = 0;
    for (int i = 0; i < 100; ++i) {
        counter++;
        std::cout << counter << std::endl;
    }
    //std::cout << "Size: " << sizeof(counter) << std::endl;

    t1.join();

    return 0;
}
