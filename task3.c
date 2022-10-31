#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

#define N 5
#define M 6

void print_int_arr(const int *parr, size_t arr_size)
{
    printf("\n==== ==== ==== ==== ====\nМассив отрицательных значений: \n");
    for (size_t i = 0; i < arr_size; i++)
    {
        printf("parr[%ld] = %d\n", i, parr[i]);
    }
    printf("==== ==== ==== ==== ====\n\n");
}

// Возвращает "true", если память для массива была выделена правильно
// В противном случае возвращает "false"
bool is_alloc_mem_int_arr(int *p)
{
    return (!p) ? false : true;
}

// Выделяет память для целочисленного массива с проверкой правильности
int *alloc_mem_int_arr(size_t alloc_size)
{
    int *parr_rdm = (int *)calloc(alloc_size, sizeof(int));

    if (!is_alloc_mem_int_arr(parr_rdm))
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

void print_menu()
{
    printf("1. Ручной ввод\n2. Заполнение случайными числами\n3. Выход\nВвдите значение: ");
}

void print_int_matrix(int **pp, const char *msg)
{
    // Выделение памяти для 'result_str'
    char *result_str = (char *)calloc(strlen("\n==== ==== ==== ==== ==== ==== ==== ==== ====\n") +
                                          strlen(msg),
                                      sizeof(char));

    // Проверка на правильность выделения памяти
    if (!result_str)
    {
        printf("Can't allocate memory for message string. Exiting with \'-1\' status\n");
        exit(-1);
    }

    // Копирование в 'result_str' строки "\n==== ==== ==== ==== ==== ==== ==== ==== ====\n"
    strcpy(result_str, "\n==== ==== ==== ==== ==== ==== ==== ==== ====\n");

    // Объединение строк сообщения 'msg' и ":\n" в 'result_str'
    strcat(result_str, msg);
    strcat(result_str, ":\n");
    printf("%s", result_str);

    // Простая итерация по матрице по индексам строки и столбца
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

// Возвращает "true", если память матрицы распределена правильно
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

// Выделяет память матрице с проверками на правильность выделения
// Возвращает указатель на матрицу целочисленных значений
int **alloc_mem_matrix()
{
    int **pp = (int **)calloc(N, sizeof(int *));

    if (!pp)
    {
        printf("Ошибка: Память для каждой строки матрицы не может быть выделена. Выход со статусом \'-1\'\n");
        exit(-1);
    }

    for (int row = 0; row < N; row++)
    {
        pp[row] = (int *)calloc(M, sizeof(int));

        if (!pp[row])
        {
            printf("Ошибка: Память для каждой колонки матрицы не может быть выделена. Выход со статусом \'-1\'\n");
            exit(-1);
        }
    }

    if (!is_allocated_mem_matrix(pp))
    {
        printf("Ошибка: Память для матрицы не может быть выделена. Выход со статусом \'-1\'\n");
        exit(-1);
    }

    return pp;
}

// Освобождение памяти двойного указателя 'p'
void dealloc_mem_matrix(int **pp)
{
    for (int row = 0; row < N; row++)
    {
        free(pp[row]);
    }

    free(pp);
    pp = NULL;
}

// Возвращает матрицу, которая заполняется введенными вручную значениями
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

// Возвращает матрицу, которая заполнена случайными числами
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

// Возвращает количество столбцов с отрицательными значениями из матрицы
int count_cols_with_negative(int **pp)
{
    // Инициализирующий счетчик, который будет возвращен в качестве результата
    // и переменная, которая характеризует, что мы уже увеличили
    // количество определенного столбца, в котором хранится отрицательное значение
    int count = 0, used_col = -1;

    // Сперва итерация по столбцам матрицы, затем итерация по строкам
    for (int col = 0; col < M; col++)
    {
        for (int row = 0; row < N; row++)
        {
            // Если найден отрицательный элемент и эти столбцы ранее не встречались
            // запомните его (присвоть ему значение 'used_col')
            // затем увеличьте счетчик столбцов с отрицательными элементами
            if ((pp[row][col] < 0) && (used_col != col))
            {
                used_col = col;
                count++;
            }
        }
    }

    return count;
}

// Возвращает массив 1-го отрицательного значения из каждого столбца матрицы
int *save_1st_negative_col_elems(int **pp)
{
    int used_col = -1, count = 0;
    int *negative_elems = alloc_mem_int_arr((size_t)count_cols_with_negative(pp));

    for (int col = 0; col < M; col++)
    {
        for (int row = 0; row < N; row++)
        {
            // Если найден отрицательный элемент и эти столбцы ранее не встречались
            // запомните его (присвоите ему значение 'used_col')
            // затем увеличьте счетчик столбцов с отрицательными элементами
            // и используйте этот счетчик для заполнения массива 'negative_elems'
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

// Возвращает матрицу из исходной матрицы, где
// 1-й отрицательный элемент в столбце был заменен
// с суммой оставшихся элементов
int **replace_1st_negative_in_col(int **pp)
{
    int used_col = -1;

    for (int col = 0; col < M; col++)
    {
        for (int row = 0; row < N; row++)
        {
            // Если найден отрицательный элемент и эти столбцы ранее не встречались
            // запомните его (присвоите ему значение 'used_col')
            if ((pp[row][col] < 0) && (used_col != col))
            {
                used_col = col;

                int sum = 0;
                for (int k = row; k < N; k++)
                {
                    if ((k + 1) < N)
                        sum += pp[k + 1][used_col];
                }

                // // Нам не нужно менять элемент с индексом последней строки
                if (row != N - 1)
                    pp[row][col] = sum;
            }
        }
    }

    return pp;
}

// Выполняет некоторую функциональность, 
// которая задается переменной 'input'
void menu(int input)
{
    switch (input)
    {
    case 1:
    {
        int **matrix_man = alloc_mem_matrix();
        matrix_man = matrix_input_manual();
        print_int_matrix(matrix_man, "Изначальная матрица");
        print_int_arr(save_1st_negative_col_elems(matrix_man), count_cols_with_negative(matrix_man));
        print_int_matrix(replace_1st_negative_in_col(matrix_man), "Преобразованная матрица");
        dealloc_mem_matrix(matrix_man);
        break;
    }
    case 2:
    {
        int **matrix_rdm = alloc_mem_matrix();
        matrix_rdm = matrix_input_random();
        print_int_matrix(matrix_rdm, "Изначальная матрица");
        print_int_arr(save_1st_negative_col_elems(matrix_rdm), count_cols_with_negative(matrix_rdm));
        print_int_matrix(replace_1st_negative_in_col(matrix_rdm), "Преобразованная матрица");
        dealloc_mem_matrix(matrix_rdm);
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