#include "miniai/ml/loss/binary_cross_entropy.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#define CHECK_CLOSE(actual, expected)                                      \
    do {                                                                   \
        if (fabs((actual) - (expected)) > 1e-9) {                          \
            fprintf(stderr, "FAILED: %s:%d: got %.17g, expected %.17g\n",  \
                    __FILE__, __LINE__, (double)(actual), (double)(expected)); \
            return 1;                                                       \
        }                                                                   \
    } while (0)

static int test_half_predictions(void)
{
    CHECK_CLOSE(miniai_binary_cross_entropy(0.5, 0.0), log(2.0));
    CHECK_CLOSE(miniai_binary_cross_entropy(0.5, 1.0), log(2.0));
    CHECK_CLOSE(miniai_binary_cross_entropy(0.5, 0.25), log(2.0));
    return 0;
}

static int test_correct_predictions(void)
{
    CHECK_CLOSE(miniai_binary_cross_entropy(0.999, 1.0), 0.0010005003335835344);
    CHECK_CLOSE(miniai_binary_cross_entropy(0.001, 0.0), 0.0010005003335835344);
    return 0;
}

static int test_saturated_predictions_are_finite(void)
{
    double loss_zero = miniai_binary_cross_entropy(0.0, 1.0);
    double loss_one = miniai_binary_cross_entropy(1.0, 0.0);

    if (!isfinite(loss_zero) || !isfinite(loss_one)) {
        fprintf(stderr, "FAILED: saturated predictions must have finite loss\n");
        return 1;
    }
    if (fabs(loss_zero - 27.631021115928547) > 1e-4 ||
        fabs(loss_one - 27.631021115928547) > 1e-4) {
        fprintf(stderr,
                "FAILED: unexpected saturated loss zero=%.17g one=%.17g\n",
                loss_zero, loss_one);
        return 1;
    }
    return 0;
}

static int test_invalid_values_return_nan(void)
{
    double invalid[] = {
        miniai_binary_cross_entropy(-0.01, 0.5),
        miniai_binary_cross_entropy(1.01, 0.5),
        miniai_binary_cross_entropy(0.5, -0.01),
        miniai_binary_cross_entropy(0.5, 1.01),
        miniai_binary_cross_entropy(NAN, 0.5),
        miniai_binary_cross_entropy(INFINITY, 0.5),
        miniai_binary_cross_entropy(0.5, NAN),
        miniai_binary_cross_entropy(0.5, INFINITY)
    };

    for (size_t i = 0; i < sizeof(invalid) / sizeof(invalid[0]); ++i) {
        if (!isnan(invalid[i])) {
            fprintf(stderr, "FAILED: invalid input %zu did not return NAN\n", i);
            return 1;
        }
    }
    return 0;
}

static int test_soft_target(void)
{
    CHECK_CLOSE(miniai_binary_cross_entropy(0.5, 0.25), log(2.0));
    CHECK_CLOSE(miniai_binary_cross_entropy(0.8, 0.3),
                -(0.3 * log(0.8) + 0.7 * log1p(-0.8)));
    return 0;
}

int main(int argc, char **argv)
{
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: bce_value_tests <test-name>\n");
        return 1;
    }

    if (strcmp(argv[1], "half") == 0) {
        result = test_half_predictions();
    } else if (strcmp(argv[1], "correct") == 0) {
        result = test_correct_predictions();
    } else if (strcmp(argv[1], "saturated") == 0) {
        result = test_saturated_predictions_are_finite();
    } else if (strcmp(argv[1], "invalid") == 0) {
        result = test_invalid_values_return_nan();
    } else if (strcmp(argv[1], "soft") == 0) {
        result = test_soft_target();
    } else {
        fprintf(stderr, "Unknown test: %s\n", argv[1]);
        return 1;
    }

    if (result == 0) {
        printf("Binary cross entropy test passed: %s\n", argv[1]);
    }
    return result;
}
