#ifndef STUDENTMANAGEMENT_H
#define STUDENTMANAGEMENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Student {
char roll_no[10];
char name[50];
char year_sem[20];
float cgpa;
};

extern struct Student *students;
extern int count;

void addStudent();
void displayStudents();
void searchStudent();
void editStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();
void menu();
#endif