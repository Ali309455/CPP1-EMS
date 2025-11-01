#include "../header files/studentmanagement.h"

// void ems_init(void) {
//     printf("EMS initialized.\n");
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Student
{
    int roll_no;
    char name[50];
    char year_sem[20];
    float cgpa;
};

struct Student students[MAX];
int count = 0;
void addStudent()
{
    int n;
    printf("\nHow many students do you want to add? ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++)
    {
        printf("\n--- Adding Student %d ---\n", i + 1);

        printf("Enter Roll Number: ");
        scanf("%d", &students[count].roll_no);
        getchar();

        printf("Enter Name: ");
        fgets(students[count].name, sizeof(students[count].name), stdin);
        students[count].name[strcspn(students[count].name, "\n")] = 0;

        printf("Enter Year and Semester: ");
        fgets(students[count].year_sem, sizeof(students[count].year_sem), stdin);
        students[count].year_sem[strcspn(students[count].year_sem, "\n")] = 0;

        printf("Enter CGPA: ");
        scanf("%f", &students[count].cgpa);
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

    printf("\n%-10s %-20s %-15s %-5s\n", "Roll No", "Name", "Year and Semester", "CGPA");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("%-10d %-20s %-15s %-.2f\n",
               students[i].roll_no, students[i].name,
               students[i].year_sem, students[i].cgpa);
    }
}

void searchStudent()
{
    int roll;
    printf("\nEnter Roll Number to search: ");
    scanf("%d", &roll);
    for (int i = 0; i < count; i++)
    {
        if (students[i].roll_no == roll)
        {
            printf("\nStudent Found:\n");
            printf("Name: %s\nClass: %s\nCGPA: %.2f\n",
                   students[i].name, students[i].year_sem, students[i].cgpa);
            return;
        }
    }
    printf("Student not found!\n");
}

void editStudent()
{

    int roll;
    printf("\nEnter Roll Number to edit: ");
    scanf("%d", &roll);
    getchar();

    for (int i = 0; i < count; i++)
    {
        if (students[i].roll_no == roll)
        {
            printf("Editing record for %s\n", students[i].name);

            printf("Enter updated Name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;

            printf("Enter updated Year & Semester: ");
            fgets(students[i].year_sem, sizeof(students[i].year_sem), stdin);
            students[i].year_sem[strcspn(students[i].year_sem, "\n")] = 0;

            printf("Enter updated CGPA: ");
            scanf("%f", &students[i].cgpa);
            while (getchar() != '\n')
                ;

            printf("Record updated successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void deleteStudent()
{
    int roll, found = 0;
    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++)
    {
        if (students[i].roll_no == roll)
        {
            found = 1;
            for (int j = i; j < count - 1; j++)
            {
                students[j] = students[j + 1];
            }
            count--;
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
        fprintf(fp, "%d,%s,%s,%.2f\n",
                students[i].roll_no,
                students[i].name,
                students[i].year_sem,
                students[i].cgpa);
    }
    fclose(fp);
}

void loadFromFile()
{
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL)
        return;

    while (count < MAX &&
           fscanf(fp, "%d,%49[^,],%19[^,],%f\n",
                  &students[count].roll_no,
                  students[count].name,
                  students[count].year_sem,
                  &students[count].cgpa) == 4)
    {
        count++;
    }

    fclose(fp);
}

void duplicate()
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
        printf("6. Save & Exit\n");
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
            saveToFile();
            printf("Data saved. Exiting...\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);
}

