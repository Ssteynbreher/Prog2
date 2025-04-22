#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//ЗАДАНИЕ 1
void* thread_func1(void* arg) {
    for (int i = 1; i <= 5; i++) {
        printf("Дочерний поток: строка %d\n", i);
    }
    return NULL;
}

void task1() {
    printf("\n=== Задание 1 ===\n");
    pthread_t thread; // Создаем переменную для хранения ID потока
    
    // Создаем поток (NULL - атрибуты по умолчанию)
    pthread_create(&thread, NULL, thread_func1, NULL);
    
    // Главный поток продолжает работать
    for (int i = 1; i <= 5; i++) {
        printf("Главный поток: строка %d\n", i);
    }
    
    // Ждем завершения дочернего потока
    pthread_join(thread, NULL);
}

//ЗАДАНИЕ 2
void* thread_func2(void* arg) {
    for (int i = 1; i <= 5; i++) {
        printf("Дочерний поток: строка %d\n", i);
    }
    return NULL;
}

void task2() {
    printf("\n=== Задание 2 ===\n");
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func2, NULL);
    
    // Ждем завершения дочернего потока ПЕРЕД выводом
    pthread_join(thread, NULL);
    
    for (int i = 1; i <= 5; i++) {
        printf("Главный поток: строка %d\n", i);
    }
}

//ЗАДАНИЕ 3
void* thread_func3(void* arg) {
    char** messages = (char**)arg; // Приводим аргумент к нужному типу
    for (int i = 0; messages[i] != NULL; i++) {
        printf("%s\n", messages[i]);
    }
    return NULL;
}

void task3() {
    printf("\n=== Задание 3 ===\n");
    pthread_t threads[4]; // Массив для 4 потоков
    
    // Массивы сообщений для каждого потока (последний элемент NULL)
    char* messages1[] = {"Поток 1: строка 1", "Поток 1: строка 2", NULL};
    char* messages2[] = {"Поток 2: строка 1", NULL};
    char* messages3[] = {"Поток 3: строка 1", "Поток 3: строка 2", "Поток 3: строка 3", NULL};
    char* messages4[] = {"Поток 4: строка 1", "Поток 4: строка 2", NULL};
    
    // Создаем 4 потока с разными параметрами
    pthread_create(&threads[0], NULL, thread_func3, messages1);
    pthread_create(&threads[1], NULL, thread_func3, messages2);
    pthread_create(&threads[2], NULL, thread_func3, messages3);
    pthread_create(&threads[3], NULL, thread_func3, messages4);
    
    // Ждем завершения всех потоков
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
}

//ЗАДАНИЕ 4
void* thread_func4(void* arg) {
    int id = *(int*)arg;
    for (int i = 1; i <= 5; i++) {
        printf("Поток %d: строка %d\n", id, i);
        sleep(1); // Задержка между выводами
    }
    return NULL;
}

void task4() {
    printf("\n=== Задание 4 ===\n");
    pthread_t threads[3];
    int ids[3] = {1, 2, 3}; // ID для потоков
    
    // Создаем 3 потока
    for (int i = 0; i < 3; i++) {
        pthread_create(&threads[i], NULL, thread_func4, &ids[i]);
    }
    
    sleep(2); // Ждем 2 секунды
    
    // Прерываем все потоки
    for (int i = 0; i < 3; i++) {
        pthread_cancel(threads[i]);
        printf("Поток %d прерван\n", i+1);
    }
}

//ЗАДАНИЕ 5
void cleanup(void* arg) {
    printf("Очистка: поток завершен\n");
}

void* thread_func5(void* arg) {
    pthread_cleanup_push(cleanup, NULL); // Регистрируем функцию очистки
    
    int id = *(int*)arg;
    for (int i = 1; i <= 5; i++) {
        printf("Поток %d: строка %d\n", id, i);
        sleep(1);
    }
    
    pthread_cleanup_pop(0); // 0 - не вызывать cleanup при нормальном завершении
    return NULL;
}

void task5() {
    printf("\n=== Задание 5 ===\n");
    pthread_t thread;
    int id = 1;
    
    pthread_create(&thread, NULL, thread_func5, &id);
    sleep(2);
    
    pthread_cancel(thread); // Прерываем поток
    pthread_join(thread, NULL); // Ждем завершения
}

//ЗАДАНИЕ 6
void* sleep_sort(void* arg) {
    int num = *(int*)arg;
    usleep(num * 1000); 
    printf("%d ", num);
    return NULL;
}

void task6() {
    printf("\n=== Задание 6 ===\n");
    int arr[] = {3, 1, 4, 2, 5}; 
    int n = sizeof(arr)/sizeof(arr[0]);
    pthread_t threads[n];
    
    printf("До сортировки: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    printf("После сортировки: ");
    for (int i = 0; i < n; i++) {
        pthread_create(&threads[i], NULL, sleep_sort, &arr[i]);
    }
    
    // Ждем завершения всех потоков
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("\n");
}

int main() {
    task1(); 
    task2(); 
    task3(); 
    task4(); 
    task5(); 
    task6(); 
    
    return 0;
}