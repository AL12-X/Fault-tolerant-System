namespace FT {
    enum class ErrorStatus {
        noError,
        withError
    };
    
    template<typename T>
    T mult(const T& op1, const T& op2, ErrorStatus& err) {
        T res = op1 * op2; // checked and corrected
        T tmp = op1 * (op2 + 1) - res - op1;
        if (tmp != 0) {
            err = ErrorStatus::withError;
            return res + tmp;
        }
        err = ErrorStatus::noError;
        return res;
    }

    template<typename T>
    T div(const T& op1, const T& op2, ErrorStatus& err) {
        T res = op1 / op2; // checked and corrected
        T tmp = (op1 + 1) / op2 - res - 1 / op2;
        if (tmp != 0) {
            err = ErrorStatus::withError;
            return res + tmp;
        }
        err = ErrorStatus::noError;
        return res;
    }

    template<typename T>
    T lNot(const T& op, ErrorStatus& err) {
        T res = ~op; // checked and corrected
        T tmp = (op ^ res) ^ -1;
        if (tmp != 0) {
            err = ErrorStatus::withError;
            return res ^ tmp;
        }
        err = ErrorStatus::noError;
        return res;
    }

    template<typename T>
    T lXor(const T& op1, const T& op2, ErrorStatus& err) {
        T res = op1 ^ op2; // checked and corrected
        T tmp = res ^ res;
        if (tmp != 0) {
            err = ErrorStatus::withError;
            return res ^ tmp;
        }
        err = ErrorStatus::noError;
        return res;
    }

    // NOT WORKING =======================================
    template<typename T>
<<<<<<< HEAD
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
=======
    T lAnd(const T& op1, const T& op2, ErrorStatus& err) {
        T res = op1 & op2; // checked and corrected
        T tmp = ((op1 & ~op2) | res) ^ op1;
        if (tmp != 0) {
            err = ErrorStatus::withError;
            return res ^ tmp;
        }
        err = ErrorStatus::noError;
        return res;
>>>>>>> 595d334b53d1ea3465b06a89d8f4778696c4cb9c
    }
}