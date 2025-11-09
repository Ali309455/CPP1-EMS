#include <stdio.h>
#include <string.h>

// Subject ke naam list
char subjects[6][20] = {"ITFA", "CP", "PST", "English", "AP", "CAG"};

// Function prototypes
void takeAttendance(int (*attendance)[100], int *totalStudents);
void displayAttendance(int (*attendance)[100], int totalStudents);
void checkTotalAttendance(int (*attendance)[100], int totalStudents);

int main()
{
    int attendance[6][100]; // Yeh main ke andar banayi gayi 2D array hai
    int totalStudents = 0;  // Yeh total students ka number rakhegi
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
            takeAttendance(attendance, &totalStudents);
            break;
        case 2:
            displayAttendance(attendance, totalStudents);
            break;
        case 3:
            checkTotalAttendance(attendance, totalStudents);
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

// Function 1: Attendance lena pointer ke zariye
void takeAttendance(int (*attendance)[100], int *totalStudents)
{
    printf("Enter total number of students: ");
    scanf("%d", totalStudents);

    for (int i = 0; i < *totalStudents; i++)
    {
        printf("\nTaking attendance for Student %d:\n", i + 1);
        for (int j = 0; j < 6; j++)
        {
            int status;
            printf("Enter attendance for %s (1 = Present, 0 = Absent): ", subjects[j]);
            scanf("%d", &status);

            *(*(attendance + j) + i) = status; // Pointer ke through value save ho rahi hai
        }
    }
}

// Function 2: Attendance show karna
void displayAttendance(int (*attendance)[100], int totalStudents)
{
    if (totalStudents == 0)
    {
        printf("\nTake attendance First\n");
        return;
    }

    printf("\nAttendance Record:\n");
    printf("-------------------------------------------\n");
    printf("Student\tITFA\tCP\tPST\tEnglish\tAP\tCAG\n");
    printf("-------------------------------------------\n");

    for (int i = 0; i < totalStudents; i++)
    {
        printf("S%d\t", i + 1);
        for (int j = 0; j < 6; j++)
        {
            int value = *(*(attendance + j) + i); // Pointer ke zariye value access
            printf("%c\t", value == 1 ? 'P' : 'A');
        }
        printf("\n");
    }
    printf("-------------------------------------------\n");
}

// Function 3: Kisi ek subject ki total attendance check karna
void checkTotalAttendance(int (*attendance)[100], int totalStudents)
{
    if (totalStudents == 0)
    {
        printf("\nTake attendance First!\n");
        return;
    }

    char subName[20];
    printf("\nEnter subject name to check total attendance: ");
    scanf("%s", subName);

    int subjectIndex = -1;
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(subName, subjects[i]) == 0)
        {
            subjectIndex = i;
            break;
        }
    }

    if (subjectIndex == -1)
    {
        printf("Subject Name is Wrong\n");
        return;
    }

    int presentCount = 0;
    for (int i = 0; i < totalStudents; i++)
    {
        int value = *(*(attendance + subjectIndex) + i);
        if (value == 1)
            presentCount++;
    }

    printf("\nSubject: %s\n", subjects[subjectIndex]);
    printf("Total Students: %d\n", totalStudents);
    printf("Present Students: %d\n", presentCount);
    printf("Absent Students: %d\n", totalStudents - presentCount);
    printf("Attendance Percentage: %.2f%%\n", (presentCount * 100.0) / totalStudents);
}