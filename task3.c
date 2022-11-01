#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <locale.h>

#define N 5
#define M 6

void print_int_arr(int arr_size, int parr[arr_size])
{
    printf("\n==== ==== ==== ==== ====\nМассив отрицательных значений: \n");
    for (int i = 0; i < arr_size; i++)
    {
        printf("arr[%d] = %d\n", i, parr[i]);
    }
    printf("==== ==== ==== ==== ====\n\n");
}

void print_menu()
{
    printf("1. Ручной ввод\n2. Заполнение случайными числами\n3. Выход\nВвдите значение: ");
}

void print_int_matrix(int rows, int cols, int matrix[rows][cols])
{
    // Простая итерация по матрице по индексам строки и столбца
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            printf("%d\t", matrix[row][col]);
        }
        printf("\n");
    }
}

// Заполняет пользовательскими числами переданную как аргумент матрицу
void matrix_input_manual(int rows, int cols, int matrix[rows][cols])
{
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            printf("матрица[%d][%d] = ", row, col);
            scanf("%d", &matrix[row][col]);
        }
    }
}

// Заполняет случайными числами переданную как аргумент матрицу
void matrix_input_random(int rows, int cols, int matrix[rows][cols])
{
    srand(time(NULL));

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            matrix[row][col] = rand() % 10 - 2;
        }
    }
}

// Возвращает количество столбцов с отрицательными значениями из матрицы
int count_cols_with_negative(int rows, int cols, int matrix[rows][cols])
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
            if ((matrix[row][col] < 0) && (used_col != col))
            {
                used_col = col;
                count++;
            }
        }
    }

    return count;
}

// Заполняет массив 'dest' 1-ым отрицательным значением из каждого столбца матрицы
void save_1st_negative_col_elems(int rows, int cols, int matrix[rows][cols], int *dest)
{
    int used_col = -1, count = 0;

    for (int col = 0; col < cols; col++)
    {
        for (int row = 0; row < rows; row++)
        {
            // Если найден отрицательный элемент и эти столбцы ранее не встречались
            // запомните его (присвоите ему значение 'used_col')
            // затем увеличьте счетчик столбцов с отрицательными элементами
            // и используйте этот счетчик для заполнения массива 'negative_elems'
            if ((matrix[row][col] < 0) && (used_col != col))
            {
                used_col = col;
                dest[count] = matrix[row][col];
                count++;
            }
        }
    }   
}

// Изменяет исходную матрицу следующим образом:
// 1-й отрицательный элемент в столбце заменяется на
// сумму оставшихся элементов
void replace_1st_negative_in_col(int rows, int cols, int matrix[rows][cols])
{
    int used_col = -1;

    for (int col = 0; col < rows; col++)
    {
        for (int row = 0; row < cols; row++)
        {
            // Если найден отрицательный элемент и эти столбцы ранее не встречались
            // запомните его (присвоите ему значение 'used_col')
            if ((matrix[row][col] < 0) && (used_col != col))
            {
                used_col = col;

                int sum = 0;
                for (int k = row; k < N; k++)
                {
                    if ((k + 1) < N)
                        sum += matrix[k + 1][used_col];
                }

                // // Нам не нужно менять элемент с индексом последней строки
                if (row != N - 1)
                    matrix[row][col] = sum;
            }
        }
    }
}

// Выполняет некоторую функциональность,
// которая задается переменной 'input'
void menu(int input, int rows, int cols)
{
    switch (input)
    {
    case 1:
    {
        int matrix_man[rows][cols];
        matrix_input_manual(rows, cols, matrix_man);
        printf("Изначальная матрица:\n");
        print_int_matrix(rows, cols, matrix_man);
        printf("Массив:\n");
        int neg_arr[count_cols_with_negative(rows, cols, matrix_man)];
        print_int_arr(count_cols_with_negative(rows, cols, matrix_man), neg_arr);
        printf("Преобразованная матрица:\n");
        print_int_matrix(rows, cols, matrix_man);
        break;
    }
    case 2:
    {
        int matrix_rdm[rows][cols];
        matrix_input_random(rows, cols, matrix_rdm);
        printf("Изначальная матрица:\n");
        print_int_matrix(rows, cols, matrix_rdm);
        printf("Массив:\n");
        int neg_arr[count_cols_with_negative(rows, cols, matrix_rdm)];
        save_1st_negative_col_elems(rows, cols, matrix_rdm, neg_arr);
        print_int_arr(count_cols_with_negative(rows, cols, matrix_rdm), neg_arr);
        printf("Преобразованная матрица:\n");
        print_int_matrix(rows, cols, matrix_rdm);
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
        menu(input, N, M);
    }

    return 0;
}