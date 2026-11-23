#include "miniai/ml/loss/clip_probability.h"

#include <math.h>

double miniai_clip_probability(double probability)
{
    const double epsilon = MINIAI_PROBABILITY_EPSILON;
    double clipped = probability;

    if (isnan(clipped)) {
        return clipped;
    }

    if (clipped < epsilon) {
        clipped = epsilon;
    } else if (clipped > 1.0 - epsilon) {
        clipped = 1.0 - epsilon;
    }

    return clipped;
}
