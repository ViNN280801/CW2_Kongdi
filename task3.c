#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define N 5
#define M 6

// Переменная для хранения максимального размера вводимой строки
#define BUFFER_SIZE 256

void print_double_arr(size_t arr_size, double parr[arr_size])
{
    printf("\n==== ==== ==== ==== ====\nМассив отрицательных значений: \n");
    for (size_t i = 0UL; i < arr_size; i++)
    {
        printf("arr[%ld] = %f\n", i, parr[i]);
    }
    printf("==== ==== ==== ==== ====\n\n");
}

void print_menu()
{
    printf("1. Начать работу\n2. Выход\nВвдите значение: ");
}

void print_submenu()
{
    printf("1. Ручной ввод\n2. Заполнение случайными числами\n3. Выход\nВвдите значение: ");
}

void print_double_matrix(size_t rows, size_t cols, double matrix[rows][cols])
{
    // Простая итерация по матрице по индексам строки и столбца
    for (size_t row = 0UL; row < rows; row++)
    {
        for (size_t col = 0UL; col < cols; col++)
        {
            printf("%f\t", matrix[row][col]);
        }
        printf("\n");
    }
}

// Возвращает число, введённое пользователем
// Обрабатывает возможный ввод символов или строки
double input_double()
{
    // Инициализация массива 256-ью нулями
    char buffer[BUFFER_SIZE] = {'0'};

    // Пользователь вводит строку
    scanf("%s", buffer);

    // Если функция atoi() возвращает 0, т.е.
    // ей не удалось преобразовать введённую строку в число,
    // выводим сообщение и просим заново ввести число
    while (atof(buffer) == 0.0)
    {
        printf("Вы ввели не число. Попробуйте снова: ");
        scanf("%s", buffer);
    }

    // Строка преобразуется в число с помощью atoi() (alpha to numeric)
    // Затем возвращается целочисленное значение
    return atof(buffer);
}

// Заполняет пользовательскими числами переданную как аргумент матрицу
void matrix_input_manual(size_t rows, size_t cols, double matrix[rows][cols])
{
    for (size_t row = 0UL; row < rows; row++)
    {
        for (size_t col = 0UL; col < cols; col++)
        {
            printf("матрица[%ld][%ld] = ", row, col);
            matrix[row][col] = input_double();
        }
    }
}

// Заполняет случайными числами переданную как аргумент матрицу
void matrix_input_random(size_t rows, size_t cols, double matrix[rows][cols])
{
    srand(time(NULL));

    for (size_t row = 0UL; row < N; row++)
    {
        for (size_t col = 0UL; col < M; col++)
        {
            matrix[row][col] = (double)rand() / RAND_MAX * 10.0 - 5.0;
        }
    }
}

// Возвращает количество столбцов с отрицательными значениями из матрицы
int count_cols_with_negative(size_t rows, size_t cols, double matrix[rows][cols])
{
    // Инициализирующий счетчик, который будет возвращен в качестве результата
    // и переменная, которая характеризует, что мы уже увеличили
    // количество определенного столбца, в котором хранится отрицательное значение
    int count = 0, used_col = -1;

    // Сперва итерация по столбцам матрицы, затем итерация по строкам
    for (size_t col = 0UL; col < M; col++)
    {
        for (size_t row = 0UL; row < N; row++)
        {
            // Если найден отрицательный элемент и эти столбцы ранее не встречались
            // запомните его (присвоть ему значение 'used_col')
            // затем увеличьте счетчик столбцов с отрицательными элементами
            if ((matrix[row][col] < 0) && (used_col != (int)col))
            {
                used_col = col;
                count++;
            }
        }
    }

    return count;
}

