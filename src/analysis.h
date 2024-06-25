#pragma once

#include <stddef.h>

// returns the multi class fischer value
float Evaluate(
    size_t count,
    size_t classes,
    int   *labels,
    float *vals
);
