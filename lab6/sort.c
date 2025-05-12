#include "sort.h"

// Функция для сортировки студентов по убыванию общего балла (сортировка выбором)
void selectSort(struct Student students[], int n) {
    for (int i = 0; i < n; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            if (students[j].total > students[k].total) {
                k = j;
            }
        }
        if (k != i) {
            // Меняем местами студентов
            struct Student temp = students[i];
            students[i] = students[k];
            students[k] = temp;
        }
    }
}

// Функция сортировки подсчетом
void CountingSort(struct Student students[], int n) {
    int max_score = 0;
    for (int i = 0; i < n; i++) {
        if (students[i].total > max_score) {
            max_score = students[i].total;
        }
    }

    // Создаем массив для подсчета
    int *count = (int *)malloc((max_score + 1) * sizeof(int));
    if (count == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для count\n");
        return; // Обработка ошибки выделения памяти
    }

    for (int i = 0; i <= max_score; i++) {
        count[i] = 0;
    }

    // Подсчитываем количество студентов для каждого балла
    for (int i = 0; i < n; i++) {
        count[students[i].total]++;
    }

    // Создаем массив для хранения отсортированных студентов
    struct Student *output = (struct Student *)malloc(n * sizeof(struct Student));
    if (output == NULL) {
        fprintf(stderr, "Ошибка выделения памяти для output\n");
        free(count); // Освобождаем выделенную ранее память
        return; // Обработка ошибки выделения памяти
    }

    int index = 0;
    for (int i = max_score; i >= 0; i--) {
        while (count[i] > 0) {
            for (int j = 0; j < n; j++) {
                if (students[j].total == i) {
                    output[index] = students[j];
                    index++;
                    count[i]--;
                    break;  // Важно: выходим из внутреннего цикла после нахождения студента
                }
            }
        }
    }

    // Копируем отсортированный массив обратно в students
    for (int i = 0; i < n; i++) {
        students[i] = output[i];
    }

    // Освобождаем выделенную память
    free(count);
    free(output);
}
