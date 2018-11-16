#pragma once
#include <iostream>
#include <mutex>
namespace Utils
{
extern std::recursive_mutex out_mtx;

inline void println()
{
  std::lock_guard<std::recursive_mutex> lg{out_mtx};
  std::cout << std::endl; 
}

template <typename T, typename... Rest>
void println(const T &word, const Rest &... rest)
{
  std::lock_guard<std::recursive_mutex> lg{out_mtx};
  std::cout << word << ' ';
  println(rest...);
}

} // namespace Utils
