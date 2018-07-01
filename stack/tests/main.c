#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "../include/stack.h"

START_TEST (isEmpty_newStack_isTrue) 
{
  Stack * s = Stack_new();
  ck_assert(true == Stack_isEmpty(s));
  Stack_free(s);
}
END_TEST

START_TEST (isEmpty_onePush_isFalse)
{
  Stack * s = Stack_new();
  Stack_push(s, 10);
    ck_assert(false == Stack_isEmpty(s));
  Stack_free(s);
}
END_TEST

START_TEST (isEmpty_onePush_onePop_isFalse)
{
  Stack * s = Stack_new();
  Stack_push(s, 10);
  Stack_pop(s);
  ck_assert(true == Stack_isEmpty(s));
  Stack_free(s);
}
END_TEST

START_TEST (pop_twoPush_inReverseOrder)
{
  const int vals[] = {1, 2};
  Stack * s = Stack_new();
  Stack_push(s, vals[0]);
  Stack_push(s, vals[1]);
  ck_assert_int_eq(vals[1], Stack_pop(s));
  ck_assert_int_eq(vals[0], Stack_pop(s));
  Stack_free(s);
}
END_TEST

Suite *test_suite(void);

int main(void) {
  Suite *s = test_suite();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);  // important for debugging!

  srunner_run_all(sr, CK_VERBOSE);

  int num_tests_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return num_tests_failed;
}

Suite *test_suite(void) {
  Suite *s = suite_create("Module");
  TCase *tc_sample;

  tc_sample = tcase_create("TestCase");
  tcase_add_test(tc_sample, isEmpty_newStack_isTrue);
  tcase_add_test(tc_sample, isEmpty_onePush_isFalse);
  tcase_add_test(tc_sample, isEmpty_onePush_onePop_isFalse);
  tcase_add_test(tc_sample, pop_twoPush_inReverseOrder);
  suite_add_tcase(s, tc_sample);

  return s;
}