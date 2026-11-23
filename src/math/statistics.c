#include "miniai/math/statistics.h"
#include <math.h>
#include <stddef.h>


double miniai_mean(const double data[], size_t n) {
    if (data == NULL || n == 0) {
        return NAN;
    }

    double sum = 0.0;

    for (size_t i = 0; i < n; ++i) {
        if (!isfinite(data[i])) {
            return NAN;
        }

        sum += data[i];
    }

    return sum / (double)n;
}

double miniai_min(const double data[], size_t n) {
    if (data == NULL || n == 0) {
        return NAN;
    }

    double minimum = data[0];

    for (size_t i = 0; i < n; ++i) {
        if (!isfinite(data[i])) {
            return NAN;
        }
        if (data[i] < minimum) {
            minimum = data[i];
        }
    }

    return minimum;
}

double miniai_max(const double data[], size_t n) {
    if (data == NULL || n == 0) {
        return NAN;
    }

    double maximum = data[0];

    for (size_t i = 0; i < n; ++i) {
        if (!isfinite(data[i])) {
            return NAN;
        }
        if (data[i] > maximum) {
            maximum = data[i];
        }
    }

    return maximum;
}

double miniai_variance( const double data[], size_t n ) {
    double sum = 0.0;
    if ( n == 0 || data == NULL ) {
        return NAN;
    }
    double mean = miniai_mean( data, n );
    for ( size_t i = 0; i < n; i++ ) {
        double diff = data[i] - mean;
        sum += diff * diff;
    }

    return sum/n;
}

double miniai_stddev( const double data[], size_t n ) {
    double val = miniai_variance(data, n);
    if ( n == 0 || data == NULL ) {
        return NAN;
    }
    else {
        return sqrt(val);
    }
}

/* 
    Standardizes the input array to have a mean of 0 and stddev of 1.
    Formula: (x_i - mean) / stddev
    Supports in-place operations if in == out.
*/
int miniai_standardize(const double in[], double out[], size_t n) {
    size_t index;
    double stddev;
    double mean;

    // Requirement: n=0 -> error
    if (n == 0) {
        return 1;
    }

    if (in == NULL || out == NULL){
        return 2;
    }
    stddev = miniai_stddev(in, n);

    // Requirement: std==0 -> error. Also handle NaN to avoid division by zero
    if (!isfinite(stddev) || stddev == 0.0) {
        return 3;
    }
    mean = miniai_mean(in, n);

    for (index = 0; index < n; ++index) {
        out[index] = (in[index] - mean) / stddev;
    }

    return 0;
}

int miniai_minmax_scale(const double in[], double out[], size_t n)
{
    if (n == 0) {
        return 1;
    }

    if (in == NULL || out == NULL) {
        return 2;
    }

    double minimum = miniai_min(in, n);
    double maximum = miniai_max(in, n);

    if (!isfinite(minimum) || !isfinite(maximum)) {
        return 3;
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
