#ifndef DEBUG_UTIL
#define DEBUG_UTIL

#ifdef NDEBUG
    #define DEBUG_PRINT(x)
#else
    #define DEBUG_PRINT(x) std::cout << x << std::endl;
#endif //NDEBUG

#endif //DEBUG_UTIL