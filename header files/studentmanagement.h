#ifndef STUDENTMANAGEMENT_H
#define STUDENTMANAGEMENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUBJECTS 6

struct marks
{
    int itfa;
    int cp;
    int ap;
    int pst;
    int cag;
    int fe;

    int itfa_credithours;
    int cp_credithours;
    int ap_credithours;
    int pst_credithours;
    int cag_credithours;
    int fe_credithours;

    float itfa_gradescore;
    float cp_gradescore;
    float ap_gradescore;
    float pst_gradescore;
    float cag_gradescore;
    float fe_gradescore;
};

struct Student
{
     char roll_no[10];
    char name[50];
    char semester[20];
    float cgpa;
    struct marks marks_info;
    int attendance[SUBJECTS];

};

extern struct Student *students;
extern int count;

void addStudent();
void displayStudents();
void searchStudent();
void editStudent();
void deleteStudent();
void saveDataArray(struct Student *s, int cnt);
int loadData(struct Student *students, int maxCount);
void menu(struct Student *s);
#endif
