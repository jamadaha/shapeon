#include "preprocessing.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <criterion/parameterized.h>

Test(preprocessing, map_labels) {
    int labels[4] = {-1, 0, 1, 1};
    int mapped[100];

    cr_assert_eq(MapLabels(mapped, labels, 4), 3);
    cr_assert_eq(mapped[0], -1);
    cr_assert_eq(mapped[1], 0);
    cr_assert_eq(mapped[2], 1);
    cr_assert_eq(labels[0], 0);
    cr_assert_eq(labels[1], 1);
    cr_assert_eq(labels[2], 2);
    cr_assert_eq(labels[3], 2);
}
