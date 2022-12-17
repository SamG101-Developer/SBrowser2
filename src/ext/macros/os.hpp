#ifndef SBROWSER2_OS_HPP
#define SBROWSER2_OS_HPP


#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__) && !defined(_WIN32)
    #define OS_WINDOWS
#elif defined(__ANDROID__)
    #define OS_ANDROID
#elif defined(__linux__)
    #define OS_LINUX
#elif defined(__unix__) || !defined(__APPLE__) && defined(__MACH__)
    #include <sys/param.h>
    #if defined(BSD)
        #define OS_BSD
    #endif
#elif defined(__hpux)
    #define OS_HPUX
#elif defined(_AIX)
    #define OS_AIX
#elif defined(__APPLE__) && defined(__MACH__)
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR == 1 || TARGET_OS_IPHONE == 1
        #define OS_IOS
    #elif TARGET_OS_MAC == 1
        #define OS_OSX
    #endif
#elif defined(__sun) && defined(__SVR4)
    #define OS_SOLARIS
#else
    #define OS_UNKNOWN
#endif


#endif //SBROWSER2_OS_HPP
