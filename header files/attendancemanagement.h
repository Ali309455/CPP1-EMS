#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <stdio.h>
#include <string.h>

#define SUBJECTS 6
#define MAX_STUDENTS 100

// Subjects ke naam
extern char subjects[SUBJECTS][20];

// Structure for each student
struct Student
{
    char name[50];
    char rollNumber[10];
    int attendance[SUBJECTS]; // 1 = Present, 0 = Absent
};

// Function prototypes
void takeAttendance(struct Student *students, int totalStudents);
void displayAttendance(struct Student *students, int totalStudents);
void checkTotalAttendance(struct Student *students, int totalStudents);

#endif
