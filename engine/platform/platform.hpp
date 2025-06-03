#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(_WIN32_) || defined(__NT__)
    #define MNEMOS_PLATFORM_WIN32
#elif defined(__linux__) || defined(__linux) || defined(_linux_)
    #define MNEMOS_PLATFORM_LINUX
#endif
