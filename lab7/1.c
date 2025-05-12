#define _POSIX_C_SOURCE 200112L 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#define MAX 2500 

// ==== ЗАДАНИЕ 7: СИНХРОНИЗАЦИЯ ====

pthread_mutex_t mutex7 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond7 = PTHREAD_COND_INITIALIZER;
int turn7 = 0; // 0 — родитель, 1 — дочерний

void* thread_func7(void* arg) {
    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&mutex7);
        while (turn7 != 1)
            pthread_cond_wait(&cond7, &mutex7);

        printf("Дочерний поток: строка %d\n", i);
        turn7 = 0;
        pthread_cond_signal(&cond7);
        pthread_mutex_unlock(&mutex7);
    }
    return NULL;
}

void task7() {
    printf("\n=== Задание 7: Синхронизированный вывод ===\n");
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func7, NULL);

    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&mutex7);
        while (turn7 != 0)
            pthread_cond_wait(&cond7, &mutex7);

        printf("Родительский поток: строка %d\n", i);
        turn7 = 1;
        pthread_cond_signal(&cond7);
        pthread_mutex_unlock(&mutex7);
    }

    pthread_join(thread, NULL);
}

// ==== ЗАДАНИЕ 8: ПЕРЕМНОЖЕНИЕ МАТРИЦ ====

int **A, **B, **C;
int N, num_threads;

typedef struct {
    int start_row;
    int end_row;
} ThreadData;

void* multiply(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return NULL;
}

void print_matrix(int** M, const char* name) {
    printf("\nМатрица %s:\n", name);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3d ", M[i][j]);
        }
        printf("\n");
    }
}

void allocate_and_fill_matrices() {
    A = malloc(N * sizeof(int*));
    B = malloc(N * sizeof(int*));
    C = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        A[i] = malloc(N * sizeof(int));
        B[i] = malloc(N * sizeof(int));
        C[i] = malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            A[i][j] = B[i][j] = 1;
        }
    }
}

void free_matrices() {
    for (int i = 0; i < N; i++) {
        free(A[i]); free(B[i]); free(C[i]);
    }
    free(A); free(B); free(C);
}

void task8(int size, int threads) {
    N = size;
    num_threads = threads;
    printf("\n=== Задание 8: Перемножение матриц %dx%d потоками: %d ===\n", N, N, threads);

    allocate_and_fill_matrices();

    pthread_t ids[threads];
    ThreadData thread_data[threads];
    int rows_per_thread = N / threads;
    int extra = N % threads;
    int current = 0;

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < threads; i++) {
        int rows = rows_per_thread + (i < extra ? 1 : 0);
        thread_data[i].start_row = current;
        thread_data[i].end_row = current + rows;
        current += rows;
        pthread_create(&ids[i], NULL, multiply, &thread_data[i]);
    }

    for (int i = 0; i < threads; i++)
        pthread_join(ids[i], NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double ms = (end.tv_sec - start.tv_sec) * 1000.0 +
                (end.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("Время выполнения: %.3f мс\n", ms);

    //выводятся только матрицы меньше 5
    if (N <= 5) {
        print_matrix(A, "A");
        print_matrix(B, "B");
        print_matrix(C, "C");
    }

    free_matrices();
}

// ==== ЗАДАНИЯ 1–6 оставлены без изменений ====

void* thread_func1(void* arg) {
    for (int i = 1; i <= 5; i++)
        printf("Дочерний поток: строка %d\n", i);
    return NULL;
}
void task1() {
    printf("\n=== Задание 1 ===\n");
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func1, NULL);
    for (int i = 1; i <= 5; i++)
        printf("Родительский поток: строка %d\n", i);
    pthread_join(thread, NULL);
}

void* thread_func2(void* arg) {
    for (int i = 1; i <= 5; i++)
        printf("Дочерний поток: строка %d\n", i);
    return NULL;
}
void task2() {
    printf("\n=== Задание 2 ===\n");
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func2, NULL);
    pthread_join(thread, NULL);
    for (int i = 1; i <= 5; i++)
        printf("Родительский поток: строка %d\n", i);
}

void* thread_func3(void* arg) {
    char** messages = (char**)arg;
    for (int i = 0; messages[i] != NULL; i++)
        printf("%s\n", messages[i]);
    return NULL;
}
void task3() {
    printf("\n=== Задание 3 ===\n");
    pthread_t threads[4];
    char* m1[] = {"Поток 1: строка 1", "Поток 1: строка 2", NULL};
    char* m2[] = {"Поток 2: строка 1", NULL};
    char* m3[] = {"Поток 3: строка 1", "Поток 3: строка 2", "Поток 3: строка 3", NULL};
    char* m4[] = {"Поток 4: строка 1", "Поток 4: строка 2", NULL};
    pthread_create(&threads[0], NULL, thread_func3, m1);
    pthread_create(&threads[1], NULL, thread_func3, m2);
    pthread_create(&threads[2], NULL, thread_func3, m3);
    pthread_create(&threads[3], NULL, thread_func3, m4);
    for (int i = 0; i < 4; i++) pthread_join(threads[i], NULL);
}

void* thread_func4(void* arg) {
    int id = *(int*)arg;
    for (int i = 1; i <= 5; i++) {
        printf("Поток %d: строка %d\n", id, i);
        sleep(1);
    }
    return NULL;
}
void task4() {
    printf("\n=== Задание 4 ===\n");
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
        pthread_create(&threads[i], NULL, thread_func4, &ids[i]);
    sleep(2);
    for (int i = 0; i < 3; i++) {
        pthread_cancel(threads[i]);
        printf("Поток %d прерван\n", i + 1);
    }
}

void cleanup(void* arg) {
    printf("Очистка: поток завершен\n");
}
void* thread_func5(void* arg) {
    pthread_cleanup_push(cleanup, NULL);
    int id = *(int*)arg;
    for (int i = 1; i <= 5; i++) {
        printf("Поток %d: строка %d\n", id, i);
        sleep(1);
    }
    pthread_cleanup_pop(0);
    return NULL;
}
void task5() {
    printf("\n=== Задание 5 ===\n");
    pthread_t thread;
    int id = 1;
    pthread_create(&thread, NULL, thread_func5, &id);
    sleep(2);
    pthread_cancel(thread);
    pthread_join(thread, NULL);
}

void* sleep_sort(void* arg) {
    int num = *(int*)arg;
    usleep(num * 1000);
    printf("%d ", num);
    return NULL;
}
void task6() {
    printf("\n=== Задание 6 ===\n");
    int arr[] = {3, 1, 4, 2, 5, 9, 14, 44, 66, 8, 67, 32, 545, 99, 0, 12, 55};
    int n = sizeof(arr) / sizeof(arr[0]);
    pthread_t threads[n];
    printf("До сортировки: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\nПосле сортировки: ");
    for (int i = 0; i < n; i++)
        pthread_create(&threads[i], NULL, sleep_sort, &arr[i]);
    for (int i = 0; i < n; i++)
        pthread_join(threads[i], NULL);
    printf("\n");
}



int main(int argc, char* argv[]) {
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();

    if (argc == 3) {
        int size = atoi(argv[1]);
        int threads = atoi(argv[2]);
        if (size > 0 && size <= MAX && threads > 0 && threads <= size)
            task8(size, threads);
        else
            printf("Некорректный ввод. Размер <= %d, потоки <= %d\n", MAX, size);
    } else {
        printf("\n<размер> <потоки>\n");
    }

    return 0;
}
