#ifndef MINIAI_ML_LOSS_CLIP_PROBABILITY_H
#define MINIAI_ML_LOSS_CLIP_PROBABILITY_H

#ifdef __cplusplus
extern "C" {
#endif

#define MINIAI_PROBABILITY_EPSILON 1e-12

double miniai_clip_probability(double probability);

#ifdef __cplusplus
}
#endif

#endif
