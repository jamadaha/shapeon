#include "feature.h"
#include "log.h"
#include <float.h>
#include <math.h>
#include <stdlib.h>

static inline float Dist(
    const float *shapelet,
    size_t       shapelet_length,
    const float *series,
    size_t       pos
) {
    const float offset = series[pos] - shapelet[0];
    float       dist   = 0;
    for (size_t i = 0; i < shapelet_length; i++)
        dist +=
            fabs(series[pos + i] - shapelet[i] - offset);
    return dist;
}

static inline float DistMin(
    const float *shapelet,
    size_t       shapelet_length,
    const float *series,
    size_t       series_length
) {
    float best_dist = FLT_MAX;
    for (size_t i = 0; i <= series_length - shapelet_length;
         i++) {
        const float dist =
            Dist(shapelet, shapelet_length, series, i);
        if (dist < best_dist) best_dist = dist;
    }
    return best_dist;
}

static inline float DistMax(
    const float *shapelet,
    size_t       shapelet_length,
    const float *series,
    size_t       series_length
) {
    float best_dist = FLT_MIN;
    for (size_t i = 0; i <= series_length - shapelet_length;
         i++) {
        const float dist =
            Dist(shapelet, shapelet_length, series, i);
        if (dist > best_dist) best_dist = dist;
    }
    return best_dist;
}

float AttributeCalculate(
    Attribute    a,
    const float *shapelet,
    size_t       shapelet_length,
    const float *series,
    size_t       series_length
) {
    switch (a) {
    case DIST_MIN:
        return DistMin(
            shapelet, shapelet_length, series, series_length
        );
    case DIST_MAX:
        return DistMax(
            shapelet, shapelet_length, series, series_length
        );
    default: break;
    }
    ERROR(
        "Feature Calculate called with unhandled "
        "attribute: %d",
        a
    );
    exit(1);
}
