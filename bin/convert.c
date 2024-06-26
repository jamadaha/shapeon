#include "error_code.h"
#include "feature.h"
#include "io.h"
#include "log.h"
#include "parse.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

void Convert(
    float ***feature_series,
    size_t   feature_count,
    Feature *features,
    size_t   series_count,
    size_t   series_length,
    float  **series
); // See buttom of file

int main(int argc, char **argv) {
    LogInit();
    const char *out_path      = argv[1];
    const char *path_features = argv[2];
    const char *path_data     = argv[3];

    INFO("Loading features");
    ErrorCode code          = NONE;
    size_t    feature_count = 0;
    Feature  *features      = NULL;
    code                    = LoadFeatures(&feature_count, &features, path_features);
    if (code != OK) {
        ERROR("Feature loading failed with %d", code);
        return code;
    }
    INFO("Features: %zu", feature_count);

    INFO("Loading data");
    size_t  count  = 0;
    size_t  length = 0;
    int    *labels = NULL;
    float **series = NULL;
    code           = LoadData(&count, &length, &labels, &series, path_data);
    if (code != OK) {
        ERROR("Data loading failed with %d", code);
        return code;
    }
    INFO("Data points: %zu", count);
    INFO("Series length: %zu", length);

    INFO("Converting series");
    float **feature_series = NULL;
    Convert(&feature_series, feature_count, features, count, length, series);

    INFO("Exporting data");
    code = ExportSeries(out_path, count, feature_count, labels, feature_series);
    if (code != OK) ERROR("Failed to export features with %d", code);

    INFO("Freeing data");
    FreeFeatures(feature_count, features);
    FreeData(count, labels, series);
    for (size_t i = 0; i < count; i++)
        arrfree(feature_series[i]);
    arrfree(feature_series);

    return code;
}

void Convert( //
    float ***feature_series,
    size_t   feature_count,
    Feature *features,
    size_t   series_count,
    size_t   series_length,
    float  **series
) {
    for (size_t i = 0; i < series_count; i++) {
        float *_series         = series[i];
        float *_feature_series = NULL;
        for (size_t t = 0; t < feature_count; t++) {
            Feature   f   = features[t];
            Attribute a   = f.a;
            float    *s   = f.shapelet;
            size_t    l   = f.length;
            float     val = AttributeCalculate(a, s, l, _series, series_length);
            arrpush(_feature_series, val);
        }
        arrpush(*feature_series, _feature_series);
    }
}
