    #include "s21_matrix.h"
    #include "s21_support_matrix.c"

    int main()
    {
        matrix_t result = {NULL, 3, 3};
        int rows = 1;
        int columns = 1;
        int count = 1;
        double res = 0.0;
        s21_create_matrix(3, 3, &result);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                result.matrix[i][j] = count++; 
            }
        }



        s21_determinant(&result, &res);
        printf("%f", res);
    }


    int s21_create_matrix(int rows, int columns, matrix_t *result)
    {

        result -> matrix = (double **)malloc(rows * sizeof(double *));

        for (int i = 0; i < rows; i++)
        {
            result -> matrix[i] = (double *) malloc (columns * sizeof(double));
        }

        s21_set_null_matrix(result);

    }

    void s21_remove_matrix(matrix_t *A)
    {
        if(s21_check_matrix(A))
        {
            for (int i = 0; i < A -> rows; i++)
            {
                free(A -> matrix[i]);
            }
            free(A -> matrix);
        }
    }

    int s21_eq_matrix(matrix_t *A, matrix_t *B)
    {
        int flag_fail = SUCCESS;

        if(!s21_size_comparison(A, B) || !s21_check_matrix(A) || !s21_check_matrix(B))
        {
            flag_fail = FAILURE;
        }
        else
        {
            for (int i = 0; i < A -> rows; i++)
            {
                for (int j = 0; j < A -> columns; j++)
                {
                    if(A -> matrix[i][j] != B -> matrix[i][j] || !s21_compare_digits(A -> matrix[i][j], B -> matrix[i][j]))
                    {
                        flag_fail = FAILURE;
                    }
                }
            }
        }
        
        return flag_fail;
    }

    int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result)
    {
        int flag_fail = SUCCESS;

        if(!s21_eq_matrix(A, B) || !s21_check_matrix(A) || !s21_check_matrix(B))
        {
            flag_fail = FAILURE;
        }
        else
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
        int flag_fail = SUCCESS;

        if(!s21_eq_matrix(A, B) || !s21_check_matrix(A) || !s21_check_matrix(B))
        {
            flag_fail = FAILURE;
        }
        else
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
        int flag_fail = s21_check_matrix(A);

        if(flag_fail)
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

        if(!s21_check_matrix(A))
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
        int flag_fail = SUCCESS;
        double result_determinant = 0;

        if(!s21_check_matrix(A) || !s21_square_matrix(A))
        {
            flag_fail = FAILURE;
        }
        else
        {
            matrix_t minor = {0};
            s21_create_matrix(A -> rows, A -> columns ,result);

            for (int i = 0; i < A -> rows; i++)
            {
                for (int j = 0; j < A -> rows; j++)
                {
                    double alg_add = 1.0f;

                    s21_new_matrix_for_minor(A -> rows, i, j, A -> columns, &minor, A);
                    if((i + j) % 2 == 1)
                    {
                        alg_add = -1.0f;
                    }
                    
                    s21_determinant(&minor, &result_determinant);

                    result -> matrix[i][j] = alg_add * result_determinant;

                    s21_remove_matrix(&minor);
                }
            }
        }

        return flag_fail;
    }


    int s21_determinant(matrix_t *A, double *result)
    {
        int flag_fail = SUCCESS;
        int minor_size = A -> rows;
        int alg_add = 1;

        if (!s21_check_matrix(A) || !s21_square_matrix(A))
        {
            flag_fail = FAILURE;
        }
        else
        {
            if(A -> rows == 1)
            {
                *result = A -> matrix[0][0];
            }
            else if (A -> rows == 2)
            {
                *result = (A -> matrix[0][0] * A -> matrix[1][1]) - (A -> matrix[1][0] * A -> matrix[0][1]);
            }
            else if(A -> rows > 2)
            {
                for(int i = 0; i < A -> rows; i++)
                {
                    matrix_t minor = {0};

                    s21_new_matrix_for_minor(minor_size, minor_size, 0, i, &minor, A);

                    *result += alg_add * minor.matrix[0][i] * s21_determinant(&minor, result);
                    s21_remove_matrix(&minor);
                    alg_add = -alg_add;
                }
            }
        }

        return flag_fail;
    }

    int s21_inverse_matrix(matrix_t *A, matrix_t *result)
    {
        int flag_fail = SUCCESS;

        if(!s21_square_matrix || !s21_check_matrix)
        {
            flag_fail = FAILURE;
        }
        else
        {
            double determinant = 0;
            s21_determinant(A, &determinant);

            if(determinant == 0.0f)
            {
                flag_fail = FAILURE;
            }
            else
            {
                matrix_t alg_matrix = {0};
                
                s21_create_matrix(A -> rows, A -> rows, &alg_matrix);
                s21_calc_complements(A, &alg_matrix);
                
                matrix_t alg_matrix_transpose = {0};

                s21_transpose(&alg_matrix, &alg_matrix_transpose);
            }
        }

        return flag_fail;
    }