#if defined(__MINGW32__)
#include "mingw_compat.hpp"

#include <chrono>
#include <cstdlib>

extern "C" {
int timespec_get(struct timespec* ts, int base) {
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

int at_quick_exit(void (*func)(void)) {
        g_quick_exit_handler = func;
        return 0;
}

void quick_exit(int status) {
        if (g_quick_exit_handler != nullptr) {
                g_quick_exit_handler();
        }
        _Exit(status);
}
}
#endif
