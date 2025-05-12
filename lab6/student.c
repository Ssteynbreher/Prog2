#include "student.h"

// Реализация функции addStudent
struct Student addStudent(char name[], int math, int phy, int inf) {
    struct Student newStudent;
    strncpy(newStudent.name, name, MAX_NAME_LENGTH - 1);
    newStudent.name[MAX_NAME_LENGTH - 1] = '\0'; // Гарантия завершения строки
    newStudent.math = math;
    newStudent.phy = phy;
    newStudent.inf = inf;
    newStudent.total = math + phy + inf;
    return newStudent;
}

// Реализация функции printStudentInfo
void printStudentInfo(struct Student student) {
    printf("Имя студента: %s\n", student.name);
    printf("Балл по математике: %d, Балл по физике: %d, Балл по информатике: %d, Общий балл: %d\n", student.math, student.phy, student.inf, student.total);
}
