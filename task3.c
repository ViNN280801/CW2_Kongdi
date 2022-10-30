#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 5
#define M 6

void print_int_arr(const int *parr, size_t arr_size)
{
    printf("\n==== ==== ==== ==== ====\nArray of negative values: \n");
    for (size_t i = 0; i < arr_size; i++)
    {
        printf("parr[%ld] = %d\n", i, parr[i]);
    }
    printf("==== ==== ==== ==== ====\n\n");
}

// Returns "true" if memory for array was allocated correctly
// Otherwise returns "false"
bool is_alloc_mem_int_arr(int *p)
{
    return (!p) ? false : true;
}

// Allocates memory for integer array with cheking on correctness
int *alloc_mem_int_arr(size_t alloc_size)
{
    int *parr_rdm = (int *)calloc(alloc_size, sizeof(int));

    if (!is_alloc_mem_int_arr(parr_rdm))
    {
        printf("Can't allocate memory for array of integers. Exiting with \'-1\' status\n");
        exit(-1);
    }

    return parr_rdm;
}

// Deallocating memory of 'p' pointer
void dealloc_mem_int_arr(int *p)
{
    free(p);
    p = NULL;
}

void print_menu()
{
    printf("1. Manual input\n2. Random input\n3. Exit\nEnter the value: ");
}

void print_int_matrix(int **pp, const char *msg)
{
    // Allocating memory for 'result_str'
    char *result_str = (char *)calloc(strlen("\n==== ==== ==== ==== ==== ==== ==== ==== ====\n") +
                                          strlen(msg),
                                      sizeof(char));

    // Check if memory allocated correctly
    if (!result_str)
    {
        printf("Can't allocate memory for message string. Exiting with \'-1\' status\n");
        exit(-1);
    }

    // Copying to 'result_str' following string
    strcpy(result_str, "\n==== ==== ==== ==== ==== ==== ==== ==== ====\n");

    // Concatenating message 'msg' and ":\n" strings to 'result_str'
    strcat(result_str, msg);
    strcat(result_str, ":\n");
    printf("%s", result_str);

    // Simple iterating over the matrix by indeces of row and column
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            printf("%d\t", pp[row][col]);
        }
        printf("\n");
    }
    printf("==== ==== ==== ==== ==== ==== ==== ==== ====\n\n");

    free(result_str);
    result_str = NULL;
}

// Return "true" if memory of matrix allocated correctly
bool is_allocated_mem_matrix(int **pp)
{
    for (int row = 0; row < N; row++)
    {
        if (!pp[row])
            return false;
    }
    if (!pp)
        return false;

    return true;
}

// Allocates memory to matrix with checkings on correctness of allocating
// Returns pointer on a matrix of integer values
int **alloc_mem_matrix()
{
    int **pp = (int **)calloc(N, sizeof(int *));

    if (!pp)
    {
        printf("Can't allocate memory for each row of matrix. Exiting with \'-1\' status\n");
        exit(-1);
    }

    for (int row = 0; row < N; row++)
    {
        pp[row] = (int *)calloc(M, sizeof(int));

        if (!pp[row])
        {
            printf("Can't allocate memory for each column of matrix. Exiting with \'-1\' status\n");
            exit(-1);
        }
    }

    if (!is_allocated_mem_matrix(pp))
    {
        printf("Can't allocate memory for matrix. Exiting with \'-1\' status\n");
        exit(-1);
    }

    return pp;
}

// Deallocating memory of 'p' pointer
void dealloc_mem_matrix(int **pp)
{
    for (int row = 0; row < N; row++)
    {
        free(pp[row]);
    }

    free(pp);
    pp = NULL;
}

// Returns a matrix, which is filled with a manually entered values
int **matrix_input_manual()
{
    int **matrix = alloc_mem_matrix();

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            printf("matrix[%d][%d] = ", row, col);
            scanf("%d", &matrix[row][col]);
        }
    }

    return matrix;
}

// Returns a matrix, which is filled with a random numbers
int **matrix_input_random()
{
    int **matrix = alloc_mem_matrix();

    srand(time(NULL));

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            matrix[row][col] = rand() % 10 - 5;
        }
    }

    return matrix;
}

// Returns count of columns with negative values from matrix
int count_cols_with_negative(int **pp)
{
    // Initializing count that will be returned as result
    // and variable thats characterizes that we are already incremented
    // count of certain column which is stores the negative value
    int count = 0, used_col = -1;

    // Firstly iterating by columns of matrix, then iterating by rows
    for (int col = 0; col < M; col++)
    {
        for (int row = 0; row < N; row++)
        {
            // If found negative element and this columns haven't met before
            // remember it (assign it to 'used_col')
            // then increment the counter of columns with negative elems
            if ((pp[row][col] < 0) && (used_col != col))
            {
                used_col = col;
                count++;
            }
        }
    }

    return count;
}

// Returns array of 1st negative values from each column from matrix
int *save_1st_negative_col_elems(int **pp)
{
    int used_col = -1, count = 0;
    int *negative_elems = alloc_mem_int_arr((size_t)count_cols_with_negative(pp));

    for (int col = 0; col < M; col++)
    {
        for (int row = 0; row < N; row++)
        {
            // If found negative element and this columns haven't met before
            // remember it (assign it to 'used_col')
            // then increment the counter of columns with negative elems
            // and use this counter to fill an array 'negative_elems'
            if ((pp[row][col] < 0) && (used_col != col))
            {
                used_col = col;
                negative_elems[count] = pp[row][col];
                count++;
            }
        }
    }

    return negative_elems;
}

// Returns matrix from original matrix, where
// 1st negative element in a column was replaced
// with a sum of remaining elements
int **replace_1st_negative_in_col(int **pp)
{
    int used_col = -1;

    for (int col = 0; col < M; col++)
    {
        for (int row = 0; row < N; row++)
        {
            // If found negative element and this columns haven't met before
            // remember it (assign it to 'used_col')
            if ((pp[row][col] < 0) && (used_col != col))
            {
                used_col = col;

                int sum = 0;
                for (int k = row; k < N; k++)
                {
                    if ((k + 1) < N)
                        sum += pp[k + 1][used_col];
                }

                // We don't need to change element with last row indexz
                if (row != N - 1)
                    pp[row][col] = sum;
            }
        }
    }

    return pp;
}

// Perform some functionality which is set by 'input' variable
void menu(int input)
{
    switch (input)
    {
    case 1:
    {
        int **matrix_man = alloc_mem_matrix();
        matrix_man = matrix_input_manual();
        print_int_matrix(matrix_man, "Original matrix");
        print_int_arr(save_1st_negative_col_elems(matrix_man), count_cols_with_negative(matrix_man));
        print_int_matrix(replace_1st_negative_in_col(matrix_man), "Transformed matrix");
        dealloc_mem_matrix(matrix_man);
        break;
    }
    case 2:
    {
        int **matrix_rdm = alloc_mem_matrix();
        matrix_rdm = matrix_input_random();
        print_int_matrix(matrix_rdm, "Original matrix");
        print_int_arr(save_1st_negative_col_elems(matrix_rdm), count_cols_with_negative(matrix_rdm));
        print_int_matrix(replace_1st_negative_in_col(matrix_rdm), "Transformed matrix");
        dealloc_mem_matrix(matrix_rdm);
        break;
    }
    case 3:
        printf("Exiting ...\n");
        break;
    default:
        printf("Wrong input, try again\n");
        break;
    }
}

int main()
{
    int input = 0;

    while (input != 3)
    {
        print_menu();
        scanf("%d", &input);
        menu(input);
    }

    return 0;
}