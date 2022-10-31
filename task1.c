#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>

#define z1 0.14
#define t1 0.53
#define N 30

// Макросы для вычисления следующего числа последовательности z_i и t_i
#define NEXT_Z(z, t) sin(z) + 2 * t
#define NEXT_T(z, t) t + z *sin(z)

// Предварительное объявление функций, чтобы можно было вызывать
// в 'calc_zn' функцию 'calc_tn', которая объявлена позже
double calc_zn(double z, const double t, int n);
double calc_tn(double z, const double t, int n);

// Возвращает следующий член последовательности z_i
double calc_zn(double z, double t, int n)
{
    // Инициализация переменных результата вычисления
    // следующих членов z_i и t_i
    double next_z = NEXT_Z(z, t), next_t = NEXT_T(z, t);

    // Если в последовательности один член, то есть
    // n = 1, то возвращается изначальное значение, то есть z_1
    if (n == 1)
        return z;
    // Если в последовательности два члена, то
    // вычисленное следующее, то есть, если есть z_1, 
    // то возвращается z_2
    else if (n == 2)
        return next_z;
    // В ином случае вычисляется и возвращается
    // следующий член последовательности
    else
    {
        return calc_zn(next_z, next_t, n - 1);
    }
}

// Возвращает следующий член последовательности t_i
double calc_tn(double z, double t, int n)
{
    double next_z = NEXT_Z(z, t), next_t = NEXT_T(z, t);

    if (n == 1)
        return t;
    else if (n == 2)
        return next_t;
    else
    {
        return calc_tn(next_z, next_t, n - 1);
    }
}

// Печатает n-ные члены последовательности
void print_zn_tn(int n)
{
    double z_n = calc_zn(z1, t1, n);
    double t_n = calc_tn(z1, t1, n);

    printf("z_%d = %lf\nt_%d = %lf\n", n, z_n, n, t_n);
}

int main()
{
    // Подключение локализации русского языка
    setlocale(LC_ALL, "rus");

    // Функция вывода на экран N членов последовательностей z_i и t_i
    print_zn_tn(N);

    return 0;
}