// Заполняет массив 'dest' 1-ым отрицательным значением из каждого столбца матрицы
void save_1st_negative_col_elems(size_t rows, size_t cols, double matrix[rows][cols], double *dest)
{
    int used_col = -1, count = 0;

    for (size_t col = 0UL; col < cols; col++)
    {
        for (size_t row = 0UL; row < rows; row++)
        {
            // Если найден отрицательный элемент и эти столбцы ранее не встречались
            // запомните его (присвоите ему значение 'used_col')
            // затем увеличьте счетчик столбцов с отрицательными элементами
            // и используйте этот счетчик для заполнения массива 'negative_elems'
            if ((matrix[row][col] < 0) && (used_col != (int)col))
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
void replace_1st_negative_in_col(size_t rows, size_t cols, double matrix[rows][cols])
{
    size_t used_col = -1;

    for (size_t col = 0UL; col < cols; col++)
    {
        for (size_t row = 0UL; row < rows; row++)
        {
            // Если найден отрицательный элемент и эти столбцы ранее не встречались
            // запоминаем его (присваиваем ему значение 'used_col')
            if ((matrix[row][col] < 0.0) && (used_col != col))
            {
                used_col = col;

                double sum = 0.0;
                for (size_t k = row; k < rows; k++)
                {
                    if ((k + 1UL) < rows && ((used_col + 1UL) < cols))
                        sum += matrix[k + 1UL][used_col + 1UL];
                }

                // Нам не нужно менять элемент с индексом последней строки
                if (row != (N - 1))
                    matrix[row][col] = sum;
            }
        }
    }
}

enum Menu
{
    start_menu = 1,
    exit_menu = 2
};

enum subMenu
{
    manual_submenu = 1,
    random_submenu = 2,
    exit_submenu = 3
};

// Выполняет некоторую функциональность,
// которая задается переменной 'input'
void perform_some_functionality(size_t rows, size_t cols)
{
    for (;;)
    {
        print_menu();
        enum Menu input_menu = (int)input_double();

        switch (input_menu)
        {
        case start_menu:
        {
            int flag = 0;

            while (flag != 1)
            {
                print_submenu();
                enum subMenu input_submenu;
                input_submenu = (int)input_double();

                switch (input_submenu)
                {
                case manual_submenu:
                {
                    double matrix_man[rows][cols];
                    matrix_input_manual(rows, cols, matrix_man);
                    printf("Изначальная матрица:\n");
                    print_double_matrix(rows, cols, matrix_man);
                    double neg_arr[count_cols_with_negative(rows, cols, matrix_man)];
                    save_1st_negative_col_elems(rows, cols, matrix_man, neg_arr);
                    print_double_arr(count_cols_with_negative(rows, cols, matrix_man), neg_arr);
                    printf("Преобразованная матрица:\n");
                    replace_1st_negative_in_col(rows, cols, matrix_man);
                    print_double_matrix(rows, cols, matrix_man);
                    break;
                }
                case random_submenu:
                {
                    double matrix_rdm[rows][cols];
                    matrix_input_random(rows, cols, matrix_rdm);
                    printf("Изначальная матрица:\n");
                    print_double_matrix(rows, cols, matrix_rdm);
                    double neg_arr[count_cols_with_negative(rows, cols, matrix_rdm)];
                    save_1st_negative_col_elems(rows, cols, matrix_rdm, neg_arr);
                    print_double_arr(count_cols_with_negative(rows, cols, matrix_rdm), neg_arr);
                    printf("Преобразованная матрица:\n");
                    replace_1st_negative_in_col(rows, cols, matrix_rdm);
                    print_double_matrix(rows, cols, matrix_rdm);
                    break;
                }
                case exit_submenu:
                {
                    printf("Выход из подменю ...\n");
                    flag = 1;
                    break;
                }
                default:
                    printf("Неверный ввод, попробуйте снова\n");
                    break;
                }
            }
            break;
        }
        case exit_menu:
        {
            printf("Выход из программы ...\n");
            exit(1);
        }
        default:
            printf("Неверный ввод, попробуйте снова\n");
            break;
        }
    }
}

int main()
{
    // Подключение локализации русского языка
    setlocale(LC_ALL, "rus");
    perform_some_functionality(N, M);

    return 0;
}