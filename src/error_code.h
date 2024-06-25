#pragma once

typedef enum {
    OK                      = 0,
    OUT_OF_MEMORY           = 1,
    PARSE_ERROR             = 10,
    PARSE_INVALID_CHARACTER = 11,
    NONE                    = 100
} ErrorCode;
