#include "analysis.h"
#include <stdio.h>
#define STB_DS_IMPLEMENTATION
#include <float.h>
#include <stb_ds.h>

#include "error_code.h"
#include "feature.h"
#include "io.h"
#include "log.h"
#include "parse.h"
#include "preprocessing.h"
#include "window.h"

int main(int argc, char **argv) {
    LogInit();
    if (argc < 2) {
        ERROR("Missing path argument");
        return 1;
    }
    INFO("Opening file");
    File file = FileOpen(argv[1]);
    INFO("Parsing data");
    ErrorCode result;
    size_t    count, length;
    int      *labels;
    float   **series;
    if ((result = ParseLabelled(
             &count, &length, &labels, &series, file.buffer
         )) != OK) {
        ERROR("Failed to parse series data");
        TRACE("Closing file");
        FileClose(&file);
        return 1;
    }
    TRACE("Closing file");
    FileClose(&file);
    INFO("Data points: %zu", count);
    INFO("Series length: %zu", length);

    int    mapped[100];
    size_t classes = MapLabels(mapped, labels, count);
    INFO("Class count: %zu", classes);

    size_t windows  = 0;
    Attribute attributes[2] = {DIST_MIN, DIST_MAX};

    Window   max_window;
    float    max_eval = FLT_MIN;
    Windower windower =
        WindowerInit(2, 16, length, count, series);
    Window window;
    while (NextWindow(&window, &windower)) {
        windows++;
        for (size_t i = 0; i < 2; i++) {
            float vals[count];
            for (size_t t = 0; t < count; t++) {
                vals[t] = AttributeCalculate(
                    attributes[i], window.ptr, window.width,
                    series[t], length
                );
            }
            float eval =
                Evaluate(count, classes, labels, vals);
            if (eval > max_eval) {
                max_eval   = eval;
                max_window = window;
            }
        }
    }
    printf("%f\n", max_eval);
    for (size_t i = 0; i < max_window.width; i++)
        printf("%f ", max_window.ptr[i]);
    printf("\n");

    INFO("Windows tested: %zu", windows);

    FreeLabelled(count, labels, series);
    return 0;
}
