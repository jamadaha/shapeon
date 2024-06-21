#include "../src/information.h"
#include <criterion/assert.h>
#include <criterion/internal/assert.h>
#include <criterion/parameterized.h>
#include <math.h>

// clang-format off
// a = 10/30 = 0.33
// b = 5/30  = 0.16
// c = 15/30 = 0.50
// entropy = (-a * log2(a))       + (-b * log2(b))       + (-c * log2(c)) 
//           (-0.33 * log2(0.33)) + (-0.16 * log2(0.16)) + (-0.50 * log2(0.50))
//           (-0.33 * -1.5995)    + (-0.16 * -2.644)     + (-0.50 * -1)
//           (0.527835)           + (0.42304)            + (0.5)
//        ~= 1.4591
Test(information, entropy_1) {
    int labels[30] = {
        0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
    };
    float entropy = Entropy(labels, 30, 3);
    float diff = fabs(1.4591 - entropy);
    cr_assert_lt(diff, 0.01);
}
// clang-format on
