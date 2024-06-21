#include "information.h"
#include <math.h>

float Entropy(int *labels, size_t length, size_t classes) {
    size_t class_count[classes];
    for (size_t i = 0; i < classes; i++)
        class_count[i] = 0;
    for (size_t i = 0; i < length; i++)
        class_count[labels[i]]++;

    float entropy = 0;
    for (size_t i = 0; i < classes; i++) {
        if (class_count[i]) {
            double prop = (float)class_count[i] / length;
            entropy += (-prop) * log2(prop);
        }
    }
    return entropy;
}
