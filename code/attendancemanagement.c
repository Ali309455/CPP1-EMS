#include <stdio.h>
#include <string.h>

#define SUBJECTS 6
#define MAX_STUDENTS 100

// Subjects ke naam
char subjects[SUBJECTS][20] = {"ITFA", "CP", "PST", "English", "AP", "CAG"};

// Structure for each student
struct Student
{
    char name[50];
    int rollNumber;
    int attendance[SUBJECTS]; // 1 = Present, 0 = Absent
};

// Function prototypes
void takeAttendance(struct Student students[], int *totalStudents);
void displayAttendance(struct Student students[], int totalStudents);
void checkTotalAttendance(struct Student students[], int totalStudents);

int main()
{
    struct Student students[MAX_STUDENTS];
    int totalStudents = 0;
    int choice;

    while (1)
    {
        printf("\n===== Attendance Management System (Structure Version) =====\n");
        printf("1. Take Attendance\n");
        printf("2. Display Attendance Table\n");
        printf("3. Check Total Attendance (Subject Wise)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            takeAttendance(students, &totalStudents);
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

// Function 1: Attendance lena
void takeAttendance(struct Student students[], int *totalStudents)
{
    printf("Enter total number of students: ");
    scanf("%d", totalStudents);

    for (int i = 0; i < *totalStudents; i++)
    {
        printf("\nEnter name of Student %d: ", i + 1);
        scanf(" %[^\n]s", students[i].name);
        printf("Enter roll number of Student %d: ", i + 1);
        scanf("%d", &students[i].rollNumber);

        printf("Taking attendance for %s:\n", students[i].name);
        for (int j = 0; j < SUBJECTS; j++)
        {
            int status;
            printf("Enter attendance for %s (1 = Present, 0 = Absent): ", subjects[j]);
            scanf("%d", &status);
            students[i].attendance[j] = status;
        }
    }
}

// Function 2: Attendance show karna
void displayAttendance(struct Student students[], int totalStudents)
{
    if (totalStudents == 0)
    {
        printf("\n⚠️ Pehle attendance lo!\n");
        return;
    }

    printf("\nAttendance Record:\n");
    printf("----------------------------------------------------------\n");
    printf("Roll\tName\t\tITFA\tCP\tPST\tEnglish\tAP\tCAG\n");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < totalStudents; i++)
    {
        printf("%d\t%s\t", students[i].rollNumber, students[i].name);
        for (int j = 0; j < SUBJECTS; j++)
        {
            printf("%c\t", students[i].attendance[j] == 1 ? 'P' : 'A');
        }
        printf("\n");
    }
    printf("----------------------------------------------------------\n");
}

// Function 3: Kisi ek subject ki total attendance check karna
void checkTotalAttendance(struct Student students[], int totalStudents)
{
    if (totalStudents == 0)
    {
        printf("\n⚠️ Pehle attendance lo!\n");
        return;
    }

    char subName[20];
    printf("\nEnter subject name to check total attendance: ");
    scanf("%s", subName);

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
        printf("❌ Galat subject name hai!\n");
        return;
    }

    int presentCount = 0;
    for (int i = 0; i < totalStudents; i++)
    {
        if (students[i].attendance[subjectIndex] == 1)
            presentCount++;
    }

    printf("\nSubject: %s\n", subjects[subjectIndex]);
    printf("Total Students: %d\n", totalStudents);
    printf("Present Students: %d\n", presentCount);
    printf("Absent Students: %d\n", totalStudents - presentCount);
    printf("Attendance Percentage: %.2f%%\n", (presentCount * 100.0) / totalStudents);
}