#pragma once

typedef enum {
    OK                      = 0,
    OUT_OF_MEMORY           = 1,
    FAILED_TO_OPEN_FILE     = 10,
    PARSE_ERROR             = 20,
    PARSE_INVALID_CHARACTER = 21,
    NONE                    = 100
} ErrorCode;
