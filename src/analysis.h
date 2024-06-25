#pragma once

#include "feature.h"
#include <stdbool.h>
#include <stddef.h>

// returns the multi class fischer value
float Evaluate(size_t count, size_t classes, int *labels, float *vals);

// checks whether a similar feature is already contained
bool Exists(size_t count, Feature *features, Feature *feature);
