#include <stdio.h>
#include <stdlib.h>
#include "../header files/studentmanagement.h"
#include "../header files/Portal.h"
#include "../header files/resultprocessing.h"
#include "../header files/sittingarrangement.h"
#include "../header files/attendancemanagement.h"
int count;
struct Student *s;
struct portal_info credentials;

void student_interface(struct Student *std, int cnt)
{
    int choice;
    while (1)
    {
        printf("1. View Your Info\n");
        printf("2. View Your Marks\n");
        printf("3. View Your Attendance\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            searchStudent(std, cnt);
            break;
        case 2:
        {
            char roll_no[19];
            printf("Enter Roll Number: ");
            scanf("%s", roll_no);
            search_marks_data(std, roll_no, cnt);
            break;
        }
        case 3:
            displayAttendance(std, count);
            break;
        case 4:
            printf("Exiting from student Dashboard....\n");
            return;
        
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
    }
}

void admin_dashboard(struct Student *std, int cnt , struct portal_info *cred){
int choice;
    while (1)
    {
        printf("----------> Admin Interface <----------\n");
        printf("1. Security \n");
        printf("2. Student Prior Information Dashboard\n");
        printf("3. Student Result Processing\n");
        printf("4. Attendance Management\n");
        printf("5. Sitting Arrangement\n");
        printf("6. Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            Admin_interface(cred);
            break;
        case 2:
        {
            menu(s);
            break;
        }
        case 3:
            tabulation(s, count);
            break;
        case 4:
            attendance_management(s, count);
            break;
        case 5:
            sittingArrangement(count, s);
            return;
        case 6:
            printf("Exiting from Dashboard....\n");
            return;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
    }
}
void main(void)
{
    s = calloc(20, sizeof(struct Student));
    count = loadData(s, 20);
    memset(&credentials, 0, sizeof(credentials));
    load_credentials(&credentials, 1);
    int status = portal();
    if (status == 1)
    {
        tabulation(s,count);
    }
    else if (status == 2)
    {
        admin_dashboard(s,count, &credentials);
    }
    else
    {
        student_interface(s, count);
    }
}