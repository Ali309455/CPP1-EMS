#include "../header files/studentmanagement.h"

// void ems_init(void) {
//     printf("EMS initialized.\n");
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Student {
    int roll_no;
    char name[50];
    char year_sem[20];
    float cgpa;
};

struct Student students[MAX];
int count = 0;

void addStudent(struct Student *ptr) {
    int n;
    printf("\nHow many students do you want to add? ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        struct Student *s = ptr + count; 

        printf("\n--- Adding Student %d ---\n", i + 1);

        printf("Enter Roll Number: ");
        scanf("%d", &s->roll_no);
        getchar();

        printf("Enter Name: ");
        fgets(s->name, sizeof(s->name), stdin);
        s->name[strcspn(s->name, "\n")] = 0;

        printf("Enter Year and Semester: ");
        fgets(s->year_sem, sizeof(s->year_sem), stdin);
        s->year_sem[strcspn(s->year_sem, "\n")] = 0;

        printf("Enter CGPA: ");
        scanf("%f", &s->cgpa);
        getchar();

        count++;
        printf("Student added successfully!\n");
    }
}

void displayStudents(struct Student *ptr) {
    if (count == 0) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n%-10s %-20s %-15s %-5s\n", "Roll No", "Name", "Year and Semester", "CGPA");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        struct Student *s = ptr + i;
        printf("%-10d %-20s %-15s %-.2f\n",
               s->roll_no, s->name, s->year_sem, s->cgpa);
    }
}

void searchStudent(struct Student *ptr) {
    int roll;
    printf("\nEnter Roll Number to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        struct Student *s = ptr + i;
        if (s->roll_no == roll) {
            printf("\nStudent Found:\n");
            printf("Name: %s\nClass: %s\nCGPA: %.2f\n",
                   s->name, s->year_sem, s->cgpa);
            return;
        }
    }
    printf("Student not found!\n");
}

void editStudent(struct Student *ptr) {
    int roll;
    printf("\nEnter Roll Number to edit: ");
    scanf("%d", &roll);
    getchar();

    for (int i = 0; i < count; i++) {
        struct Student *s = ptr + i;
        if (s->roll_no == roll) {
            printf("Editing record for %s\n", s->name);

            printf("Enter updated Name: ");
            fgets(s->name, sizeof(s->name), stdin);
            s->name[strcspn(s->name, "\n")] = 0;

            printf("Enter updated Year & Semester: ");
            fgets(s->year_sem, sizeof(s->year_sem), stdin);
            s->year_sem[strcspn(s->year_sem, "\n")] = 0;

            printf("Enter updated CGPA: ");
            scanf("%f", &s->cgpa);
            getchar();

            printf("Record updated successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void deleteStudent(struct Student *ptr) {
    int roll, found = 0;
    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        struct Student *s = ptr + i;
        if (s->roll_no == roll) {
            found = 1;
            for (int j = i; j < count - 1; j++) {
                *(ptr + j) = *(ptr + j + 1); 
            }
            count--;
            printf("Record deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Student not found!\n");
}

void saveToFile(struct Student *ptr) {
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL) {
        printf("Error saving data!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        struct Student *s = ptr + i;
        fprintf(fp, "%d,%s,%s,%.2f\n",
                s->roll_no, s->name, s->year_sem, s->cgpa);
    }

    fclose(fp);
}

void loadFromFile(struct Student *ptr) {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL)
        return;

    while (count < MAX &&
           fscanf(fp, "%d,%49[^,],%19[^,],%f\n",
                  &(ptr + count)->roll_no,
                  (ptr + count)->name,
                  (ptr + count)->year_sem,
                  &(ptr + count)->cgpa) == 4) {
        count++;
    }

    fclose(fp);
}

void duplicate(struct Student *ptr) {
    int choice;
    loadFromFile(ptr);

    do {
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

        switch (choice) {
        case 1:
            addStudent(ptr);
            break;
        case 2:
            displayStudents(ptr);
            break;
        case 3:
            searchStudent(ptr);
            break;
        case 4:
            editStudent(ptr);
            break;
        case 5:
            deleteStudent(ptr);
            break;
        case 6:
            saveToFile(ptr);
            printf("Data saved. Exiting...\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);
}

