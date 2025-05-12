#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "student.h"
#include "sort.h"

#define N 10

int main() {
    struct Student students[N];
    srand(time(NULL));

    // Заполняем массив студентов случайными данными
    for (int i = 0; i < N; i++) {
        char name[64];
        snprintf(name, sizeof(name), "Студент_%d", i + 1);
        int math = rand() % 101;
        int phy = rand() % 101;
        int inf = rand() % 101;
        students[i] = addStudent(name, math, phy, inf);
    }

    // Вывод информации о процессоре (необязательно, но оставил)
    printf("Информация о процессоре:\n");
    system("grep -m 1 'model name' /proc/cpuinfo");
    system("grep -m 1 'cpu MHz' /proc/cpuinfo");

    clock_t start, end;
    double time_spent;

    // Замер времени для сортировки выбором
    start = clock();
    selectSort(students, N);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время работы сортировки выбором: %f секунд\n", time_spent);

    // Заполняем массив студентов случайными данными (чтобы отсортировать несortированный массив)
    for (int i = 0; i < N; i++) {
        char name[64];
        snprintf(name, sizeof(name), "Студент_%d", i + 1);
        int math = rand() % 101;
        int phy = rand() % 101;
        int inf = rand() % 101;
        students[i] = addStudent(name, math, phy, inf);
    }

    // Замер времени для сортировки подсчетом
    start = clock();
    CountingSort(students, N);
    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Время работы сортировки подсчетом: %f секунд\n", time_spent);

    // Вывод размера данных
    printf("Размер данных: %lu байт\n", (unsigned long)(N * sizeof(struct Student))); // Более безопасное преобразование типа

    return 0;
}
