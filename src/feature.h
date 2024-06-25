#pragma once

#include <stddef.h>

typedef enum { DIST_MIN, DIST_MAX, FREQUENCY, MAX_ATTRIBUTE } Attribute;
static Attribute ATTRIBUTES[MAX_ATTRIBUTE] = {DIST_MIN, DIST_MAX, FREQUENCY};

typedef struct {
    Attribute    a;
    const float *shapelet;
    size_t       length;
} Feature;

float AttributeCalculate(
    Attribute    a,
    const float *shapelet,
    size_t       shapelet_length,
    const float *series,
    size_t       series_length
);
