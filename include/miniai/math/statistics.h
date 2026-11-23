#ifndef MINIAI_MATH_STATISTICS_H
#define MINIAI_MATH_STATISTICS_H

#include <stddef.h>

/**
 * Scale values to the [0, 1] interval using min-max normalization.
 *
 * Formula: (x - min) / (max - min).
 * Supports in-place scaling when in == out.
 *
 * Returns 0 on success and a non-zero value on error.
 */
int miniai_minmax_scale(const double in[], double out[], size_t n);

#endif
