#include <type_traits>
#include <thread>
#include <vector>

namespace FT {
    enum ErrorStatus {
        notOccurred,
        corrected,
        fatal
    };

    template<typename T>
    T compare(std::vector<T> values, ErrorStatus* err) {
        if (values[0] == values[1]) {
            *err = (values[0] == values[2]) ? ErrorStatus::notOccurred : ErrorStatus::corrected;
            return values[0];
        }

        if (values[1] == values[2]) {
            *err = (values[1] == values[0]) ? ErrorStatus::notOccurred : ErrorStatus::corrected;
            return values[1];
        }

        if (values[2] == values[0]) {
            *err = (values[2] == values[1]) ? ErrorStatus::notOccurred : ErrorStatus::corrected;
            return values[2];
        }

        *err = ErrorStatus::fatal;
        return T();
    }
}