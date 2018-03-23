#ifndef DEFINEOS_H
#define DEFINEOS_H

#ifdef __unix__
    #define OS_LINUX
#elif defined(_WIN32) || defined(WIN32)
    #define OS_WINDOWS
#endif

#endif // DEFINEOS_H
