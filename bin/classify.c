#include <math.h>
#include <stdio.h>
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include <float.h>
#include <limits.h>

#include "error_code.h"
#include "log.h"
#include "parse.h"

void swapi(int *a, int *b) {
    int temp = *a;
    *a       = *b;
    *b       = temp;
}

void swapf(float *a, float *b) {
    float temp = *a;
    *a         = *b;
    *b         = temp;
}

int Classify(
    size_t  k,
    size_t  count,
    size_t  length,
    int    *labels,
    float **series,
    float  *s
) {
    float best_value[k];
    int   best_label[k];
    for (size_t i = 0; i < k; i++) {
        best_value[i] = FLT_MAX;
        best_label[i] = INT_MAX;
    }
    for (size_t i = 0; i < count; i++) {
        float val = 0;
        for (size_t t = 0; t < length; t++)
            val += fabsf(series[i][t] - s[t]);
        if (val < best_value[k - 1]) {
            best_value[k - 1] = val;
            best_label[k - 1] = labels[i];
            for (size_t t = k - 1; t > 1; t--)
                if (best_value[t] < best_value[t - 1]) {
                    swapf(
                        &best_value[t - 1], &best_value[t]
                    );
                    swapi(
                        &best_label[t - 1], &best_label[t]
                    );
                }
        }
    }
    int    label       = INT_MAX;
    size_t highest_occ = 0;
    for (size_t i = 0; i < k; i++) {
        size_t occ = 0;
        for (size_t t = i; t < k; t++)
            if (best_label[i] == best_label[t]) occ++;
        if (occ > highest_occ) {
            label       = best_label[i];
            highest_occ = occ;
        }
    }
    return label;
}

int main(int argc, char **argv) {
    LogInit();
    if (argc < 3) {
        ERROR("Missing path argument");
        return 1;
    }
    size_t      k          = 1;
    size_t      shots      = 6;
    const char *path_train = argv[1];
    const char *path_test  = argv[2];
    INFO("Path train: %s", path_train);
    INFO("Path test: %s", path_test);

    size_t count_train, length_train, count_test,
        length_test;
    int    *labels_train, *labels_test;
    float **series_train, **series_test;

    ErrorCode ec;
    INFO("Loading train data");
    if ((ec = Load(
             &count_train, &length_train, &labels_train,
             &series_train, path_train
         )) != OK)
        return ec;
    INFO("Loading test data");
    if ((ec = Load(
             &count_test, &length_test, &labels_test,
             &series_test, path_test
         )) != OK)
        return ec;

    if (shots > count_train) shots = count_train;

    size_t correct = 0;
    for (size_t i = 0; i < count_test; i++) {
        int label_expected = labels_test[i];
        int label_actual   = Classify(
            k, shots, length_train, labels_train,
            series_train, series_test[i]
        );
        if (label_expected == label_actual) correct++;
    }
    printf(
        "Total: %zu. Correct: %zu\n", count_test, correct
    );
    printf(
        "Accuracy: %f%%\n",
        (double)correct / (double)count_test * 100
    );

    if (length_train != length_test) {
        ERROR("Train and test series are not of same length"
        );
        return 1;
    }

    TRACE("Unloading train data");
    FreeLabelled(count_train, labels_train, series_train);

    TRACE("Unloading test data");
    FreeLabelled(count_test, labels_test, series_test);

    return ec;
}
