#include "s21_test_matrix.h"

START_TEST(trans_matrix1) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;

  s21_transpose(&A, &Z);
  //   for(int i = 0; i < 3; i++)
  //   {
  //     for(int j = 0; j < 3; j++)
  //     {
  //         printf("%lf\t", Z.matrix[i][j]);
  //     }
  //     printf("\n");
  //   }
  s21_create_matrix(3, 3, &X);

  X.matrix[0][0] = 1.0;
  X.matrix[0][1] = 4.0;
  X.matrix[0][2] = 7.0;
  X.matrix[1][0] = 2.0;
  X.matrix[1][1] = 5.0;
  X.matrix[1][2] = 8.0;
  X.matrix[2][0] = 3.0;
  X.matrix[2][1] = 6.0;
  X.matrix[2][2] = 9.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(trans_matrix2) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(2, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;

  s21_transpose(&A, &Z);

  s21_create_matrix(3, 2, &X);

  X.matrix[0][0] = 1.0;
  X.matrix[0][1] = 4.0;
  X.matrix[1][0] = 2.0;
  X.matrix[1][1] = 5.0;
  X.matrix[2][0] = 3.0;
  X.matrix[2][1] = 6.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(trans_matrix3) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 1.0;

  s21_transpose(&A, &Z);

  s21_create_matrix(1, 1, &X);

  X.matrix[0][0] = 1.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(trans_matrix4) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  int rows = -3;
  int columns = -3;

  s21_create_matrix(rows, columns, &A);

  s21_transpose(&A, &Z);

  s21_create_matrix(rows, columns, &X);

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, FAILURE);
}
END_TEST

Suite *suite_transpose_matrix(void) {
  Suite *s = suite_create("suite_transpose");
  TCase *tc = tcase_create("case_transpose");

  tcase_add_test(tc, trans_matrix1);
  tcase_add_test(tc, trans_matrix2);
  tcase_add_test(tc, trans_matrix3);
  tcase_add_test(tc, trans_matrix4);

  suite_add_tcase(s, tc);
  return s;
}