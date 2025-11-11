#include "../header files/studentmanagement.h"

// void ems_init(void) {
//     printf("EMS initialized.\n");
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    char roll_no[10];
    char name[50];
    char semester[20];
    float cgpa;
};

struct Student *students = NULL;
int count = 0;

void addStudent()
{
    int n;
    printf("\nHow many students do you want to add? ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++)
    {
        students = realloc(students, (count + 1) * sizeof(struct Student));
        if (students == NULL)
        {
            printf("Memory allocation failed!\n");
            exit(1);
        }

        struct Student *s = students + count;

        printf("\n--- Adding Student %d ---\n", i + 1);

        printf("Enter Roll Number: ");
        scanf("%s", (*s).roll_no);
        getchar();

        printf("Enter Name: ");
        fgets((*s).name, sizeof((*s).name), stdin);
        (*s).name[strcspn((*s).name, "\n")] = 0;

        printf("Enter First Year's Semester: ");
        fgets((*s).semester, sizeof((*s).semester), stdin);
        (*s).semester[strcspn((*s).semester, "\n")] = 0;

        printf("Enter CGPA: ");
        scanf("%f", &(*s).cgpa);
        getchar();

        count++;
        printf("Student added successfully!\n");
    }
}

void displayStudents()
{
    if (count == 0)
    {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n%-10s %-20s %-15s %-5s\n", "Roll No", "Name", "Semester", "CGPA");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        struct Student *s = students + i;
        printf("%-10s %-20s %-15s %.2f\n",
               (*s).roll_no, (*s).name, (*s).semester, (*s).cgpa);
    }
}

void searchStudent()
{
    char roll[10];
    printf("\nEnter Roll Number to search: ");
    scanf("%s", roll);

    for (int i = 0; i < count; i++)
    {
        struct Student *s = students + i;
        if (strcmp((*s).roll_no, roll) == 0)
        {
            printf("\nStudent Found:\n");
            printf("Roll No: %s\nName: %s\nSemester: %s\nCGPA: %.2f\n",
                   (*s).roll_no, (*s).name, (*s).semester, (*s).cgpa);
            return;
        }
    }
    printf("Student not found!\n");
}

void editStudent()
{
    char roll[10];
    printf("\nEnter Roll Number to edit: ");
    scanf("%s", roll);
    getchar();

    for (int i = 0; i < count; i++)
    {
        struct Student *s = students + i;
        if (strcmp((*s).roll_no, roll) == 0)
        {
            printf("\nEditing record for %s\n", (*s).name);

            printf("Enter updated Name: ");
            fgets((*s).name, sizeof((*s).name), stdin);
            (*s).name[strcspn((*s).name, "\n")] = 0;

            printf("Enter updated Semester: ");
            fgets((*s).semester, sizeof((*s).semester), stdin);
            (*s).semester[strcspn((*s).semester, "\n")] = 0;

            printf("Enter updated CGPA: ");
            scanf("%f", &(*s).cgpa);
            getchar();

            printf("Record updated successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void deleteStudent()
{
    char roll[10];
    int found = 0;
    printf("\nEnter Roll Number to delete: ");
    scanf("%s", roll);

    for (int i = 0; i < count; i++)
    {
        struct Student *s = students + i;
        if (strcmp((*s).roll_no, roll) == 0)
        {
            found = 1;
            for (int j = i; j < count - 1; j++)
            {
                *(students + j) = *(students + j + 1);
            }
            count--;
            students = realloc(students, count * sizeof(struct Student));
            printf("Record deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");
}

void saveToFile()
{
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL)
    {
        printf("Error saving data!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        struct Student *s = students + i;
        fprintf(fp, "%s,%s,%s,%.2f\n",
                (*s).roll_no, (*s).name, (*s).semester, (*s).cgpa);
    }

    fclose(fp);
}

void loadFromFile()
{
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL)
        return;

    struct Student temp;
    while (fscanf(fp, "%9[^,],%49[^,],%19[^,],%f\n",
                  temp.roll_no, temp.name, temp.semester, &temp.cgpa) == 4)
    {
        students = realloc(students, (count + 1) * sizeof(struct Student));
        if (students == NULL)
        {
            printf("Memory allocation failed while loading file!\n");
            exit(1);
        }
        *(students + count) = temp;
        count++;
    }

    fclose(fp);
}

void sittingArrangement()
{
    int rooms, capacity;
    printf("Enter number of rooms: ");
    scanf("%d", &rooms);
    printf("Enter capacity of each room: ");
    scanf("%d", &capacity);

    int totalSeats = rooms * capacity;

    if (count > totalSeats)
    {
        printf("Not enough seats for all students! Total seats: %d, Students: %d\n",
               totalSeats, count);
        return;
    }

    printf("\n===== Sitting Arrangement =====\n");

    int studentIndex = 0;

    for (int r = 1; r <= rooms; r++)
    {
        printf("\nRoom %d:\n", r);
        for (int s = 1; s <= capacity; s++)
        {
            if (studentIndex < count)
            {
                struct Student *st = students + studentIndex;
                printf("%s(%s)\t", (*st).name, (*st).roll_no);
                studentIndex++;
            }
            else
            {
                printf("Empty\t");
            }
        }
        printf("\n");
    }
}

void menu()
{
    int choice;
    loadFromFile();

    do
    {
        printf("\n===== Student Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Edit Student\n");
        printf("5. Delete Student\n");
        printf("6. Sitting Arrangement\n");
        printf("7. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            editStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            sittingArrangement();
            break;
        case 7:
            saveToFile();
            printf("Data saved. Exiting...\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 7);

    free(students);
}
