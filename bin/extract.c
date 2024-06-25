#include "io.h"
#include "window.h"
#define STB_DS_IMPLEMENTATION
#include <stb_ds.h>

#include <float.h>

#include "analysis.h"
#include "error_code.h"
#include "feature.h"
#include "log.h"
#include "parse.h"
#include "preprocessing.h"

#define FEATURES 100

size_t Extract(
    Feature **features,
    size_t    classes,
    size_t    count,
    size_t    length,
    int      *labels,
    float   **series
); // See buttom of file

int main(int argc, char **argv) {
    LogInit();
    const char *path = argv[1];

    INFO("Loading data");
    size_t    count  = 0;
    size_t    length = 0;
    int      *labels = NULL;
    float   **series = NULL;
    ErrorCode code   = NONE;
    code             = Load(&count, &length, &labels, &series, path);
    if (code != OK) {
        ERROR("Data loading failed with %d", code);
        return code;
    }
    INFO("Data points: %zu", count);
    INFO("Series length: %zu", length);

    INFO("Mapping labels");
    size_t classes        = 0;
    int    class_map[100] = {0};
    classes               = MapLabels(class_map, labels, count);
    INFO("Class count: %zu", classes);

    INFO("Generating features");
    size_t   feature_count = 0;
    Feature *features      = NULL;
    feature_count          = Extract(&features, classes, count, length, labels, series);
    if (!features) {
        ERROR("Failed to generate any features");
        goto TERMINATION;
    }
    INFO("Features: %zu", feature_count);

    INFO("Exporting features");
    code = ExportFeatures(feature_count, features);
    if (code != OK) {
        ERROR("Failed to export features with %d", code);
        goto TERMINATION;
    }

TERMINATION:
    INFO("Freeing data");
    FreeLabelled(count, labels, series);
    if (features) arrfree(features);

    return code;
}

size_t Extract(
    Feature **features, // Output, feature list
    size_t    classes,  // The number of classes
    size_t    count,    // The number of data points
    size_t    length,   // The length of series
    int      *labels,   // The class of each series
    float   **series    // A list of series. Must all be equal length
) {
    Windower windower               = WindowerInit(2, 2, length, count, series);
    float    feature_vals[FEATURES] = {0};
    Feature  _features[FEATURES]    = {0};
    for (size_t i = 0; i < FEATURES; i++) {
        feature_vals[i]       = FLT_MIN;
        _features[i].shapelet = NULL;
    }

    Window window;
    while (NextWindow(&window, &windower)) {
        for (size_t a = 0; a < MAX_ATTRIBUTE; a++) {
            const Attribute attribute = ATTRIBUTES[a];
            float           vals[count];
            for (size_t i = 0; i < count; i++) {
                float *s = series[i];
                vals[i]  = AttributeCalculate(attribute, window.ptr, window.width, s, length);
            }
            const float eval = Evaluate(count, classes, labels, vals);
            if (eval > feature_vals[FEATURES - 1]) {
                feature_vals[FEATURES - 1]       = eval;
                _features[FEATURES - 1].shapelet = window.ptr;
                _features[FEATURES - 1].length   = window.width;
                _features[FEATURES - 1].a        = attribute;
                for (size_t i = FEATURES - 1; i > 0; i--)
                    if (feature_vals[i] > feature_vals[i - 1]) {
                        float val           = feature_vals[i - 1];
                        feature_vals[i - 1] = feature_vals[i];
                        feature_vals[i]     = val;
                        Feature f           = _features[i - 1];
                        _features[i - 1]    = _features[i];
                        _features[i]        = f;
                    } else
                        break;
            }
        }
    }

    size_t feature_count = 0;
    for (size_t i = 0; i < 100; i++) {
        if (!_features[i].shapelet) break;
        feature_count++;
        arrpush(*features, _features[i]);
    }
    return feature_count;
}
