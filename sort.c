#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 10

struct Student {
    char name[64];  
    int math;
    int phy;
    int inf;
    int total;
};

struct Student addStudent(char *name, int math, int phy, int inf) {
    struct Student newStudent;
    strncpy(newStudent.name, name, 63);
    newStudent.math = math;
    newStudent.phy = phy;
    newStudent.inf = inf;
    newStudent.total = math + phy + inf;
    return newStudent;
}

void printStudentInfo(struct Student student) {
    printf("Имя: %s, Математика: %d, Физика: %d, Информатика: %d, Общий балл: %d\n",
           student.name, student.math, student.phy, student.inf, student.total);
}

void insertionSort(struct Student students[], int n) {
    for (int i = 1; i < n; i++) {
        struct Student key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].total < key.total) {
            students[j + 1] = students[j];
            j = j - 1;
        }
        students[j + 1] = key;
    }
}

void countingSort(struct Student students[], int n) {
    int maxTotal = 300;
    int count[maxTotal + 1];
    struct Student output[n];
    
    for (int i = 0; i <= maxTotal; i++) count[i] = 0;
    for (int i = 0; i < n; i++) count[students[i].total]++;
    for (int i = maxTotal - 1; i >= 0; i--) count[i] += count[i + 1];
    for (int i = 0; i < n; i++) {
        output[count[students[i].total] - 1] = students[i];
        count[students[i].total]--;
    }
    for (int i = 0; i < n; i++) students[i] = output[i];
}

void quickSort(struct Student students[], int low, int high) {
    if (low < high) {
        int pivot = students[high].total;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (students[j].total >= pivot) {
                i++;
                struct Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
        struct Student temp = students[i + 1];
        students[i + 1] = students[high];
        students[high] = temp;
        int pivotIndex = i + 1;
        quickSort(students, low, pivotIndex - 1);
        quickSort(students, pivotIndex + 1, high);
    }
}

void printProcessorInfo() {
    system("cat /proc/cpuinfo | grep 'model name' | head -n 1");
}

void measureSortTime(void (*sortFunction)(struct Student[], int), struct Student students[], int n) {
    clock_t start = clock();
    sortFunction(students, n);
    clock_t end = clock();
    printf("Время работы сортировки: %f секунд\n", ((double)(end - start)) / CLOCKS_PER_SEC);
}

void measureQuickSortTime(struct Student students[], int n) {
    clock_t start = clock();
    quickSort(students, 0, n - 1);
    clock_t end = clock();
    printf("Время работы QuickSort: %f секунд\n", ((double)(end - start)) / CLOCKS_PER_SEC);
}

int main() {
    struct Student students[N];

    for (int i = 0; i < N; i++) {
        char name[64];
        snprintf(name, sizeof(name), "Студент%d", i + 1);
        students[i] = addStudent(name, rand() % 101, rand() % 101, rand() % 101);
    }

    printf("Список студентов до сортировки:\n");
    for (int i = 0; i < N; i++) printStudentInfo(students[i]);
    
    printf("\nСортировка вставками:\n");
    measureSortTime(insertionSort, students, N);
    for (int i = 0; i < N; i++) printStudentInfo(students[i]);
    
    for (int i = 0; i < N; i++) {
        char name[64];
        snprintf(name, sizeof(name), "Студент%d", i + 1);
        students[i] = addStudent(name, rand() % 101, rand() % 101, rand() % 101);
    }

    printf("\nСортировка подсчётом:\n");
    measureSortTime(countingSort, students, N);
    for (int i = 0; i < N; i++) printStudentInfo(students[i]);
    
    for (int i = 0; i < N; i++) {
        char name[64];
        snprintf(name, sizeof(name), "Студент%d", i + 1);
        students[i] = addStudent(name, rand() % 101, rand() % 101, rand() % 101);
    }
    
    printf("\nСортировка QuickSort:\n");
    measureQuickSortTime(students, N);
    for (int i = 0; i < N; i++) printStudentInfo(students[i]);
    
    printf("\nИнформация о процессоре:\n");
    printProcessorInfo();
    
    return 0;
}