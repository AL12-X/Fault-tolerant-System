// Use only for single-thread execution.
// The implementation with thread support will include global mutex, and therefore result in reduced performance.

namespace FT {

    // Add functions here
    enum class Function {
        none,
        main,
        foo,
        bar
    };

    static Function currentFunction = Function::none;
}