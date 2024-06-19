#include "parse.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <criterion/parameterized.h>

Test(parse, atom) {
    const char *str = "0 1";

    size_t count, length;
    int *labels;
    float **series;
    ErrorCode result;

    result = ParseLabelled(&count, &length, &labels, &series, str);

    cr_assert_eq(OK, result);
    cr_assert_eq(1, count);
    cr_assert_eq(1, length);

    FreeLabelled(count, labels, series);
}

Test(parse, excess_ws) {
    const char *str = "0 1 ";

    size_t count, length;
    int *labels;
    float **series;
    ErrorCode result;

    result = ParseLabelled(&count, &length, &labels, &series, str);

    cr_assert_eq(OK, result);
    cr_assert_eq(1, count);
    cr_assert_eq(1, length);

    FreeLabelled(count, labels, series);
}

Test(parse, single) {
    const char *str = "0 0.1 0.2";

    size_t count, length;
    int *labels;
    float **series;
    ErrorCode result;

    result = ParseLabelled(&count, &length, &labels, &series, str);

    cr_assert_eq(OK, result);
    cr_assert_eq(1, count);
    cr_assert_eq(2, length);

    FreeLabelled(count, labels, series);
}

Test(parse, tabs) {
    const char *str = "0\t0.1";

    size_t count, length;
    int *labels;
    float **series;
    ErrorCode result;

    result = ParseLabelled(&count, &length, &labels, &series, str);

    cr_assert_eq(OK, result);
    cr_assert_eq(1, count);
    cr_assert_eq(1, length);

    FreeLabelled(count, labels, series);
}

Test(parse, multiple) {
    const char *str = "0 0.1 0.2 \n 1 -0.1 0.2";

    size_t count, length;
    int *labels;
    float **series;
    ErrorCode result;

    result = ParseLabelled(&count, &length, &labels, &series, str);

    cr_assert_eq(OK, result);
    cr_assert_eq(2, count);
    cr_assert_eq(2, length);

    FreeLabelled(count, labels, series);
}
