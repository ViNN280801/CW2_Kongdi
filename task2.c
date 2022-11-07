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
    printf("1. Ручной ввод\n2. Заполнение случайными числами\n3. Выход\nВвдите значение: ");
}

void print_int_arr(int size, int parr[size])
{
    printf("\n==== ==== ==== ====\nМассив целочисленных: \n");
    for (int i = 0; i < size; i++)
    {
        printf("parr[%d] = %d\n", i, parr[i]);
    }
    printf("==== ==== ==== ====\n\n");
}

// Изменяет исходный массив 'parr'
// Если элемент отрицательный -> замените его на его квадратное значение
void replace_negative_to_square(int size, int parr[size])
{
    for (int i = 0; i < size; i++)
    {
        if (parr[i] < 0)
            parr[i] *= parr[i];
    }
}

// Возвращает число, введённое пользователем
// Обрабатывает возможный ввод символов или строки
int input_int()
{
    // Инициализация массива 256-ью нулями
    char buffer[BUFFER_SIZE] = {0};

    // Пользователь вводит строку
    scanf("%s", buffer);

    // Если функция atoi() возвращает 0, т.е.
    // ей не удалось преобразовать введённую строку в число,
    // выводим сообщение и просим заново ввести число
    while (atoi(buffer) == 0)
    {
        printf("Вы ввели не число. Попробуйте снова: ");
        scanf("%s", buffer);
    }

    // Строка преобразуется в число с помощью atoi() (alpha to numeric)
    // Затем возвращается целочисленное значение
    return atoi(buffer);
}

// Заполняет массив пользовательскими значениями
void arr_input_manual(int size, int parr[size])
{
    for (int i = 0; i < size; i++)
    {
        printf("parr[%d] = ", i);
        parr[i] = input_int();
    }
}

// Возвращает массив, который заполнен случайными числами
void arr_input_rndm(int size, int parr[size])
{
    srand(time(NULL));

    // Заполнение массива случайными целочисленными значениями
    for (int i = 0; i < size; i++)
    {
        parr[i] = rand() % 5 - 5;
    }
}

// Возвращает "true", если последовательность 'parr' неубывающая
// В противном случае - "ложь"
bool is_non_decreasing_sequence(int size, int parr[size])
{
    bool flag = true;

    for (int i = 0; i < size; i++)
        if ((parr[i] > parr[i + 1]) && ((i + 1) < N))
            flag = false;

    return flag;
}

// Возвращает сумму всех элементов в последовательности
int sum_elems_in_arr(int size, int parr[size])
{
    int sum = 0;

    for (int i = 0; i < size; i++)
        sum += parr[i];

    return sum;
}

// Возвращает произведение всех элементов в последовательности
unsigned long long product_elems_in_arr(int size, int parr[size])
{
    unsigned long long product = 1;

    for (int i = 0; i < size; i++)
        product *= parr[i];

    return product;
}

// Выводит сумму элементов, если 'parr' является неубывающей последовательностью
// В противном случае печатается произведение элементов
void print_results_of_cheking(int size, int parr[size])
{
    if (is_non_decreasing_sequence(size, parr))
        printf("Сумма всех элементов в последовательности = %d\n", sum_elems_in_arr(size, parr));
    else
        printf("Произведение всех элементов в последовательности = %llu\n", product_elems_in_arr(size, parr));
}

// Выполняет некоторую функциональность,
// которая задается переменной 'input'
void menu(int input, int size)
{
    switch (input)
    {
    case 1:
    {
        int parr_man[size];
        arr_input_manual(size, parr_man);
        print_int_arr(size, parr_man);
        replace_negative_to_square(size, parr_man);
        print_int_arr(size, parr_man);
        print_results_of_cheking(size, parr_man);
        break;
    }
    case 2:
    {
        int parr_rdm[size];
        arr_input_rndm(size, parr_rdm);
        print_int_arr(size, parr_rdm);
        replace_negative_to_square(size, parr_rdm);
        print_int_arr(size, parr_rdm);
        print_results_of_cheking(size, parr_rdm);
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
        input = input_int();
        menu(input, N);
    }

    return 0;
}
