#pragma once

#include <stddef.h>

#include "error_code.h"
#include "feature.h"

ErrorCode LoadData( //
    size_t     *count,
    size_t     *length,
    int       **labels,
    float    ***series,
    const char *path
);

ErrorCode ParseData( //
    size_t     *count,
    size_t     *length,
    int       **labels,
    float    ***series,
    const char *str
);

void FreeData( //
    size_t  count,
    int    *labels,
    float **series
);

ErrorCode LoadFeatures( //
    size_t     *count,
    Feature   **features,
    const char *path
);

ErrorCode ParseFeatures( //
    size_t     *count,
    Feature   **features,
    const char *str
);

void FreeFeatures( //
    size_t   count,
    Feature *features
);
