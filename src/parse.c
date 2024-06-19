#include <ctype.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_code.h"
#include "parse.h"
#include "stb_ds.h"

ErrorCode ParseInt(int *i, const char **str) {
    char *end;
    *i = strtol(*str, &end, 10);
    if (*str == end) return PARSE_ERROR;
    *str = end;
    return OK;
}

ErrorCode ParseFloat(float *f, const char **str) {
    char *end;
    *f = strtof(*str, &end);
    if (*str == end) return PARSE_ERROR;
    *str = end;
    return OK;
}

ErrorCode ParseFloatList(float **f, const char **str) {
    while (**str != '\0' && **str != EOF && **str != '\n') {
        if (isspace(**str)) {
            (*str)++;
            continue;
        }
        float _f;
        ErrorCode ec = ParseFloat(&_f, str);
        if (ec != OK) return ec;
        arrpush(*f, _f);
    }
    return OK;
}

ErrorCode ParseLabelled(size_t *count, size_t *length, int **labels, float ***series, const char *str) {
    ErrorCode ec    = OK;
    int *_labels    = NULL;
    float **_series = NULL;

    while (*str != '\0' && *str != EOF) {
        if (isspace(*str)) {
            str++;
            continue;
        }
        int i;
        if ((ec = ParseInt(&i, &str)) != OK) break;
        arrpush(_labels, i);
        float *f = NULL;
        if ((ec = ParseFloatList(&f, &str)) != OK) break;
        arrpush(_series, f);
    }

    if (ec == OK) {
        *labels = _labels;
        *series = _series;
        *count  = arrlenu((*series));
        *length = arrlenu((*series)[0]);
    } else {
        if (_labels) arrfree(_labels);
        if (_series) {
            for (size_t i = 0; i < arrlenu(_series); i++)
                arrfree(_series[i]);
            arrfree(_series);
        }
    }

    return ec;
}

void FreeLabelled(size_t count, int *labels, float **series) {
    if (labels) arrfree(labels);
    for (size_t i = 0; i < count; i++)
        if (series[i]) arrfree(series[i]);
    if (series) arrfree(series);
}
