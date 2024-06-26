#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    size_t       width; // number of elements in window
    const float *ptr;   // ptr to start of window
} Window;

typedef struct {
    const size_t window_min;   // minimum window width
    const size_t window_max;   // maximum window width
    size_t       window_index; // current window pos
    size_t       window_width; // current window width
    const size_t series_count; // number of series
    const size_t series_width; // width of series
    size_t       series_index; // current series index
    float      **series;       // ptr to a list of lists
} Windower;

Windower WindowerInit( //
    size_t  window_min,
    size_t  window_max,
    size_t  series_width,
    size_t  series_count,
    float **series
);

bool NextWindow( //
    Window   *window,
    Windower *windower
);
