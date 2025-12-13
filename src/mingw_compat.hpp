#pragma once

#if defined(__MINGW32__)
#include <time.h>

// Forward declarations to satisfy libstdc++ using-declarations
extern "C" {
        int timespec_get(struct timespec* ts, int base);
        int at_quick_exit(void (*func)(void));
        void quick_exit(int status);
}
#endif
