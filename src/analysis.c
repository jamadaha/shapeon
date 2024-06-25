#include "analysis.h"
#include <math.h>

float Evaluate(
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
    float means[classes];
    for (size_t i = 0; i < classes; i++)
        means[i] = 0;
    for (size_t i = 0; i < classes; i++)
        means[i] = sums[i] / class_counts[i];
    float mean = 0;
    for (size_t i = 0; i < classes; i++)
        mean += powf(total_mean - means[i], 2);
    float scatter = 0;
    for (size_t i = 0; i < count; i++) {
        const float _scatter = means[labels[i]] - vals[i];
        scatter += powf(_scatter, 2);
    }
    return mean / scatter;
}
