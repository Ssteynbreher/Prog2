#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define MAX_NAME_LENGTH 64

// Определение структуры Student
struct Student {
    char name[MAX_NAME_LENGTH];
    int math;
    int phy;
    int inf;
    int total;
};

// Прототипы функций, связанных со студентами
struct Student addStudent(char name[], int math, int phy, int inf);
void printStudentInfo(struct Student student);

#endif
