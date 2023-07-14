#include "s21_test_matrix.h"

void run_tests(void) {
  Suite *list_cases[] = {
                             suite_inverse_matrix(),
                             NULL};

  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

// int main()
// {
//   run_tests();
//   return 0;
// }