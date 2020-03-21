namespace FT {
    enum class ErrorStatus {
        noError,
        caughtError
    };

    // template<typename T>
    // inline T abs(const T& op) {
    //     return (op > 0 ? op : -op);
    // }
    
    template<typename T>
    T mult(const T& op1, const T& op2, ErrorStatus& err) {
        T tmp1 = op1 * op2;
        T op2_inc = op2 + 1;
        T tmp2 = op1 * op2_inc;
        T tmp3 = (tmp2 - tmp1);
        T res = tmp3 - op1;
        if (res != 0) {
            err = ErrorStatus::caughtError;
            return tmp1 + res;
        }
        err = ErrorStatus::noError;
        return tmp1;
    }

    template<typename T>
    T div(const T& op1, const T& op2, ErrorStatus& err) {
        T c1 = op1/op2;
        T c2 = (op1+1) / op2;
        T tmp = (c2 - c1);
        T res = tmp - 1/op2;
        if(res != 0) {
            err = ErrorStatus::caughtError;
            return c1+res;
        }
        err = ErrorStatus::noError;
        return c1;
    }

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
        T tmp2 = tmp1 ^ tmp1;

        if (tmp2 != 0) {
            err = ErrorStatus::caughtError;
            return (tmp1 ^ tmp2);
        }

        err = ErrorStatus::noError;
        return tmp1;
    }

    template<typename T>
    T land(const T& op1, const T& op2, ErrorStatus& err) {
        T cnj1 = (op1) & (op2);
        T tmp1 = (op1) & (~(op2));
        tmp1 = tmp1 | cnj1;
        tmp1 = tmp1 ^ op1;

        if(tmp1 != 0) {
            err = ErrorStatus::caughtError;
            return ((cnj1 ^ tmp1));
        }
        err = ErrorStatus::noError;
        return cnj1;
    }
}