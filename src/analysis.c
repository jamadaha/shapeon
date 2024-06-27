#include "analysis.h"
#include <math.h>

float Evaluate( //
    size_t count,
    size_t classes,
    int   *labels,
    float *vals
) {
    float  total = 0;
    size_t class_counts[classes];
    float  sums[classes];
    for (size_t i = 0; i < classes; i++) {
        class_counts[i] = 0;
        sums[i]         = 0;
    }
    for (size_t i = 0; i < count; i++) {
        class_counts[labels[i]]++;
        sums[labels[i]] += vals[i];
        total += vals[i];
    }
    const float total_mean = total / count;
    float       means[classes];
    for (size_t i = 0; i < classes; i++)
        means[i] = sums[i] / class_counts[i];
    float mean = 0;
    for (size_t i = 0; i < classes; i++)
        mean += fabs(total_mean - means[i]);
    float scatter = 0;
    for (size_t i = 0; i < count; i++)
        scatter += fabs(means[labels[i]] - vals[i]);
    return mean / scatter;
}

bool Exists( //
    size_t   count,
    Feature *features,
    Feature *feature
) {
    for (size_t i = 0; i < count; i++) {
        Feature *_feature = &features[i];
        if (feature->a != _feature->a) continue;
        if (feature->length != _feature->length) continue;
        bool         differs = false;
        const size_t length  = feature->length;
        for (size_t i = 1; i < length; i++) {
            const float delta_a = feature->shapelet[i] - feature->shapelet[i - 1];
            const float delta_b = _feature->shapelet[i] - feature->shapelet[i - 1];
            if (fabs(delta_a - delta_b) < 0.1) {
                differs = true;
                break;
            }
        }
        if (!differs) return true;
    }
    return false;
}
