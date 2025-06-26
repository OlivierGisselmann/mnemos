#pragma once

#ifndef NDEBUG

#define ASSERT(expr)                                                \
    do {                                                            \
        if (!(expr)) {                                              \
            std::cerr << "Assertion failed: (" << #expr << "), "    \
                      << "function " << __FUNCTION__                \
                      << ", file " << __FILE__                      \
                      << ", line " << __LINE__ << "." << std::endl; \
            std::abort();                                           \
        }                                                           \
    } while (0)                                                     \

#else

#define ASSERT(expr)

#endif