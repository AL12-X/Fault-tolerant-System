#include <sched.h>

namespace FT {
    template<typename T_ret, typename... T_arg>
    T_ret runOn2Cores(void func(T_ret*, T_arg...), ErrorStatus* err, T_arg... args) {
        const auto cpuCoresQty = std::thread::hardware_concurrency();

        if (cpuCoresQty == 0) {
            throw std::runtime_error("Can't detect the number of cores");
        }
        if (cpuCoresQty < 2) {
            throw std::runtime_error("The CPU has less than 2 cores");
        }

        std::vector<T_ret> results(2);
        cpu_set_t mask;

        CPU_ZERO(&mask);
        CPU_SET(0, &mask);
        sched_setaffinity(0, sizeof(mask), &mask);
        func(&(*results.begin()), args...);

        CPU_ZERO(&mask);
        CPU_SET(1, &mask);
        sched_setaffinity(0, sizeof(mask), &mask);
        func(&(*results.begin()) + 1, args...);

        if (results[0] == results[1]) {
            *err = ErrorStatus::notOccurred;
            return results[0];
        } else {
            *err = ErrorStatus::fatal;
            return T_ret();
        }
    }
}