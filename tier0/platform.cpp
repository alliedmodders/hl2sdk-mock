// vim: set sts=4 ts=8 sw=4 tw=99 et:
#include <chrono>

#include "tier0/platform.h"

using namespace std::chrono;
using std::chrono::steady_clock;

static time_point<steady_clock> sLoadTime = steady_clock::now();

double
Plat_FloatTime()
{
    duration<double> diff = steady_clock::now() - sLoadTime;
    return diff.count();
}
