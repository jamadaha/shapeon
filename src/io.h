#pragma once

#include "error_code.h"
#include "feature.h"

typedef struct {
    int   fd;
    int   len;
    char *buffer;
} File;

// Opens file and directs buffer to file content
// Remember to call close file!
File FileOpen(const char *path);
void FileClose(File *file);

ErrorCode ExportFeatures(size_t count, Feature *features);
