#ifndef PRINT_UTILS
#define PRINT_UTILS

// Günter Kolousek, 2016

extern std::recursive_mutex out_mtx;

void println();

template<typename T, typename... Rest>
void println(const T& word, const Rest&... rest) {
    std::lock_guard<std::recursive_mutex> lg{out_mtx};
    std::cout << word << ' ';
    println(rest...);
}
#endif
