#include "s21_matrix.h"

int s21_check_null_matrix(matrix_t *A)
{
    int flag_fail = 0;
    
    if(A -> matrix == NULL || A == NULL)
    {
        flag_fail = 1;
    }
    
    return flag_fail;
}

int s21_incorrect_matrix(matrix_t *A)
{
    int flag_fail = 0;

    if(!s21_check_null_matrix(A))
    {
        if(A -> rows <= 0 || A -> columns <= 0) flag_fail = 1;
    }
    else    flag_fail = 1;

    return flag_fail;
} 

int s21_size_comparison(matrix_t *A, matrix_t *B)
{
    return (A -> rows == B -> rows && A -> columns == B -> columns) ? 1 : 0;
}

int s21_compare_digits(double a, double b)
{
    int flag_fail = 0;
    
    char digit_a[100] = {0};
    char digit_b[100] = {0};
    
    sprintf(digit_a, "%.6f", a);
    sprintf(digit_b, "%.6f", b);
    
    if(strcmp(digit_a, digit_b) == 0)
    {
       flag_fail = 1;
    }

    return flag_fail;
}

int s21_square_matrix(matrix_t *A)
{
    return (A -> rows == A -> columns) ? 1 : 0;
}

void s21_new_matrix_for_minor(matrix_t *A, matrix_t *minor, int minor_size, int crossed_out_rows, int crossed_out_column)
{
    s21_create_matrix(minor_size, minor_size, minor);
    int minor_index_i = 0;
    int minor_index_j = 0;
//printf("%d\n", columns);
    for (int i = 0; i < A -> rows; i++)
    {
        for (int j = 0; j < A -> columns; j++)
        {
            if(i != crossed_out_rows && j != crossed_out_column)
            {
                minor -> matrix[minor_index_i][minor_index_j++] = A -> matrix[i][j];
                if(minor_index_j == (A -> columns - 1)){minor_index_i++; minor_index_j = 0;}
            }
        }
    }
}

double s21_determinant_execution(matrix_t *A)
{
    int minor_size = A -> rows;
    int alg_add = 1;
    double result = 0.0f;
    if(A -> rows == 1)
    {
        result = A -> matrix[0][0];
    }
    else if (A -> rows == 2)
    {
        result = (A -> matrix[0][0] * A -> matrix[1][1]) - (A -> matrix[1][0] * A -> matrix[0][1]);
    }
    else
    {
        for(int i = 0; i < A -> columns; i++)
        {
            matrix_t minor = {0};

            s21_new_matrix_for_minor(A, &minor, minor_size - 1, 0, i);

            result += alg_add * A -> matrix[0][i] * s21_determinant_execution(&minor);
            //printf("%lf\n", s21_determinant_execution(&minor));
            s21_remove_matrix(&minor);
            alg_add = -alg_add;
        }
    }
    return result;
}

void s21_set_null_matrix(matrix_t* result) 
{
  for (int i = 0; i < result->rows; i++) 
  {
    for (int j = 0; j < result->columns; j++)
    {
      result->matrix[i][j] = 0;
    }
  }
}
