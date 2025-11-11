#include <stdio.h>
#include <string.h>
#include "../header files/attendancemanagement.h"


// Subjects ke naam
char subjects[SUBJECTS][20] = {"ITFA", "CP", "PST", "English", "AP", "CAG"};


// Function 1: Attendance lena
void takeAttendance(struct Student *students, int totalStudents)
{
    for (int i = 0; i < SUBJECTS; i++)
    {
        printf("\n----> Taking Attendance for Subject: %s\n", subjects[i]);
        for (int j = 0; j < totalStudents; j++)
        {
            int status;
            printf("Roll No: %s | Name: %s\n", (students + j)->rollNumber, (students + j)->name);
            printf("Enter attendance (1 = Present, 0 = Absent): ");
            scanf("%d", &status);

            // Validate input
            if (status != 0 && status != 1)
            {
                printf("Invalid input! Defaulting to 0 (Absent)\n");
                status = 0;
            }

            (students + j)->attendance[i] = status;
        }
    }
}

// Function 2: Attendance show karna
void displayAttendance(struct Student *students, int totalStudents)
{
    if (totalStudents == 0)
    {
        printf("\nNo attendance record found! Please take attendance first.\n");
        return;
    }

    printf("\n================= Attendance Record =================\n");
    printf("Roll No\t\tName\t\tITFA\tCP\tPST\tEnglish\tAP\tCAG\n");
    printf("------------------------------------------------------\n");

    for (int i = 0; i < totalStudents; i++)
    {
        printf("%-10s\t%-15s", (students + i)->rollNumber, (students + i)->name);
        for (int j = 0; j < SUBJECTS; j++)
        {
            printf("%c\t", ((students + i)->attendance[j] == 1) ? 'P' : 'A');
        }
        printf("\n");
    }

    printf("------------------------------------------------------\n");
}

// Function 3: Kisi ek subject ki total attendance check karna
void checkTotalAttendance(struct Student *students, int totalStudents)
{
    if (totalStudents == 0)
    {
        printf("\n⚠️ Pehle attendance lo!\n");
        return;
    }

    char subName[50];
    printf("\nEnter subject name to check total attendance: ");
    scanf(" %[^\n]s", subName); // read full line including spaces

    int subjectIndex = -1;
    for (int i = 0; i < SUBJECTS; i++)
    {
        if (strcmp(subName, subjects[i]) == 0)
        {
            subjectIndex = i;
            break;
        }
    }

    if (subjectIndex == -1)
    {
        printf(" Galat subject name hai!\n");
        return;
    }

    int presentCount = 0;
    for (int i = 0; i < totalStudents; i++)
    {
        if ((students + i)->attendance[subjectIndex] == 1)
            presentCount++;
    }

    printf("\nSubject: %s\n", subjects[subjectIndex]);
    printf("Total Students: %d\n", totalStudents);
    printf("Present Students: %d\n", presentCount);
    printf("Absent Students: %d\n", totalStudents - presentCount);
    printf("Attendance Percentage: %.2f%%\n", (presentCount * 100.0) / totalStudents);
}

int attendance_management()
{
    struct Student students[MAX_STUDENTS] = {
        {"Ali Khan", "BSCS001"},
        {"Sara Ahmed", "BSCS002"},
        {"Hassan Raza", "BSCS003"},
        {"Fatima Noor", "BSCS004"},
        {"Ayesha Malik", "BSCS005"}
    };

    int totalStudents = 5;
    int choice;

    while (1)
    {
        printf("\n===== Attendance Management System (Pointer Version) =====\n");
        printf("1. Take Attendance\n");
        printf("2. Display Attendance Table\n");
        printf("3. Check Total Attendance (Subject Wise)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                takeAttendance(students, totalStudents);
                break;
            case 2:
                displayAttendance(students, totalStudents);
                break;
            case 3:
                checkTotalAttendance(students, totalStudents);
                break;
            case 4:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}