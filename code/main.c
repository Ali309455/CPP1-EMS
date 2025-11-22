#include <stdio.h>
#include <stdlib.h>
#include "../header files/studentmanagement.h"
#include "../header files/Portal.h"
#include "../header files/resultprocessing.h"
#include "../header files/sittingarrangement.h"
#include "../header files/attendancemanagement.h"
int count;
struct Student *s = NULL;
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
            free(s);
            return;

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}

void admin_dashboard(struct Student *std, int cnt, struct portal_info *cred)
{
    int choice;
    while (1)
    {
        clearScreen();
        printf("---------------------> Admin Interface <--------------------\n");
        printf("1. Security \n");
        printf("2. Student Prior Information Dashboard\n");
        printf("3. Student Result Processing\n");
        printf("4. Attendance Management\n");
        printf("5. Sitting Arrangement\n");
        printf("6. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            clearScreen();
            Admin_interface(cred);
            break;
        case 2:
        {
            clearScreen();
            menu(s, cnt);
            break;
        }
        case 3:
            cnt = loadData(&s);
            if (cnt == 0)
            {
                printf("No prior data stored. First add Prior Data using Option 2 then add students (option 1) \n");
                return;
            }
            else
            {
                clearScreen();
                tabulation(s, cnt);
                break;
            }
        case 4:
            cnt = loadData(&s);
            if (cnt == 0)
            {
                printf("No prior data stored. First add Prior Data using Option 2 then add students (option 1) \n");
                return;
            }
            else
            {
                clearScreen();
                attendance_management(s, cnt);
                break;
            }
        case 5:
            cnt = loadData(&s);
            if (cnt == 0)
            {
                printf("No prior data stored. First add Prior Data using Option 2 then add students (option 1) \n");
                return;
            }
            else
            {
                clearScreen();
                sittingArrangement(cnt, s);
                return;
            }
        case 6:
            printf("Exiting from Dashboard....\n");
            free(s);
            return;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}
void main(void)
{
    s = calloc(2, sizeof(struct Student));
    count = loadData(&s);
    memset(&credentials, 0, sizeof(credentials));
    load_credentials(&credentials, 1);
    int status = portal();
    if (status == 1)
    {
        if (count == 0)
        {
            printf("No prior data stored by Admin. First ask them to input Prior Data \n");
            return;
        }
        else
        {
            tabulation(s, count);
            free(s);
            
        }
    }
    else if (status == 2)
    {
        admin_dashboard(s, count, &credentials);
    }
    else
    {
        student_interface(s, count);
    }
}