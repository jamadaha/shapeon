#include "preprocessing.h"
#define STB_DS_IMPLEMENTATION
#include <stb_ds.h>

#include "error_code.h"
#include "io.h"
#include "log.h"
#include "parse.h"

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
    int    label_map[100];
    size_t classes = MapLabels(label_map, labels, count);
    INFO("Class count: %zu", classes);

    FreeLabelled(count, labels, series);
    return 0;
}
