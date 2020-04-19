namespace FT {
    template<typename I, class = typename std::enable_if<std::is_integral<I>::value>::type>
    I mult(const I& op1, const I& op2, ErrorStatus& err) {
        I res = op1 * op2; // checked and corrected
        I tmp = op1 * (op2 + 1) - res - op1;
        if (tmp != 0) {
            err = ErrorStatus::corrected;
            return res + tmp;
        }
        err = ErrorStatus::notOccurred;
        return res;
    }

    template<typename I, class = typename std::enable_if<std::is_integral<I>::value>::type>
    I div(const I& op1, const I& op2, ErrorStatus& err) {
        I res = op1 / op2; // checked and corrected
        I tmp = (op1 + 1) / op2 - res - 1 / op2;
        if (tmp != 0) {
            err = ErrorStatus::corrected;
            return res + tmp;
        }
        err = ErrorStatus::notOccurred;
        return res;
    }

    template<typename I, class = typename std::enable_if<std::is_integral<I>::value>::type>
    I lNot(const I& op, ErrorStatus& err) {
        I res = ~op; // checked and corrected
        I tmp = (op ^ res) ^ -1;
        if (tmp != 0) {
            err = ErrorStatus::corrected;
            return res ^ tmp;
        }
        err = ErrorStatus::notOccurred;
        return res;
    }
}