namespace FT {
    enum class ErrorStatus {
        noError,
        caughtError
    };

    template<typename T>
    inline T abs(const T& op) {
        return (op > 0 ? op : -op);
    }
    
    template<typename T>
    T mult(const T& op1, const T& op2, ErrorStatus& err) {
        T tmp1 = op1 * op2;
        T op2_inc = op2 + 1;
        T tmp2 = op1 * op2_inc;
        T tmp3 = abs(tmp2 - tmp1);
        T res = tmp3 - op1;
        
        if (res != 0) {
            err = ErrorStatus::caughtError;
            if (tmp2 - tmp1 > 0) {
                return tmp1 + res;
            }

            return tmp1 - (tmp3 + op1);
        }

        err = ErrorStatus::noError;
        return tmp1;
    }

    // template<typename T>
    // T div(const T& op1, const T& op2, int& err) {
    //     T c1 = a / b;
    //     T c2 = (a + b) / b;
    //     if(c2 - c1 != 1) {
    //         std::cout << "Not equal\n";
    //         return;
    //     }
    //     std::cout << "Equal\n";
    // }

    template<typename T>
    T lnot(const T& op1, ErrorStatus& err) {
        T tmp1 = ~op1;
        T tmp2 = op1 ^ tmp1;
        tmp2 ^= -1;

        if (tmp2 != 0) {
            err = ErrorStatus::caughtError;
            return (tmp1 ^ tmp2);
        }

        err = ErrorStatus::noError;
        return tmp1;
    }

    template<typename T>
    T lxor(const T& op1, const T& op2, ErrorStatus& err) {
        T tmp1 = op1 ^ op2;
        T tmp2 = op1 ^ op2 ^ tmp1;

        if (tmp2 != 0) {
            err = ErrorStatus::caughtError;
            return tmp1 ^ tmp2;
        }

        err = ErrorStatus::noError;
        return tmp1;
    }

    // template<typename T>
    // T land(const T& op1, const T& op2, int& errcode) {
    //     T cnj = op1 & op2;
    //     T tmp = op1 & (~op2);
    //     tmp = tmp | cnj;
    //     tmp = op1 ^ tmp;
    //     return tmp;
    // }
}