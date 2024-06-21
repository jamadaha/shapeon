#include "window.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <criterion/parameterized.h>

Test(windower, single) {
    float **series = malloc(sizeof(float *));
    series[0]      = malloc(3 * sizeof(float));
    series[0][0]   = 0.1;
    series[0][1]   = 0.2;
    series[0][2]   = 0.2;

    Windower windower = WindowerInit(2, 3, 3, 1, series);
    Window   window;

    cr_assert(NextWindow(&window, &windower));
    cr_assert_eq(window.ptr, &series[0][0]);
    cr_assert_eq(window.width, 2);

    cr_assert(NextWindow(&window, &windower));
    cr_assert_eq(window.ptr, &series[0][1]);
    cr_assert_eq(window.width, 2);

    cr_assert(NextWindow(&window, &windower));
    cr_assert_eq(window.ptr, &series[0][0]);
    cr_assert_eq(window.width, 3);

    cr_assert(!NextWindow(&window, &windower));

    free(series[0]);
    free(series);
}

Test(windower, multiple) {
    float **series = malloc(2 * sizeof(float *));
    series[0]      = malloc(3 * sizeof(float));
    series[0][0]   = 0.1;
    series[0][1]   = 0.2;
    series[0][2]   = 0.2;
    series[1]      = malloc(3 * sizeof(float));
    series[1][0]   = 1.1;
    series[1][1]   = 1.2;
    series[1][2]   = 1.2;

    Windower windower = WindowerInit(2, 3, 3, 2, series);
    Window   window;

    cr_assert(NextWindow(&window, &windower));
    cr_assert_eq(window.ptr, &series[0][0]);
    cr_assert_eq(window.width, 2);

    cr_assert(NextWindow(&window, &windower));
    cr_assert_eq(window.ptr, &series[0][1]);
    cr_assert_eq(window.width, 2);

    cr_assert(NextWindow(&window, &windower));
    cr_assert_eq(window.ptr, &series[0][0]);
    cr_assert_eq(window.width, 3);

    cr_assert(NextWindow(&window, &windower));
    cr_assert_eq(window.ptr, &series[1][0]);
    cr_assert_eq(window.width, 2);

    cr_assert(NextWindow(&window, &windower));
    cr_assert_eq(window.ptr, &series[1][1]);
    cr_assert_eq(window.width, 2);

    cr_assert(NextWindow(&window, &windower));
    cr_assert_eq(window.ptr, &series[1][0]);
    cr_assert_eq(window.width, 3);

    cr_assert(!NextWindow(&window, &windower));

    free(series[0]);
    free(series[1]);
    free(series);
}
