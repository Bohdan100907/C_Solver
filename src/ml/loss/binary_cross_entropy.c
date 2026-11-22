#include "miniai/ml/loss/binary_cross_entropy.h"
#include "miniai/ml/loss/clip_probability.h"

#include <math.h>

double miniai_binary_cross_entropy(double prediction, double target)
{
    if (!isfinite(prediction) || !isfinite(target) ||
        prediction < 0.0 || prediction > 1.0 ||
        target < 0.0 || target > 1.0) {
        return NAN;
    }

    const double probability = miniai_clip_probability(prediction);

    /*
     * This is a modified BCE at the saturation boundaries: probabilities 0
     * and 1 are replaced by epsilon and 1-epsilon so log() and log1p() stay
     * finite. Soft targets in [0,1] are supported.
     */
    return -(target * log(probability) +
             (1.0 - target) * log1p(-probability));
}
