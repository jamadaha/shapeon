#include "analysis.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <criterion/parameterized.h>

Test(analysis, relative_a) {
    int   labels[4] = {0, 0, 1, 1};
    float vals_a[4] = {0, 0, 1, 1};
    float vals_b[4] = {0, 0.5, 1, 1.5};

    float eval_a = Evaluate(4, 2, labels, vals_a);
    float eval_b = Evaluate(4, 2, labels, vals_b);

    cr_assert_gt(eval_a, eval_b);
}

Test(analysis, relative_b) {
    int   labels[6] = {0, 0, 1, 1, 2, 2};
    float vals_a[6] = {0.1, 0.2, 0.4, 0.6, 1.1, 1.2};
    float vals_b[6] = {0.1, 0.2, 0.1, 0.3, 0.7, 0.8};

    float eval_a = Evaluate(6, 3, labels, vals_a);
    float eval_b = Evaluate(6, 3, labels, vals_b);

    cr_assert_gt(eval_a, eval_b);
}

Test(analysis, equal_scatter) {
    int   labels[4] = {0, 0, 1, 1};
    float vals_a[4] = {0, 0, 1, 1};
    float vals_b[4] = {0, 0, 2, 2};

    float eval_a = Evaluate(4, 2, labels, vals_a);
    float eval_b = Evaluate(4, 2, labels, vals_b);

    cr_assert_eq(eval_a, eval_b);
}
