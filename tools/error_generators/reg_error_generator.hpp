namespace FT::tools {
    #ifdef _ARCH_x64
        register int rax asm("rax");
        register int rbx asm("rbx");
        register int rcx asm("rcx");
        // register int rdx asm("rdx");
        
        // register int rsi asm("rsi");
        // register int rdi asm("rdi");
        register int rsp asm("rsp");
        // register int rbp asm("rbp");
        
        // register int r8 asm("r8");
        // register int r9 asm("r9");
        // register int r10 asm("r10");
        // register int r11 asm("r11");
        // register int r12 asm("r12");
        // register int r13 asm("r13");
        // register int r14 asm("r14");
        // register int r15 asm("r15");
    #endif

    class RegErrorGenerator {
    public:
        RegErrorGenerator() = delete;

        RegErrorGenerator(std::mutex& mtx, bool logging, std::ostream& out = std::cout)
                         : eng(rd()), mutex(mtx), os(out) {
            enableLogging = logging;
        }

        // TODO: try __asm("mov %eax, 3");

        void run(RegErrorType errType, int maxRange, int numIterations, int timeIdle) {
            std::uniform_int_distribution<> valueDistr(-maxRange, maxRange-1);
            std::uniform_int_distribution<> regIdxDistr(0, 2);

            for (int i = 0; i < numIterations; ++i) {
                int randValue;

                switch (errType) {
                    case RegErrorType::stackPointer:
                        randValue = valueDistr(eng);

                        if (enableLogging) {
                            std::lock_guard<std::mutex> lock(mutex);
                            os << "Generated: [Stack pointer register error with value " << randValue <<"]\n";
                        }

                        rsp += randValue;
                        break;
                    case RegErrorType::randomArithmeticDev:
                        randValue = valueDistr(eng);
                        int randReg = regIdxDistr(eng);

                        if (enableLogging) {
                            std::lock_guard<std::mutex> lock(mutex);
                            os << "Generated: [Arithmetic register error on register " << randReg
                               << " with value " << randValue << "]\n";
                        }

                        switch (randReg) {
                            case 0: rax += randValue; break;
                            case 1: rbx += randValue; break;
                            case 2: rcx += randValue; break;
                            //case 3: rdx += randValue; break;
                        }
                        break;
                }

                std::this_thread::sleep_for(std::chrono::microseconds(timeIdle));
            }
        }

    private:
        std::random_device rd;
        std::mt19937 eng;
        std::mutex& mutex;
        bool enableLogging;
        std::ostream& os;
    };
}
