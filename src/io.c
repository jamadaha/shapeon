#include "io.h"
#include "error_code.h"
#include "log.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

File FileOpen( //
    const char *path
) {
    File file = {.fd = -1, .buffer = NULL, .len = -1};
    file.fd   = open(path, O_RDONLY);
    if (file.fd == -1) {
        ERROR("Failed to open file \"%s\"", path);
        exit(1);
    }

    struct stat sb;
    if (fstat(file.fd, &sb) == -1) {
        ERROR("Failed to retrieve size of file \"%s\"", path);
        close(file.fd);
        exit(1);
    }
    file.len    = sb.st_size;
    file.buffer = mmap(NULL, file.len, PROT_READ, MAP_PRIVATE, file.fd, 0);
    if (file.buffer == MAP_FAILED) {
        ERROR("Failed to map file content of \"%s\"", path);
        close(file.fd);
        exit(1);
    }

    return file;
}

void FileClose( //
    File *file
) {
    munmap(file->buffer, file->len);
    close(file->fd);
}

ErrorCode ExportFeatures( //
    const char *path,
    size_t      count,
    Feature    *features
) {
    FILE *f = fopen(path, "w");
    if (!f) return FAILED_TO_OPEN_FILE;

    for (size_t i = 0; i < count; i++) {
        Feature *feature = &features[i];
        fprintf(f, "%u", feature->a);
        for (size_t t = 0; t < feature->length; t++)
            fprintf(f, " %f", feature->shapelet[t]);
        fprintf(f, "\n");
    }

    return OK;
}

ErrorCode ExportSeries( //
    const char *path,
    size_t      count,
    size_t      length,
    int        *labels,
    float     **series
) {
    FILE *f = fopen(path, "w");
    if (!f) return FAILED_TO_OPEN_FILE;

    for (size_t i = 0; i < count; i++) {
        fprintf(f, "%i", labels[i]);
        for (size_t t = 0; t < length; t++)
            fprintf(f, " %f", series[i][t]);
        fprintf(f, "\n");
    }

    return OK;
}
