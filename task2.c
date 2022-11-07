#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

#define N 30

// Переменная для хранения максимального размера вводимой строки
#define BUFFER_SIZE 256

void print_menu()
{
    printf("1. Начать работу\n2. Выход\nВвдите значение: ");
}

void print_submenu()
{
    printf("1. Ручной ввод\n2. Заполнение случайными числами\n3. Выход\nВвдите значение: ");
}

void print_double_arr(size_t size, double parr[size])
{
    printf("\n==== ==== ==== ====\nМассив целочисленных: \n");
    for (size_t i = 0UL; i < size; i++)
    {
        printf("parr[%ld] = %f\n", i, parr[i]);
    }
    printf("==== ==== ==== ====\n\n");
}

// Изменяет исходный массив 'parr'
// Если элемент отрицательный -> замените его на его квадратное значение
void replace_negative_to_square(size_t size, double parr[size])
{
    for (size_t i = 0UL; i < size; i++)
    {
        if (parr[i] < 0)
            parr[i] *= parr[i];
    }
}

// Возвращает число, введённое пользователем
// Обрабатывает возможный ввод символов или строки
double input_double()
{
    // Инициализация массива 256-ью нулями
    char buffer[BUFFER_SIZE] = {0};

    // Пользователь вводит строку
    scanf("%s", buffer);

    // Функция библиотеки C double atof(const char *str) преобразует
    // строковый аргумент str в число с плавающей запятой (тип double)
    // Эта функция возвращает преобразованное число с плавающей запятой в виде двойного значения.
    // Если корректное преобразование не может быть выполнено, оно возвращает ноль (0.0).
    while (atof(buffer) == 0.0)
    {
        printf("Вы ввели не число. Попробуйте снова: ");
        scanf("%s", buffer);
    }

    // Строка преобразуется в число с помощью atoi() (alpha to float/double)
    // Затем возвращается целочисленное значение
    return atof(buffer);
}

// Заполняет массив пользовательскими значениями
void arr_input_manual(size_t size, double parr[size])
{
    for (size_t i = 0; i < size; i++)
    {
        printf("parr[%ld] = ", i);
        parr[i] = input_double();
    }
}

// Возвращает массив, который заполнен случайными числами
void arr_input_rndm(size_t size, double parr[size])
{
    srand(time(NULL));

    // Заполнение массива случайными целочисленными значениями
    for (size_t i = 0; i < size; i++)
    {
        parr[i] = (double)rand() / RAND_MAX * 6.0 - 5.0;
    }
}

// Возвращает "true", если последовательность 'parr' неубывающая
// В противном случае - "false"
bool is_non_decreasing_sequence(size_t size, double parr[size])
{
    bool flag = true;

    for (size_t i = 0UL; i < size; i++)
        if ((parr[i] > parr[i + 1]) && ((i + 1) < N))
            flag = false;

    return flag;
}

// Возвращает сумму всех элементов в последовательности
double sum_elems_in_arr(size_t size, double parr[size])
{
    double sum = 0.0;

    for (size_t i = 0; i < size; i++)
        sum += parr[i];

    return sum;
}

// Возвращает произведение всех элементов в последовательности
double product_elems_in_arr(size_t size, double parr[size])
{
    double product = 1.0;

    for (size_t i = 0UL; i < size; i++)
        product *= parr[i];

    return product;
}

// Выводит сумму элементов, если 'parr' является неубывающей последовательностью
// В противном случае печатается произведение элементов
void print_results_of_cheking(size_t size, double parr[size])
{
    if (is_non_decreasing_sequence(size, parr))
        printf("Сумма всех элементов в последовательности = %f\n", sum_elems_in_arr(size, parr));
    else
        printf("Произведение всех элементов в последовательности = %f\n", product_elems_in_arr(size, parr));
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
void perform_some_functionality(size_t size)
{
    for (;;)
    {
        print_menu();
        enum Menu input_menu = (int)input_double();

        switch (input_menu)
        {
        case start_menu:
        {
            bool flag = false;

            while (flag != true)
            {
                print_submenu();
                enum subMenu input_submenu;
                input_submenu = (int)input_double();

                switch (input_submenu)
                {
                case manual_submenu:
                {
                    double parr_man[size];
                    arr_input_manual(size, parr_man);
                    print_double_arr(size, parr_man);
                    replace_negative_to_square(size, parr_man);
                    print_double_arr(size, parr_man);
                    print_results_of_cheking(size, parr_man);
                    break;
                }
                case random_submenu:
                {
                    double parr_rdm[size];
                    arr_input_rndm(size, parr_rdm);
                    print_double_arr(size, parr_rdm);
                    replace_negative_to_square(size, parr_rdm);
                    print_double_arr(size, parr_rdm);
                    print_results_of_cheking(size, parr_rdm);
                    break;
                }
                case exit_submenu:
                {
                    printf("Выход из подменю ...\n");
                    flag = true;
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
    perform_some_functionality(N);

    return 0;
}
