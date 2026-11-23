#include "miniai/ml/loss/clip_probability.h"

#include <math.h>
#include <stdio.h>

#define CHECK_CLOSE(actual, expected)                                      \
    do {                                                                   \
        if (fabs((actual) - (expected)) > 1e-12) {                         \
            fprintf(stderr, "FAILED: got %.17g, expected %.17g\n",         \
                    (double)(actual), (double)(expected));                 \
            return 1;                                                      \
        }                                                                  \
    } while (0)

int main(void)
{
    CHECK_CLOSE(miniai_clip_probability(-1.0),
                MINIAI_PROBABILITY_EPSILON);
    CHECK_CLOSE(miniai_clip_probability(0.0),
                MINIAI_PROBABILITY_EPSILON);
    CHECK_CLOSE(miniai_clip_probability(0.25), 0.25);
    CHECK_CLOSE(miniai_clip_probability(1.0),
                1.0 - MINIAI_PROBABILITY_EPSILON);
    CHECK_CLOSE(miniai_clip_probability(2.0),
                1.0 - MINIAI_PROBABILITY_EPSILON);

    if (!isnan(miniai_clip_probability(NAN))) {
        fprintf(stderr, "FAILED: NaN probability was not preserved\n");
        return 1;
    }

    puts("Clip probability tests passed");
    return 0;
}
