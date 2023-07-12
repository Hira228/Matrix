#include "test_matriX/s21_test_matrix.h"

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

int main() {

  run_tests();
  return 0;
}