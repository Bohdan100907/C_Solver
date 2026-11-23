#include "miniai/math/statistics.h"

#include <math.h>
#include <stddef.h>

int miniai_minmax_scale(const double in[], double out[], size_t n)
{
    if (n == 0 || in == NULL || out == NULL) {
        return 1;
    }

    double minimum = in[0];
    double maximum = in[0];

    for (size_t i = 0; i < n; ++i) {
        if (!isfinite(in[i])) {
            return 2;
        }
        if (in[i] < minimum) {
            minimum = in[i];
        }
        if (in[i] > maximum) {
            maximum = in[i];
        }
    }

    if (maximum == minimum) {
        return 3;
    }

    for (size_t i = 0; i < n; ++i) {
        const double numerator = in[i] / 2.0 - minimum / 2.0;
        const double denominator = maximum / 2.0 - minimum / 2.0;
        out[i] = numerator / denominator;
    }

    return 0;
}
