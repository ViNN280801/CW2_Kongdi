#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 30

void print_menu()
{
    printf("1. Manual input\n2. Random input\n3. Exit\nEnter the value: ");
}

void print_int_arr(const int *parr)
{
    printf("\n==== ==== ==== ====\nArray of integers: \n");
    for (int i = 0; i < N; i++)
    {
        printf("parr[%d] = %d\n", i, parr[i]);
    }
    printf("==== ==== ==== ====\n\n");
}

// Returns "true" if memory for array was allocated correctly
// Otherwise returns "false"
bool is_allocated(int *p)
{
    return (!p) ? false : true;
}

// Allocates memory for integer array with cheking on correctness
int *alloc_mem_int_arr()
{
    int *parr_rdm = (int *)calloc(N, sizeof(int));

    if (!is_allocated(parr_rdm))
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

// Changes original 'parr' array
// If element is negative -> replace it with it's square value
void replace_negative_to_square(int *parr)
{
    for (int i = 0; i < N; i++)
    {
        if (parr[i] < 0)
            parr[i] *= parr[i];
    }
}

// Returns an array, which is filled with a manually entered values
int *arr_input_manual()
{
    // Allocating memory (30 * 4 bytes (default int size))
    int *parr = (int *)calloc(N, sizeof(int));

    // Checking correctness of allocating memory
    if (!parr)
        return NULL;

    for (int i = 0; i < N; i++)
    {
        printf("parr[%d] = ", i);
        scanf("%d", &parr[i]);
    }

    return parr;
}

// Returns an array, which is filled with a random numbers
int *arr_input_rndm()
{
    srand(time(NULL));
    int *parr = (int *)calloc(N, sizeof(int));

    if (!parr)
        return NULL;

    // Filling array with random integer values
    for (int i = 0; i < N; i++)
    {
        parr[i] = rand() % 5 - 5;
    }

    return parr;
}

// Returns "true" if 'parr' sequence is non-decreasing
// Otherwise - "false"
bool is_non_decreasing_sequence(int *parr)
{
    bool flag = true;

    for (int i = 0; i < N; i++)
    {
        if ((parr[i] > parr[i + 1]) && ((i + 1) < N))
            flag = false;
    }

    return flag;
}

// Returns sum of all elements in a sequence
int sum_elems_in_arr(int *parr)
{
    int sum = 0;

    for (int i = 0; i < N; i++)
    {
        sum += parr[i];
    }

    return sum;
}

// Returns product of all elements in a sequence
unsigned long long product_elems_in_arr(int *parr)
{
    long long product = 1;

    for (int i = 0; i < N; i++)
    {
        product *= parr[i];
    }

    return product;
}

// Prints sum of elements if 'parr' is non-decreasing sequence
// Otherwise prints product of elements
void print_results_of_cheking(int *parr)
{
    if (is_non_decreasing_sequence(parr))
        printf("Sum of elements in the sequence = %d\n", sum_elems_in_arr(parr));
    else
        printf("Product of elements in the sequence = %llu\n", product_elems_in_arr(parr));
}

// Perform some functionality which is set by 'input' variable
void menu(int input)
{
    switch (input)
    {
    case 1:
    {
        int *parr_man = alloc_mem_int_arr();
        parr_man = arr_input_manual();
        print_int_arr(parr_man);
        replace_negative_to_square(parr_man);
        print_int_arr(parr_man);
        print_results_of_cheking(parr_man);
        dealloc_mem_int_arr(parr_man);
        break;
    }
    case 2:
    {
        int *parr_rdm = alloc_mem_int_arr();
        parr_rdm = arr_input_rndm();
        print_int_arr(parr_rdm);
        replace_negative_to_square(parr_rdm);
        print_int_arr(parr_rdm);
        print_results_of_cheking(parr_rdm);
        dealloc_mem_int_arr(parr_rdm);
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