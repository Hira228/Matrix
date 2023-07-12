    #include "s21_matrix.h"
    #include "s21_support_matrix.c"

// 0 - ОК
// 1 - Ошибка, неправильная матрица
// 2 - Ошибка расчета (несоответствие размеров матриц; матрица, для которой
//     невозможно произвести расчеты и т.д.)

//  EQ MATRIX 
//  SUCCESS 1
//  FAILURE 0

int main()
{
        matrix_t result = {NULL, 4, 4};
        double res = 0.f;
        s21_create_matrix(4, 4, &result);
        result.matrix[0][0] = 1.f;
        result.matrix[0][1] = 5.f;
        result.matrix[0][2] = 1.f;
        result.matrix[0][3] = 3.f;
        result.matrix[1][0] = 2.f;
        result.matrix[1][1] = 6.f;
        result.matrix[1][2] = 1.f;
        result.matrix[1][3] = 2.f;
        result.matrix[2][0] = 9.f;
        result.matrix[2][1] = 1.f;
        result.matrix[2][2] = 4.f;
        result.matrix[2][3] = 5.f;
        result.matrix[3][0] = 1.f;
        result.matrix[3][1] = 3.f;
        result.matrix[3][2] = 7.f;
        result.matrix[3][3] = 8.f;

        // for (int i = 0; i < 4; i++)
        // {
        //     for (int j = 0; j < 4; j++)
        //     {
        //         result.matrix[i][j] =rand () % 5; 
        //     }
        // }  
        for(int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                printf("%lf\t", result.matrix[i][j]);
            }
            printf("\n");
        }

        matrix_t minor = {0};
        s21_new_matrix_for_minor(&result, &minor, 3, 0, 0);
        printf("\n");
        for(int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("%lf\t", minor.matrix[i][j]);
            }
            printf("\n");
        }
        s21_determinant(&result, &res);
        printf("\n%lf\n", res);
}


int s21_create_matrix(int rows, int columns, matrix_t *result)
{
    int flag_fail = 0;

    if(rows <= 0 && columns <= 0)
    {
       flag_fail = 1;
    }
    else
    {
        result -> rows = rows;
        result -> columns = columns;
            
        result -> matrix = (double **)malloc(rows * sizeof(double *));

        for (int i = 0; i < rows; i++)
        {
            result -> matrix[i] = (double *) malloc (columns * sizeof(double));
        }

        s21_set_null_matrix(result);
    }
        
    return flag_fail;
}

void s21_remove_matrix(matrix_t *A)
{
    if(!s21_check_null_matrix(A))
    {
        for (int i = 0; i < A -> rows; i++)
        {
            free(A -> matrix[i]);
        }
        
        free(A -> matrix);
        
        A -> matrix     = NULL;
        A -> rows       = 0;
        A -> columns    = 0;
    }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B)
{
    int flag_fail = SUCCESS;

    if(s21_incorrect_matrix(A) || s21_incorrect_matrix(B))
    {
        flag_fail = FAILURE;
    }
    else if(s21_size_comparison(A, B) || s21_check_null_matrix(A) || s21_check_null_matrix(B))
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
    int flag_fail = 0;

    if(s21_check_null_matrix(A) || s21_check_null_matrix(B))      flag_fail = 1;
        
    else if(s21_incorrect_matrix(A) || s21_incorrect_matrix(B))   flag_fail = 1;
        
    else if(!s21_size_comparison(A, B))                           flag_fail = 2;
        
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
    int flag_fail = 0;

    if(s21_check_null_matrix(A) || s21_check_null_matrix(B))      flag_fail = 1;
        
    else if(s21_incorrect_matrix(A) || s21_incorrect_matrix(B))   flag_fail = 1;
        
    else if(!s21_size_comparison(A, B))                           flag_fail = 2;
        
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
    int flag_fail = 0;

    if(s21_check_null_matrix(A) || s21_incorrect_matrix(A) || !result)        flag_fail = 1;
        
    else
    {
        s21_create_matrix(A -> rows, A -> columns, result);

        for (int i = 0; i < A -> rows; i++)
        {
            for (int j = 0; j < A -> columns; j++)
            {
                result -> matrix[i][j] = A -> matrix[i][j] * number;      // ?? насчет проверки на 0
            }
        }
    }

    return flag_fail;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result)
{
    int flag_fail = 0;
        
    if(s21_check_null_matrix(A) || s21_check_null_matrix(B))      flag_fail = 1;
        
    else if(s21_incorrect_matrix(A) || s21_incorrect_matrix(B))   flag_fail = 1;
        
    else if(A -> columns != B -> columns)                         flag_fail = 2;
        
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
    int flag_fail = 0;

    if(s21_check_null_matrix(A) || s21_incorrect_matrix(A))        flag_fail = 1;
     
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
        int flag_fail = 0;
        double result_determinant = 0;

        if(s21_check_null_matrix(A) || s21_incorrect_matrix(A))        flag_fail = 1;
        
        else if(!s21_square_matrix(A) || A -> rows == 1)               flag_fail = 2;
        
        else
        {
            matrix_t minor = {0};

            s21_create_matrix(A -> rows, A -> columns ,result);

            for (int i = 0; i < A -> rows; i++)
            {
                for (int j = 0; j < A -> rows; j++)
                {
                    double alg_add = 1.0f;
                    s21_new_matrix_for_minor(A, &minor, A -> rows - 1, i, j);
                    if((i + j) % 2 == 1)
                    {
                        alg_add = -1.0f;
                    }
                    
                    s21_determinant(&minor, &result_determinant);     

                    result -> matrix[i][j] = alg_add * result_determinant;              /// ?? ПРОВЕРРИТТЬ 

                    s21_remove_matrix(&minor);
                }
            }
        }

        return flag_fail;
}


int s21_determinant(matrix_t *A, double *result)
{
        int flag_fail = 1;
        
        if(s21_check_null_matrix(A) || s21_incorrect_matrix(A))  flag_fail = 1;
        
        else if (!s21_square_matrix(A))                          flag_fail = 2;
        
        else
        {
            *result = s21_determinant_execution(A);
        }
        return flag_fail;
}


int s21_inverse_matrix(matrix_t *A, matrix_t *result)
{
    int flag_fail = 0;
    double determinant = 0;
        
    if(s21_check_null_matrix(A) || !s21_check_matrix(A))                                flag_fail = 1;
        
    else if(!s21_square_matrix(A) || (A -> rows == 1 && A -> matrix[0][0] == 0.0f))     flag_fail = 2;
        
    else
    {
        s21_determinant(A, &determinant);

        if(determinant == 0.0f)
        {
            flag_fail = 2;
        }
        else
        {
            matrix_t alg_matrix = {0};
                
            s21_create_matrix(A -> rows, A -> rows, &alg_matrix);
            s21_calc_complements(A, &alg_matrix);
                
            matrix_t alg_matrix_transpose = {0};
            s21_create_matrix(A -> rows, A -> rows, &alg_matrix_transpose);
            s21_transpose(&alg_matrix, &alg_matrix_transpose);

            for (int i = 0; i < A -> rows; i++)
            {
                for (int j = 0; j < A -> rows; j++)
                {
                        result -> matrix[i][j] = alg_matrix_transpose.matrix[i][j];
                }
            }
            s21_remove_matrix(&alg_matrix);
            s21_remove_matrix(&alg_matrix_transpose);
        }
    }

    return flag_fail;
}