#include <stdlib.h>
#include <check.h>
#include "common.h"
#include "bitset.h"

#ifndef MODULE_NAME
#error "No module name defined!"
#endif

#define CHECK(__check) fail_unless((__check), NULL)

START_TEST(bitset_simple)
{
    bitset_t *bset = bitset_alloc(16 * BITSET_BITS_IN_FIELD, (malloc_f)malloc);
    CHECK(bset != NULL);

    for (int i = 0; i < 100; i++) {
        bitset_set(bset, i);
        CHECK(bitset_test(bset, i) == 1);
    }

    CHECK(bitset_first_clear(bset) == 100);

    for (int i = 50; i > 40; i--) {
        bitset_clear(bset, i);
        CHECK(bitset_test(bset, i) == 0);
    }

    CHECK(bitset_first_clear(bset) == 41);

    /* There is no interface for freeing the bitset yet.  But we know it's just
     * a malloc away. */
    free(bset);
}
END_TEST

START_TEST(bitset_fail)
{
    bitset_t *bset;

    for (int i = 1; i < BITSET_BITS_IN_FIELD; i++) {
        bset = bitset_alloc(i, (malloc_f)malloc);
        CHECK(bset == NULL);
    }
}
END_TEST

START_TEST(bitset_full)
{
    bitset_t *bset = bitset_alloc(16 * BITSET_BITS_IN_FIELD, (malloc_f)malloc);
    for (int i = 0; i < 16 * BITSET_BITS_IN_FIELD; i++) {
        bitset_set(bset, i);
        CHECK(bitset_test(bset, i) == 1);
    }

    CHECK(bitset_first_clear(bset) == (uint32_t)-1);
    free(bset);
}
END_TEST

Suite *bitset_suite(void)
{
    Suite *s = suite_create(MODULE_NAME);
    TCase *tc = tcase_create("main");
    tcase_add_test(tc, bitset_simple);
    tcase_add_test(tc, bitset_fail);
    tcase_add_test(tc, bitset_full);
    suite_add_tcase(s, tc);

    return s;
}

int main(int argc, char *argv[])
{
    int n_failed;
    Suite *s = bitset_suite();
    SRunner *sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    n_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return n_failed ? EXIT_FAILURE : EXIT_SUCCESS;
}
