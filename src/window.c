#include "window.h"

Windower WindowerInit(
    size_t  window_min,
    size_t  window_max,
    size_t  series_width,
    size_t  series_count,
    float **series
) {
    Windower w = {
        .window_min   = window_min,
        .window_max   = window_max,
        .window_index = 0,
        .window_width = window_min,
        .series_count = series_count,
        .series_width = series_width,
        .series_index = 0,
        .series       = series
    };
    return w;
}

bool NextWindow(Window *window, Windower *windower) {
    const size_t window_min   = windower->window_min;
    const size_t window_max   = windower->window_max;
    size_t      *window_index = &windower->window_index;
    size_t      *window_width = &windower->window_width;
    const size_t series_count = windower->series_count;
    const size_t series_width = windower->series_width;
    size_t      *series_index = &windower->series_index;
    float      **series       = windower->series;
    const size_t remainder = series_width - *window_index;

    if (*series_index >= series_count) {
        return false;
    }
    if (remainder < *window_width) {
        if (*window_width < window_max) {
            (*window_width)++;
        } else {
            (*window_width) = window_min;
            (*series_index)++;
        }
        *window_index = 0;
        return NextWindow(window, windower);
    }
    window->ptr   = &series[*series_index][*window_index];
    window->width = *window_width;
    (*window_index)++;
    return true;
}
