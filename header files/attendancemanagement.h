#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <stdio.h>
#include <string.h>
#include "../header files/studentmanagement.h"

#define SUBJECTS 6

// Subjects ke naam
extern char subjects[SUBJECTS][20];

// Structure for each student

// Function prototypes
void takeAttendance(struct Student *students, int totalStudents);
void displayAttendance(struct Student *students, int totalStudents);
void checkTotalAttendance(struct Student *students, int totalStudents);

#endif
