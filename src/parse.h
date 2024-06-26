#pragma once

#include <stddef.h>

#include "error_code.h"

ErrorCode Load( //
    size_t     *count,
    size_t     *length,
    int       **labels,
    float    ***series,
    const char *path
);

ErrorCode ParseLabelled( //
    size_t     *count,
    size_t     *length,
    int       **labels,
    float    ***series,
    const char *str
);

void FreeLabelled( //
    size_t  count,
    int    *labels,
    float **series
);
