#include <limits.h>
#include <stb_ds.h>

#include "preprocessing.h"

size_t MapLabels(int *mapped, int *labels, size_t length) {
    size_t count = 0;

    for (size_t i = 0; i < length; i++) {
        size_t m = INT_MAX;
        for (size_t t = 0; t < count; t++)
            if (mapped[t] == labels[i]) {
                m = t;
                break;
            }
        if (m == INT_MAX) {
            mapped[count] = labels[i];
            m = count++;
        }
        labels[i] = m;
    }

    return count;
}
