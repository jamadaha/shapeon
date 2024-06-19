#pragma once

#include <stddef.h>

#include "error_code.h"

// Reads a time series csv file.
// Data should be in the format seen below:
// label, series...
// 0, 0.1, 1.4, ...
// 1, 4.2, 3.4
ErrorCode ParseLabelled(size_t *count, size_t *length, int **labels, float ***series, const char *str);

// Reads a time series csv file.
// Data should be in the format seen below:
// series...
// 0.1, 1.4, ...
// 4.2, 3.4
ErrorCode ParseUnlabelled(size_t *count, size_t *length, float ***series, const char *buffer);

void FreeLabelled(size_t count, int *labels, float **series);
void FreeUnlabelled(size_t count, float ***series);
