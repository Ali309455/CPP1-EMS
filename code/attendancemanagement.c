#include <stdio.h>
#include <string.h>
#include "../header files/attendancemanagement.h"
#include "../header files/studentmanagement.h"


// Name of Subjects
char subjects[SUBJECTS][20] = {"ITFA", "CP", "PST", "FE", "AP", "CAG"};

// Take Attendance 
void takeAttendance(struct Student *students, int totalStudents)
{
    for (int i = 0; i < SUBJECTS; i++)
    {
        printf("\n----> Taking Attendance for Subject: %s\n", subjects[i]);
        for (int j = 0; j < totalStudents; j++)
        {
            int status;
            printf("Roll No: %s | Name: %s\n", (students + j)->roll_no, (students + j)->name);
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
    return ;
}

// Display Attendance
void displayAttendance(struct Student *students, int totalStudents)
{
    if (totalStudents == 0)
    {
        printf("\nNo attendance record found! Please take attendance first.\n");
        return;
    }
    clearScreen();
    printf("\n============================================ Attendance Record ================================================\n");
printf("| %-10s | %-20s | %-7s | %-7s | %-7s | %-7s | %-7s | %-7s | %-7s |\n",
       "Roll No", "Name", "ITFA", "CP", "PST", "English", "AP", "CAG", "Total");
printf("============================================================================================================\n");

for (int i = 0; i < totalStudents; i++)
{
    int totalPresent = 0;
    printf("| %-10s | %-20s |", students[i].roll_no, students[i].name);

    for (int j = 0; j < SUBJECTS; j++)
    {
        char status = (students[i].attendance[j] == 1) ? 'P' : 'A';
        if (status == 'P') totalPresent++;
        printf(" %-7c |", status);
    }

    printf(" %-7d |\n", totalPresent); // Optional: show total present days
}

printf("============================================================================================================\n");

}

// Display Attendance of Specific Subject
void checkTotalAttendance(struct Student *students, int totalStudents)
{
    if (totalStudents == 0)
    {
        printf("\nTake attendance first!!\n");
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
        printf(" Invalid Subject:)\n");
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

// Print Menu
void attendance_management(struct Student *students, int totalStdnts)
{

    int totalStudents = totalStdnts;
    int choice;

    while (1)
    {
        printf("\n===== Attendance Management System =====\n");
        printf("1. Take Attendance\n");
        printf("2. Display Attendance Table\n");
        printf("3. Check Total Attendance (Subject Wise)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                clearScreen();
                takeAttendance(students, totalStudents);
                saveDataArray(students, totalStdnts, 1,1);
                break;
            case 2:
                displayAttendance(students, totalStudents);
                break;
            case 3:
                clearScreen();
                checkTotalAttendance(students, totalStudents);
                break;
            case 4:
                printf("Exiting Attendance Management system...\n");
                return ;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return ;
}