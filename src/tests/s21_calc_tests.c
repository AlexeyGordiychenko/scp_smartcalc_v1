#include "s21_calc_tests.h"

int main(void) {
  int failed = 0;
  Suite *calc_tests[] = {s21_incorrect_exp_tests(), s21_correct_exp_tests(),
                         NULL};

  for (int i = 0; calc_tests[i] != NULL; i++) {
    SRunner *sr = srunner_create(calc_tests[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
