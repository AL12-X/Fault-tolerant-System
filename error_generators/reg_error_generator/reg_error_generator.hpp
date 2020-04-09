#include <iostream>
#include <thread>

enum class ErrorType {
    randomArithmeticDev,
    stackPointer
};

int getRand(int range) {
    return rand() % (2 * range) - range;
}

void registerErrorGenerator(ErrorType errType, int maxRange, int numIterations, int period, bool enableLogging) {
    // x64 Registers
    register int rax asm("rax");
    register int rbx asm("rbx");
    register int rcx asm("rcx");
    register int rdx asm("rdx");
    register int rsi asm("rsi");
    register int rdi asm("rdi");
    register int rsp asm("rsp");
    register int rbp asm("rbp");
    register int r8 asm("r8");
    register int r9 asm("r9");
    register int r10 asm("r10");
    register int r11 asm("r11");
    register int r12 asm("r12");
    register int r13 asm("r13");
    register int r14 asm("r14");
    register int r15 asm("r15");

    for (int i = 0; i < numIterations; ++i) {
        switch (errType) {
            case ErrorType::stackPointer:
                if (enableLogging) std::cout << "[Stack pointer register error]" << std::endl;
                rsp += getRand(maxRange);
                break;
            case ErrorType::randomArithmeticDev:
                int erroneousRegisterIndex = rand() % 4;
                if (enableLogging) std::cout << "[Arithmetic register error]" << std::endl;
                switch (erroneousRegisterIndex) {
                    case 0: rax += getRand(maxRange); break;
                    case 1: rbx += getRand(maxRange); break;
                    case 2: rcx += getRand(maxRange); break;
                    case 3: rdx += getRand(maxRange); break;
                }
                break;
        }

        std::this_thread::sleep_for(std::chrono::microseconds(period));
    }
}

// TODO:
//      x86 only
//      int eax, ebx, ecx, edx;
//      eax = 1;
//      __asm( "cpuid"
//          : "+a" (eax), "+b" (ebx), "+c" (ecx), "+d" (edx));
//      int buffer = edx;
//      std::cout << "Buffer: " << buffer << std::endl;