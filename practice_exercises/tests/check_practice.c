#include "../practice.h"
#include "check.h"

START_TEST(test_twotimes) {
    ck_assert_int_eq(twotimes("mammamiamammamia"), 1);
    ck_assert_int_eq(twotimes("abracadabra"), 0);
}
END_TEST

int main(void) {
    Suite *s = suite_create("Practice");
    TCase *tc = tcase_create("two_times");
    tcase_add_test(tc, test_twotimes);
    suite_add_tcase(s, tc);
    SRunner *runner = srunner_create(s);
    srunner_run_all(runner, CK_NORMAL);
    srunner_free(runner);
}