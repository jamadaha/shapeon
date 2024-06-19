#pragma once

typedef enum {
    OK = 0,
    OUT_OF_MEMORY = 1,
    // Parsing errors
    // Used for misc parsing errors
    PARSE_ERROR = 10,
    // Used if an invalid character is found during parsing
    // The valid characters are whitespace, numbers, and dots '.' (Locale inflexible)
    PARSE_INVALID_CHARACTER
} ErrorCode;
