#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

#define N 30

void print_menu()
{
    printf("1. Ручной ввод\n2. Заполнение случайными числами\n3. Выход\nВвдите значение: ");
}

void print_int_arr(const int *parr)
{
    printf("\n==== ==== ==== ====\nМассив целочисленных: \n");
    for (int i = 0; i < N; i++)
    {
        printf("parr[%d] = %d\n", i, parr[i]);
    }
    printf("==== ==== ==== ====\n\n");
}

// Возвращает "true", если память для массива была выделена правильно
// В противном случае возвращает "false"
bool is_allocated(int *p)
{
    return (!p) ? false : true;
}

// Выделяет память для целочисленного массива с проверкой правильности
int *alloc_mem_int_arr()
{
    int *parr_rdm = (int *)calloc(N, sizeof(int));

    if (!is_allocated(parr_rdm))
    {
        printf("Ошибка: Память для массива целочисленных чисел не может быть выделена. Выход со статусом \'-1\'\n");
        exit(-1);
    }

    return parr_rdm;
}

// Освобождение памяти указателя 'p'
void dealloc_mem_int_arr(int *p)
{
    free(p);
    p = NULL;
}

// Изменяет исходный массив 'parr'
// Если элемент отрицательный -> замените его на его квадратное значение
void replace_negative_to_square(int *parr)
{
    for (int i = 0; i < N; i++)
    {
        if (parr[i] < 0)
            parr[i] *= parr[i];
    }
}

// Возвращает массив, который заполняется введенными вручную значениями
int *arr_input_manual()
{
    // Выделение памяти (30 * 4 байта (размер int по умолчанию))
    int *parr = (int *)calloc(N, sizeof(int));

    // Проверка правильности выделения памяти
    if (!parr)
        return NULL;

    for (int i = 0; i < N; i++)
    {
        printf("parr[%d] = ", i);
        scanf("%d", &parr[i]);
    }

    return parr;
}

// Возвращает массив, который заполнен случайными числами
int *arr_input_rndm()
{
    srand(time(NULL));
    int *parr = (int *)calloc(N, sizeof(int));

    if (!parr)
        return NULL;

    // Заполнение массива случайными целочисленными значениями
    for (int i = 0; i < N; i++)
    {
        parr[i] = rand() % 5 - 5;
    }

    return parr;
}

// Возвращает "true", если последовательность 'parr' неубывающая
// В противном случае - "ложь"
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

// Возвращает сумму всех элементов в последовательности
int sum_elems_in_arr(int *parr)
{
    int sum = 0;

    for (int i = 0; i < N; i++)
    {
        sum += parr[i];
    }

    return sum;
}

// Возвращает произведение всех элементов в последовательности
unsigned long long product_elems_in_arr(int *parr)
{
    long long product = 1;

    for (int i = 0; i < N; i++)
    {
        product *= parr[i];
    }

    return product;
}

// Выводит сумму элементов, если 'parr' является неубывающей последовательностью
// В противном случае печатается произведение элементов
void print_results_of_cheking(int *parr)
{
    if (is_non_decreasing_sequence(parr))
        printf("Произведение всех элементов в последовательности = %d\n", sum_elems_in_arr(parr));
    else
        printf("Произведение всех элементов в последовательности = %llu\n", product_elems_in_arr(parr));
}

// Выполняет некоторую функциональность, 
// которая задается переменной 'input'
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
        printf("Выход ...\n");
        break;
    default:
        printf("Неверный ввод, попробуйте снова\n");
        break;
    }
}

int main()
{
    // Подключение локализации русского языка
    setlocale(LC_ALL, "rus");

    int input = 0;

    while (input != 3)
    {
        print_menu();
        scanf("%d", &input);
        menu(input);
    }

    return 0;
}