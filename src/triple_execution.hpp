namespace FT {
    template<typename T_ret, typename... T_arg>
    T_ret execSubsequent(void func(T_ret*, T_arg...), ErrorStatus* err, T_arg... args) {
        std::vector<T_ret> results(3);

        for (int i = 0; i < 3; ++i) {
            func(&(*results.begin()) + i, args...);
        }

        return FT::compare(results, err);
    }

    template<typename T_ret, typename... T_arg>
    T_ret execParallel(void func(T_ret*, T_arg...), ErrorStatus* err, T_arg... args) {
        std::vector<T_ret> results(3);
        
        std::vector<std::thread> threads;
        for (int i = 0; i < 3; ++i) {
            threads.push_back(std::thread(func, &(*results.begin()) + i, args...));
        }
        for (auto& thread: threads) {
            thread.join();
        }

        return FT::compare(results, err);
    }
}
