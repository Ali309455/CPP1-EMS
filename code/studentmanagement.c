#include "../header files/studentmanagement.h"

<<<<<<< Updated upstream
void ems_init(void) {
    printf("EMS initialized.\n");
=======
// void ems_init(void) {
//     printf("EMS initialized.\n");
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char roll_no[10];
    char name[50];
    char year_sem[20];
    float cgpa;
};

struct Student *students = NULL;
int count = 0;

void addStudent() {
    int n;
    printf("\nHow many students do you want to add? ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        
        students = realloc(students, (count + 1) * sizeof(struct Student));
        if (students == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }

        struct Student *s = students + count;  

        printf("\n--- Adding Student %d ---\n", i + 1);

        printf("Enter Roll Number: ");
        scanf("%s", &(*s).roll_no);
        getchar();

        printf("Enter Name: ");
        fgets((*s).name, sizeof((*s).name), stdin);
        (*s).name[strcspn((*s).name, "\n")] = 0;

        printf("Enter Year and Semester: ");
        fgets((*s).year_sem, sizeof((*s).year_sem), stdin);
        (*s).year_sem[strcspn((*s).year_sem, "\n")] = 0;

        printf("Enter CGPA: ");
        scanf("%f", &(*s).cgpa);
        getchar();

        count++;
        printf("Student added successfully!\n");
    }
>>>>>>> Stashed changes
}
