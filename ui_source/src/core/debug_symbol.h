#ifndef __DEBUG_SYMBOL__
#define __DEBUG_SYMBOL__

#if ENABLE_LOGGING == ON

// 颜色宏定义
#define C_COLOR_RESET "\033[0m"

#define CTEXT_BLACK "\033[30m"
#define CTEXT_RED "\033[31m"
#define CTEXT_GREEN "\033[32m"
#define CTEXT_YELLOW "\033[33m"
#define CTEXT_BLUE "\033[34m"
#define CTEXT_MAGENTA "\033[35m"
#define CTEXT_CYAN "\033[36m"
#define CTEXT_WHITE "\033[37m"

#define CBACK_BLACK "\033[40m"
#define CBACK_RED "\033[41m"
#define CBACK_GREEN "\033[42m"
#define CBACK_YELLOW "\033[43m"
#define CBACK_BLUE "\033[44m"
#define CBACK_MAGENTA "\033[45m"
#define CBACK_CYAN "\033[46m"
#define CBACK_WHITE "\033[47m"

#include <iostream>

#define LOG_PRINT(...)                                                         \
  std::cout << CTEXT_GREEN << "LOG:   " << CTEXT_MAGENTA;                      \
  log_print(__VA_ARGS__);                                                      \
  std::cout << C_COLOR_RESET << std::endl;

#define INFO_PRINT(...)                                                        \
  std::cout << CTEXT_GREEN << "INFO:  ";                                       \
  log_print(__VA_ARGS__);                                                      \
  std::cout << C_COLOR_RESET << std::endl;

#define DEBUG_PRINT(...)                                                       \
  std::cout << CTEXT_BLUE << "DEBUG: " << CTEXT_YELLOW << ":\t"                \
            << C_COLOR_RESET;                                                  \
  log_print(__VA_ARGS__);                                                      \
  std::cout << std::endl;

#define ERROR_PRINT(...)                                                       \
  std::cout << CTEXT_RED << "ERROR: " << CTEXT_MAGENTA << ":\t";               \
  log_print(__VA_ARGS__);                                                      \
  std::cout << C_COLOR_RESET << std::endl;

template <typename... Args> void log_print(const Args &...args) {
  ((std::cout << args << " "), ...);
}
#else
#define LOG_PRINT(...) ((void)0)
#define DEBUG_PRINT(...) ((void)0)
#define ERROR_PRINT(...) ((void)0)
#define INFO_PRINT(...) ((void)0)
#endif

#endif // __DEBUG_SYMBOL__