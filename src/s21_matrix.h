#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#define RAND_MAX 200

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct
{
    double **matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_check_matrix(matrix_t *A);
int s21_size_comparison(matrix_t *A, matrix_t *B);
int s21_compare_digits(double a, double b);
void s21_new_matrix_for_minor(matrix_t *A, matrix_t *minor, int minor_size, int crossed_out_rows, int crossed_out_column);
int s21_square_matrix(matrix_t *A);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
void s21_set_null_matrix(matrix_t* result);
double s21_determinant_execution(matrix_t *A);
#endif