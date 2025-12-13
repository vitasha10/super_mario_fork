#if defined(__MINGW32__)
#include "mingw_compat.hpp"

#include <chrono>
#include <cstdlib>
#include <windows.h>

extern "C" {
int __attribute__((weak)) timespec_get(struct timespec* ts, int base) {
        if (ts == nullptr || base != TIME_UTC) {
                return 0;
        }

        using namespace std::chrono;
        const auto now = system_clock::now();
        const auto sec = time_point_cast<seconds>(now);
        ts->tv_sec = static_cast<time_t>(sec.time_since_epoch().count());
        ts->tv_nsec = static_cast<long>(
                duration_cast<nanoseconds>(now - sec).count()
        );
        return base;
}

static void (*g_quick_exit_handler)(void) = nullptr;

int __attribute__((weak)) at_quick_exit(void (*func)(void)) {
        g_quick_exit_handler = func;
        return 0;
}

void __attribute__((weak)) quick_exit(int status) {
        if (g_quick_exit_handler != nullptr) {
                g_quick_exit_handler();
        }
        _Exit(status);
}

extern "C" int __attribute__((weak)) __cdecl nanosleep64(const struct timespec* req, struct timespec* /*rem*/) {
        if (req == nullptr) {
                return -1;
        }

        const LONGLONG millis =
                static_cast<LONGLONG>(req->tv_sec) * 1000LL +
                static_cast<LONGLONG>(req->tv_nsec) / 1000000LL;
        if (millis > 0) {
                Sleep(static_cast<DWORD>(millis));
        }
        return 0;
}
}
#endif
