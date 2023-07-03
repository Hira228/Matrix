#include "s21_matrix.h"

int main()
{
    matrix_t result = {NULL, 3, 3};
    int rows = 13;
    int columns = 13;
    //int res = 0;
    s21_create_matrix(rows, columns, &result);
}


int s21_create_matrix(int rows, int columns, matrix_t *result)
{
    result -> matrix = (double **)malloc(rows * sizeof(double *));

    for (int i = 0; i < rows; i++)
    {
        result -> matrix[i] = (double *) malloc (columns * sizeof(double));
    }
}

void s21_remove_matrix(matrix_t *A)
{
    for (int i = 0; i < A -> rows; i++)
    {
        free(A -> matrix[i]);
    }

    free(A -> matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B)
{
    int flag_fail = SUCCESS;

    if(!(A -> rows == B -> rows && A -> columns && B -> columns) || (A -> matrix == NULL || B -> matrix == NULL))
    {
        flag_fail = FAILURE;
    }

    for (int i = 0; i < A -> rows; i++)
    {
        for (int j = 0; j < A -> columns; j++)
        {
            if(A -> matrix[i][j] != B -> matrix[i][j])
            {
                flag_fail = FAILURE;
            }
        }
    }
    
    return flag_fail;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result)
{
    int flag_fail = s21_eq_matrix(A, B);

    if(flag_fail)
    {
        s21_create_matrix(A -> rows, B -> columns, result);

        for (int i = 0; i < A -> rows; i++)
        {
            for (int j = 0; j < A -> columns; j++)
            {
                result -> matrix[i][j] = A -> matrix[i][j] + B -> matrix[i][j];
            }
        }
    }

    return flag_fail;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result)
{
    int flag_fail = s21_eq_matrix(A, B);

    if(flag_fail)
    {
        s21_create_matrix(A -> rows, A -> columns, result);

        for (int i = 0; i < A -> rows; i++)
        {
            for (int j = 0; j < A -> columns; j++)
            {
                result -> matrix[i][j] = A -> matrix[i][j] - B -> matrix[i][j];
            }
        }
    }

    return flag_fail;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result)
{
    int flag_fail = SUCCESS;

    if(A -> matrix != NULL)
    {
        s21_create_matrix(A -> rows, A -> columns, result);

        for (int i = 0; i < A -> rows; i++)
        {
            for (int j = 0; j < A -> columns; j++)
            {
                result -> matrix[i][j] = A -> matrix[i][j] * number;
            }
        }
    }
    else 
    {
        flag_fail = FAILURE;
    }

    return flag_fail;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result)
{
    int flag_fail = SUCCESS;
    if(A -> columns != B -> rows || A -> matrix == NULL || B -> matrix == NULL)
    {
        flag_fail = FAILURE;
    }
    else
    {
        s21_create_matrix(A -> rows, B -> columns, result);
        for (int i = 0; i < A -> rows; i++)
        {
            for (int j = 0; j < B -> columns; j++)
            {
                result -> matrix[i][j] = 0;
                for (int k = 0; k < A -> columns; k++)
                {
                    result -> matrix[i][j] += A -> matrix[i][k] * B -> matrix[k][j];
                }
            }
        }
    }
    return flag_fail;
}

int s21_transpose(matrix_t *A, matrix_t *result)
{
    int flag_fail = SUCCESS;

    if(A -> matrix == NULL)
    {
        flag_fail = FAILURE;
    }
    else
    {
        s21_create_matrix(A -> columns, A -> rows, result);

        for (int i = 0; i < A -> columns; i++)
        {
            for (int j = 0; j < A -> rows; j++)
            {
                result -> matrix[i][j] = A -> matrix[j][i];
            }
        }
    }

    return flag_fail;
}

int s21_calc_complements(matrix_t *A, matrix_t *result)
{
    
}