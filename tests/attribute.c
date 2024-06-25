#include "feature.h"
#include "log.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <criterion/parameterized.h>
#include <math.h>

Test(attribute_dist_min, same) {
    const float shapelet[2] = {0.0, 1.0};
    const float series[2]   = {0.0, 1.0};
    const float expected    = 0.0;

    const float val = AttributeCalculate(
        DIST_MIN, shapelet, 2, series, 2
    );

    const float diff = fabs(expected - val);

    cr_assert_lt(diff, 0.1);
}

Test(attribute_dist_min, inverse) {
    const float shapelet[2] = {0.0, 1.0};
    const float series[2]   = {1.0, 0.0};
    const float expected    = 2.0;

    const float val = AttributeCalculate(
        DIST_MIN, shapelet, 2, series, 2
    );

    const float diff = fabs(expected - val);

    cr_assert_lt(diff, 0.1);
}

Test(attribute_dist_min, long) {
    const float shapelet[2] = {0.0, 1.0};
    const float series[4]   = {0.0, 0.5, 1.0, 2.0};
    const float expected    = 0.0;

    const float val = AttributeCalculate(
        DIST_MIN, shapelet, 2, series, 4
    );

    const float diff = fabs(expected - val);

    cr_assert_lt(diff, 0.1);
}

Test(attribute_dist_min, inverse_long) {
    const float shapelet[2] = {1.0, 0.0};
    const float series[4]   = {0.0, 0.5, 1.0, 2.0};
    const float expected    = 1.5;

    const float val = AttributeCalculate(
        DIST_MIN, shapelet, 2, series, 4
    );

    const float diff = fabs(expected - val);

    cr_assert_lt(diff, 0.1);
}

Test(attribute_dist_max, same) {
    const float shapelet[2] = {0.0, 1.0};
    const float series[2]   = {0.0, 1.0};
    const float expected    = 0.0;

    const float val = AttributeCalculate(
        DIST_MAX, shapelet, 2, series, 2
    );

    const float diff = fabs(expected - val);

    cr_assert_lt(diff, 0.1);
}

Test(attribute_dist_max, inverse) {
    const float shapelet[2] = {0.0, 1.0};
    const float series[2]   = {1.0, 0.0};
    const float expected    = 2.0;

    const float val = AttributeCalculate(
        DIST_MAX, shapelet, 2, series, 2
    );

    const float diff = fabs(expected - val);

    cr_assert_lt(diff, 0.1);
}

Test(attribute_dist_max, long) {
    const float shapelet[2] = {0.0, 1.0};
    const float series[4]   = {0.0, 0.5, 1.0, 2.0};
    const float expected    = 0.5;

    const float val = AttributeCalculate(
        DIST_MAX, shapelet, 2, series, 4
    );

    const float diff = fabs(expected - val);

    cr_assert_lt(diff, 0.1);
}

Test(attribute_dist_max, inverse_long) {
    const float shapelet[2] = {1.0, 0.0};
    const float series[4]   = {0.0, 0.5, 1.0, 2.0};
    const float expected    = 2.0;

    const float val = AttributeCalculate(
        DIST_MAX, shapelet, 2, series, 4
    );

    const float diff = fabs(expected - val);

    cr_assert_lt(diff, 0.1);
}

Test(attribute_frequency, none) {
    const float shapelet[2] = {0.0, 1.0};
    const float series[4]   = {0.0, 0.5, 1.0, 1.5};
    const float expected    = 0;

    const float val = AttributeCalculate(
        FREQUENCY, shapelet, 2, series, 4
    );

    const float diff = fabs(expected - val);

    cr_assert_lt(diff, 0.1);
}

Test(attribute_frequency, half) {
    const float shapelet[2] = {0.0, 1.0};
    const float series[5]   = {0.0, 1.0, 2.0, 3.4, 6.8};
    const float expected    = 0.5f;

    const float val = AttributeCalculate(
        FREQUENCY, shapelet, 2, series, 5
    );

    const float diff = fabs(expected - val);

    cr_assert_lt(diff, 0.1);
}

Test(attribute_frequency, all) {
    const float shapelet[2] = {0.0, 1.0};
    const float series[4]   = {0.0, 1.0, 2.0, 3.0};
    const float expected    = 1.0f;

    const float val = AttributeCalculate(
        FREQUENCY, shapelet, 2, series, 4
    );

    const float diff = fabs(expected - val);

    cr_assert_lt(diff, 0.1);
}

Test(attribute_frequency, tolerance) {
    const float shapelet[2] = {0.0, 1.0};
    const float series[2]   = {0.0, 1.01};
    const float expected    = 1.0f;

    const float val = AttributeCalculate(
        FREQUENCY, shapelet, 2, series, 2
    );

    const float diff = fabs(expected - val);

    cr_assert_lt(diff, 0.1);
}
