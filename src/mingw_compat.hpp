#pragma once

#if defined(__MINGW32__)
#include <time.h>

#ifndef TIME_UTC
#define TIME_UTC 1
#endif

// Forward declarations to satisfy libstdc++ using-declarations
extern "C" {
        int timespec_get(struct timespec* ts, int base);
        int at_quick_exit(void (*func)(void));
        void quick_exit(int status);
}
#endif
