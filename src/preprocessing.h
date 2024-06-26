#pragma once

#include <stddef.h>

// moves labels to zero indexed
// returns the total number of labels
size_t MapLabels(  //
    int   *mapped, // list to be mapped to
    int   *labels, // list of prior labels
    size_t length  // length of labels
);
