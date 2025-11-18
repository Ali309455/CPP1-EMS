#include "../header files/Portal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header files/cJSON.h"
#include "../header files/resultprocessing.h"
#include "../header files/studentmanagement.h"
#include "../header files/attendancemanagement.h"
#include "../header files/sittingarrangement.h"

// Attandance Management
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
    return;
}

// Function 2: Attendance show karna
void displayAttendance(struct Student *students, int totalStudents)
{
    if (totalStudents == 0)
    {
        printf("\nNo attendance record found! Please take attendance first.\n");
        return;
    }

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
            if (status == 'P')
                totalPresent++;
            printf(" %-7c |", status);
        }

        printf(" %-7d |\n", totalPresent); // Optional: show total present days
    }

    printf("============================================================================================================\n");
}

// Function 3: Kisi ek subject ki total attendance check karna
void checkTotalAttendance(struct Student *students, int totalStudents)
{
    if (totalStudents == 0)
    {
        printf("\n Pehle attendance lo!\n");
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

void attendance_management(struct Student *students, int totalStdnts)

{

    int totalStudents = totalStdnts;
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
            saveDataArray(students, totalStdnts, 1);
            break;
        case 2:
            displayAttendance(students, totalStudents);
            break;
        case 3:
            checkTotalAttendance(students, totalStudents);
            break;
        case 4:
            printf("Exiting Attendance Management system...\n");
            return;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }

    return;
}

// PORTAl
void load_credentials(struct portal_info *cred, int flag)
{
    // --- Validate input pointer ---
    if (cred == NULL)
    {
        printf("Error: NULL pointer passed to load_credentials.\n");
        return;
    }

    // --- Open file for reading ---
    FILE *file = fopen("D:\\code\\FE-CPP1-EMS\\Data\\credentials.json", "r");
    if (file == NULL)
    {
        perror("Error opening credentials file");
        return;
    }

    // --- Get file size ---
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    if (length <= 0)
    {
        printf("Error: credentials.json is empty or corrupted.\n");
        fclose(file);
        return;
    }
    fseek(file, 0, SEEK_SET);

    // --- Read entire file into buffer ---
    char *data = (char *)malloc(length + 1);
    if (data == NULL)
    {
        printf("Error: Memory allocation failed while reading credentials.\n");
        fclose(file);
        return;
    }

    size_t read_bytes = fread(data, 1, length, file);
    data[read_bytes] = '\0';
    fclose(file);

    // --- Parse JSON data ---
    cJSON *json = cJSON_Parse(data);
    free(data);

    if (json == NULL)
    {
        printf("Error: Failed to parse JSON from credentials.json\n");
        return;
    }

    // --- Extract teacher_password ---
    cJSON *teacher = cJSON_GetObjectItem(json, "teacher_password");
    if (teacher == NULL || !cJSON_IsString(teacher))
    {
        printf("Error: Missing or invalid 'teacher_password' in JSON.\n");
        cJSON_Delete(json);
        return;
    }

    // --- Extract admin_password ---
    cJSON *admin = cJSON_GetObjectItem(json, "admin_password");
    if (admin == NULL || !cJSON_IsString(admin))
    {
        printf("Error: Missing or invalid 'admin_password' in JSON.\n");
        cJSON_Delete(json);
        return;
    }

    // --- Copy data into structure safely ---
    strncpy(cred->teacher_password, teacher->valuestring, sizeof(cred->teacher_password) - 1);
    strncpy(cred->admin_password, admin->valuestring, sizeof(cred->admin_password) - 1);
    strncpy(cred->q1, cJSON_GetObjectItem(json, "q1")->valuestring, sizeof(cred->q1) - 1);
    strncpy(cred->q2, cJSON_GetObjectItem(json, "q2")->valuestring, sizeof(cred->q2) - 1);

    // Ensure null termination
    cred->teacher_password[sizeof(cred->teacher_password) - 1] = '\0';
    cred->admin_password[sizeof(cred->admin_password) - 1] = '\0';
    if (flag == 1)
        printf("Credentials loaded successfully.\n");

    // --- Clean up ---
    cJSON_Delete(json);
}

void save_password(struct portal_info cred)
{
    cJSON *json = cJSON_CreateObject();

    cJSON_AddStringToObject(json, "teacher_password", cred.teacher_password);
    cJSON_AddStringToObject(json, "admin_password", cred.admin_password);
    cJSON_AddStringToObject(json, "q1", cred.q1);
    cJSON_AddStringToObject(json, "q2", cred.q2);

    FILE *file = fopen("D:\\code\\FE-CPP1-EMS\\Data\\credentials.json", "w");
    if (file == NULL)
    {
        perror("Error opening credentials file");
        return;
    }

    char *json_string = cJSON_Print(json);
    if (json_string == NULL)
    {
        printf("Error: Failed to generate JSON string.\n");
        cJSON_Delete(json);
        fclose(file);
        return;
    }

    fputs(json_string, file);
    fclose(file);

    printf("Passweord saved successfully!\n");

    // Clean up
    free(json_string);
    cJSON_Delete(json);
}
void forget_password(struct portal_info cred)
{
    char ans1[25];
    char ans2[25];
    printf("n ----> You need to answer these 2 security Questions <----\n");
    printf("Q1: What is your favorite color?\n");
    scanf("%s", &ans1);
    printf("Q2: What is your favorite animal?\n");
    scanf("%s", &ans2);
    if (strcmp(ans1, cred.q1) == 0 && strcmp(ans2, cred.q2) == 0)
    {
        printf("Password: %s\n", cred.teacher_password);
    }
    else
    {
        printf("Wrong Answers\n");
    }
}

void change_password(int choice, struct portal_info *cred)
{
    char current_password[30];
    char new_password[30];
    switch (choice)
    {
    case 3:
        forget_password(*cred);
        break;
    case 1:
        printf("Enter Current Password: ");
        scanf("%s", &current_password);
        if (strcmp(cred->teacher_password, current_password) == 0)
        {
            printf("Enter New Password: ");
            scanf("%s", &new_password);
            strcpy(cred->teacher_password, new_password);
            save_password(*cred);
        }
        else
        {
            printf("Wrong Password\n");
        }
        break;
    case 2:
        printf("Enter Current Password: ");
        scanf("%s", &current_password);
        if (strcmp(cred->admin_password, current_password) == 0)
        {
            printf("Enter New Password: ");
            scanf("%s", &new_password);
            strcpy(cred->admin_password, new_password);
            save_password(*cred);
        }
        else
            printf("Wrong Password\n");
        break;

    default:
        printf("Invalid Choice");
        break;
    }
}
void Admin_interface(struct portal_info *cred)
{
    int admin_choice;
    printf("---------------------> Admin Interface <---------------------\n");
    printf("Enter 1 to change password of Teachers\n");
    printf("Enter 2 to change Password of Admin\n");
    printf("Enter 3 if you forget password\n ");
    scanf("%d", &admin_choice);
    change_password(admin_choice, cred);
}
void first_time_login(struct portal_info *cred)
{
    char password[30];
    printf("-----> YOUR USING THE SYSTEM FIRST TIME SET ADMIN AND TEACHER PASSWORDS <---------\n");

    printf("Enter Admin Password: ");
    scanf("%s", password);
    strncpy(cred->admin_password, password, sizeof(cred->admin_password) - 1);
    printf("Enter Teacher Password: ");
    scanf("%s", password);
    strncpy(cred->teacher_password, password, sizeof(cred->teacher_password) - 1);
    char ans1[25];
    char ans2[25];
    printf("\t ----> You need to answer these 2 security Questions <----\n");
    printf("Q1: What is your favorite color?\n");
    scanf("%s", &ans1);
    printf("Q2: What is your favorite animal?\n");
    scanf("%s", &ans2);
    strncpy(cred->q1, ans1, sizeof(cred->q1) - 1);
    strncpy(cred->q2, ans2, sizeof(cred->q2) - 1);
    save_password(*cred);
}
int login(struct portal_info cred)
{
    char password[30];
    int status_choice;
    printf("------------------------------------> WELCOME TO EXAMINATION MANAGEMENT SYSTEM <----------------------\n");
    printf("\n0-> Student \n1-> Teacher\n2-> Admin \n");
    printf("Enter your status: ");
    scanf("%d", &status_choice);
    if (status_choice == 1 || status_choice == 2)
    {
        printf("Enter password: ");
        scanf("%s", password);
        if (status_choice == 1 && strcmp(password, cred.teacher_password) == 0)
        {
            printf("Your Password is Correct!!\n ");
            return 1;
        }
        else if (status_choice == 2 && strcmp(password, cred.admin_password) == 0)
        {
            printf("Your Password is Correct!!\n ");
            return 2;
        }
        else
        {
            printf("Invalid password you can only access student interface\n");
        }
    }
    else
    {
        printf("----------> Student Interface <----------\n");
        return 0;
    }
}

int portal(void)
{
    struct portal_info credentials;
    memset(&credentials, 0, sizeof(credentials));
    load_credentials(&credentials, 0);
    if (strlen(credentials.admin_password) == 0)
        first_time_login(&credentials);
    int status = login(credentials);
    return status;
}

// RESULT PROCESSING
int CNT;
struct Student *students;

float grade_points(int marks)
{

    if (marks <= 100 && marks >= 85)
    {
        return 4.0;
    }
    else if (marks <= 84 && marks >= 80)
    {
        return 3.7;
    }
    else if (marks <= 79 && marks >= 75)
    {
        return 3.4;
    }
    else if (marks <= 74 && marks >= 70)
    {
        return 3.0;
    }
    else if (marks <= 69 && marks >= 67)
    {
        return 2.7;
    }
    else if (marks <= 66 && marks >= 64)
    {
        return 2.4;
    }
    else if (marks <= 63 && marks >= 60)
    {
        return 2.0;
    }
    else if (marks <= 59 && marks >= 57)
    {
        return 1.7;
    }
    else if (marks <= 56 && marks >= 54)
    {
        return 1.4;
    }
    else if (marks <= 53 && marks >= 50)
    {
        return 1.0;
    }
    else
    {
        return 0.0;
    }
}

void printdata(struct Student *pstr, int totalstdns)
{
    printf("=====================================================================================================\n");
    printf("| %-7s | %-20s | %-4s | %-4s | %-4s | %-4s | %-4s | %-4s | %-6s |\n",
           "Roll No", "Name", "ITFA", "CP", "AP", "PST", "CAG", "FE", "CGPA");
    printf("=====================================================================================================\n");

    for (int i = 0; i < totalstdns; i++)
    {
        struct marks m = pstr[i].marks_info;

        printf("| %-7s | %-20s | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | %-6.2f |\n",
               pstr[i].roll_no, pstr[i].name,
               m.itfa, m.cp, m.ap, m.pst, m.cag, m.fe,
               pstr[i].cgpa);
    }

    printf("=====================================================================================================\n");
}
void add_marks_data(struct Student *arr, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("Enter %s(%s)   marks in itfa: ", arr[i].roll_no, arr[i].name);
        scanf("%d", &arr[i].marks_info.itfa);
        printf("Enter %s(%s)  marks in cp: ", arr[i].roll_no, arr[i].name);
        scanf("%d", &arr[i].marks_info.cp);
        printf("Enter %s(%s)  marks in ap: ", arr[i].roll_no, arr[i].name);
        scanf("%d", &arr[i].marks_info.ap);
        printf("Enter %s(%s)  marks in pst: ", arr[i].roll_no, arr[i].name);
        scanf("%d", &arr[i].marks_info.pst);
        printf("Enter %s(%s)  marks in cag: ", arr[i].roll_no, arr[i].name);
        scanf("%d", &arr[i].marks_info.cag);
        printf("Enter %s(%s)  marks in fe: ", arr[i].roll_no, arr[i].name);
        scanf("%d", &arr[i].marks_info.fe);
        if (i == 0)
        {
            printf("-----> Same credit hours will be added for every Student <------\n");
            printf("Enter %s(%s)  itfa_credithours: ", arr[i].roll_no, arr[i].name);
            scanf("%d", &arr[i].marks_info.itfa_credithours);

            printf("Enter %s(%s)  cp_credithours: ", arr[i].roll_no, arr[i].name);
            scanf("%d", &arr[i].marks_info.cp_credithours);

            printf("Enter %s(%s)  ap_credithours: ", arr[i].roll_no, arr[i].name);
            scanf("%d", &arr[i].marks_info.ap_credithours);

            printf("Enter %s(%s)  pst_credithours: ", arr[i].roll_no, arr[i].name);
            scanf("%d", &arr[i].marks_info.pst_credithours);

            printf("Enter %s(%s)  cag_credithours: ", arr[i].roll_no, arr[i].name);
            scanf("%d", &arr[i].marks_info.cag_credithours);

            printf("Enter %s(%s)  fe_credithours: ", arr[i].roll_no, arr[i].name);
            scanf("%d", &arr[i].marks_info.fe_credithours);
        }
        else
        {
            arr[i].marks_info.itfa_credithours = arr[0].marks_info.itfa_credithours;
            arr[i].marks_info.cp_credithours = arr[0].marks_info.cp_credithours;
            arr[i].marks_info.ap_credithours = arr[0].marks_info.ap_credithours;
            arr[i].marks_info.pst_credithours = arr[0].marks_info.pst_credithours;
            arr[i].marks_info.cag_credithours = arr[0].marks_info.cag_credithours;
            arr[i].marks_info.fe_credithours = arr[0].marks_info.fe_credithours;
        }
        arr[i].marks_info.itfa_gradescore = grade_points(arr[i].marks_info.itfa);
        arr[i].marks_info.cp_gradescore = grade_points(arr[i].marks_info.cp);
        arr[i].marks_info.ap_gradescore = grade_points(arr[i].marks_info.ap);
        arr[i].marks_info.pst_gradescore = grade_points(arr[i].marks_info.pst);
        arr[i].marks_info.cag_gradescore = grade_points(arr[i].marks_info.cag);
        arr[i].marks_info.fe_gradescore = grade_points(arr[i].marks_info.fe);
    }
}

void printMenu()
{
    printf("\t -----------------> MARKS AND RESULT PROCESSIONG <-----------------\n");
    printf("\t1. Add marks data (NOTE: if u want to add all student's marks data one by one )\n");
    printf("\t2. Update marks data (NOTE: if u want to add 1 student's marks data OR update existing Student's marks data )\n");
    printf("\t3. Search marks data\n");
    printf("\t4. Calculate CGPA\n");
    printf("\t5. Print data\n");
    printf("\t6. Exit\n");
}
void calculate_cgpa(struct Student *pstr, int count)
{
    int index = 0;
    for (int i = 0; i < count; i++)
    {
        // if (strcasecmp(pstr[i].roll_no, roll_no) == 0)
        // {
        //     index = i;
        //     break;
        // }

        if (pstr[i].cgpa == 0.0)
        {
            pstr[i].cgpa = ((pstr[i].marks_info.itfa_gradescore * pstr[i].marks_info.itfa_credithours) +
                            (pstr[i].marks_info.cp_gradescore * pstr[i].marks_info.cp_credithours) +
                            (pstr[i].marks_info.ap_gradescore * pstr[i].marks_info.ap_credithours) +
                            (pstr[i].marks_info.pst_gradescore * pstr[i].marks_info.pst_credithours) +
                            (pstr[i].marks_info.cag_gradescore * pstr[i].marks_info.cag_credithours) +
                            (pstr[i].marks_info.fe_gradescore * pstr[i].marks_info.fe_credithours)) /
                           (pstr[i].marks_info.itfa_credithours + pstr[i].marks_info.cp_credithours + pstr[i].marks_info.ap_credithours + pstr[i].marks_info.pst_credithours + pstr[i].marks_info.cag_credithours + pstr[i].marks_info.fe_credithours);
        }
        else
        {
            float temp = ((pstr[i].marks_info.itfa_gradescore * pstr[i].marks_info.itfa_credithours) +
                          (pstr[i].marks_info.cp_gradescore * pstr[i].marks_info.cp_credithours) +
                          (pstr[i].marks_info.ap_gradescore * pstr[i].marks_info.ap_credithours) +
                          (pstr[i].marks_info.pst_gradescore * pstr[i].marks_info.pst_credithours) +
                          (pstr[i].marks_info.cag_gradescore * pstr[i].marks_info.cag_credithours) +
                          (pstr[i].marks_info.fe_gradescore * pstr[i].marks_info.fe_credithours)) /
                         (pstr[i].marks_info.itfa_credithours + pstr[i].marks_info.cp_credithours + pstr[i].marks_info.ap_credithours + pstr[i].marks_info.pst_credithours + pstr[i].marks_info.cag_credithours + pstr[i].marks_info.fe_credithours);
            pstr[i].cgpa = (pstr[i].cgpa + temp) / 2;
        }
    }
    printf("\t ------> Every students cgpa is calculated based on the data <--------\n");
    printdata(pstr, count);
}
void edit_marks_data(struct Student *pstr, char roll_no[19], int count)
{
    int index = -1;
    for (int i = 0; i < count; i++)
    {
        if (strcasecmp(pstr[i].roll_no, roll_no) == 0)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        printf(" %s previous marks in itfa are: %d, Enter marks in itfa: ", pstr[index].roll_no, pstr[index].marks_info.itfa);
        scanf("%d", &pstr[index].marks_info.itfa);
        printf(" %s previous marks in cp are: %d, Enter marks in cp: ", pstr[index].roll_no, pstr[index].marks_info.itfa);
        scanf("%d", &pstr[index].marks_info.cp);
        printf(" %s previous marks in AP are: %d, Enter marks in AP: ", pstr[index].roll_no, pstr[index].marks_info.itfa);
        scanf("%d", &pstr[index].marks_info.ap);
        printf(" %s previous marks in PST are: %d, Enter marks in PST: ", pstr[index].roll_no, pstr[index].marks_info.itfa);
        scanf("%d", &pstr[index].marks_info.pst);
        printf(" %s previous marks in CAG are: %d, Enter marks in CAG: ", pstr[index].roll_no, pstr[index].marks_info.itfa);
        scanf("%d", &pstr[index].marks_info.cag);
        printf(" %s previous marks in FE are: %d, Enter marks in FE: ", pstr[index].roll_no, pstr[index].marks_info.itfa);
        scanf("%d", &pstr[index].marks_info.fe);
        pstr[index].marks_info.itfa_credithours = pstr[0].marks_info.itfa_credithours;
        pstr[index].marks_info.cp_credithours = pstr[0].marks_info.cp_credithours;
        pstr[index].marks_info.ap_credithours = pstr[0].marks_info.ap_credithours;
        pstr[index].marks_info.pst_credithours = pstr[0].marks_info.pst_credithours;
        pstr[index].marks_info.cag_credithours = pstr[0].marks_info.cag_credithours;
        pstr[index].marks_info.fe_credithours = pstr[0].marks_info.fe_credithours;
        pstr[index].marks_info.itfa_gradescore = grade_points(pstr[index].marks_info.itfa);
        pstr[index].marks_info.cp_gradescore = grade_points(pstr[index].marks_info.cp);
        pstr[index].marks_info.ap_gradescore = grade_points(pstr[index].marks_info.ap);
        pstr[index].marks_info.pst_gradescore = grade_points(pstr[index].marks_info.pst);
        pstr[index].marks_info.cag_gradescore = grade_points(pstr[index].marks_info.cag);
        pstr[index].marks_info.fe_gradescore = grade_points(pstr[index].marks_info.fe);
        printf("\t ------> %S data Updated successfully <--------\n", roll_no);
    }
    else
        printf("\t ------> %S Not Found <--------\n", roll_no);
}
void search_marks_data(struct Student *pstr, char roll_no[19], int count)
{
    for (int i = 0; i < count; i++)
    {
        if (strcasecmp(pstr[i].roll_no, roll_no) == 0)
        {
            printf("=====================================================================================================\n");
            printf("| %-7s | %-15s | %-4s | %-4s | %-4s | %-4s | %-4s | %-4s | %-6s |\n",
                   "Roll No", "Name", "ITFA", "CP", "AP", "PST", "CAG", "FE", "CGPA");
            printf("=====================================================================================================\n");

            struct marks m = pstr[i].marks_info;

            printf("| %-7s | %-15s | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | %-6.2f |\n",
                   pstr[i].roll_no, pstr[i].name,
                   m.itfa, m.cp, m.ap, m.pst, m.cag, m.fe,
                   pstr[i].cgpa);

            printf("=====================================================================================================\n");
            return;
        }
    }
    printf("\t ------> %S Not Found <--------\n", roll_no);
}
void delete_marks_data(struct Student *pstr, char roll_no[19])
{
    for (int i = 0; i < CNT; i++)
    {
        if (strcasecmp(pstr[i].roll_no, roll_no) == 0)
        {
            for (int j = i; j < CNT; j++)
            {
                pstr[j] = pstr[j + 1];
            }
            CNT--;
        }
        else
        {
            printf("\t ------> %S Not Found <--------\n", roll_no);
            return;
        }
    }
    printf("\t ------> %S data deleted successfully <--------\n", roll_no);
}
void tabulation(struct Student *s, int totalstdnts)
{
    printf("%s", s[0].roll_no);
    int choice;
    printf("\t----------------------> THE DATA IS <----------------------------\n ");
    printdata(s, totalstdnts);
    while (1)
    {
        printMenu();
        printf("Enter Your Choice ( 1-5 ) : ");
        scanf("%d", &choice);
        char roll_no[19];
        if (choice >= 1 && choice <= 5)
        {
            switch (choice)
            {
            case 1:
                add_marks_data(s, totalstdnts);
                saveDataArray(s, totalstdnts, 1);
                printf("\t------------> Your marks data is saved successfully and the data is : \n");
                printdata(s, totalstdnts);
                break;
            case 2:
                if (totalstdnts == 0)
                {
                    printf("NO DATA STORED\n");
                    break;
                }
                printf("Enter Roll No: ");
                scanf("%s", roll_no);
                edit_marks_data(s, roll_no, totalstdnts);
                saveDataArray(s, totalstdnts, 1);
                break;
            case 3:
                if (totalstdnts == 0)
                {
                    printf("NO DATA STORED\n");
                    break;
                }
                printf("Enter Roll No: ");
                scanf("%s", roll_no);
                search_marks_data(s, roll_no, totalstdnts);
                break;
            case 4:
                if (totalstdnts == 0)
                {
                    printf("NO DATA STORED\n");
                    break;
                }
                calculate_cgpa(s, totalstdnts);
                break;
            case 5:
                if (totalstdnts == 0)
                {
                    printf("NO DATA STORED\n");
                    break;
                }
                printdata(s, totalstdnts);
                break;

            default:
                break;
            }
        }
        else
        {
            saveDataArray(s, totalstdnts, 1);
            return;
        }
    }
}

// STUDENT MANAGEMENT
int count = 0;

void saveDataArray(struct Student *s, int count, int flag_attendance)
{

    cJSON *jsonArray = cJSON_CreateArray();

    for (int i = 0; i < count; i++)
    {
        // Create JSON object for each student
        cJSON *studentObj = cJSON_CreateObject();
        cJSON_AddStringToObject(studentObj, "roll_no", s[i].roll_no);
        cJSON_AddStringToObject(studentObj, "name", s[i].name);
        cJSON_AddStringToObject(studentObj, "semester", s[i].semester);
        cJSON_AddNumberToObject(studentObj, "cgpa", s[i].cgpa);
        int attendanceArr[SUBJECTS];
        if (flag_attendance == 1)
        {
            for (int j = 0; j < SUBJECTS; j++)
            {
                attendanceArr[j] = s[i].attendance[j];
            }
        }
        else
        {
            for (int j = 0; j < SUBJECTS; j++)
                attendanceArr[j] = 0;
        }
        cJSON *attendanceArray = cJSON_CreateIntArray(attendanceArr, SUBJECTS);
        cJSON_AddItemToObject(studentObj, "attendance", attendanceArray);
        // Nested marks object
        cJSON *marksObj = cJSON_CreateObject();
        cJSON_AddNumberToObject(marksObj, "itfa", s[i].marks_info.itfa);
        cJSON_AddNumberToObject(marksObj, "cp", s[i].marks_info.cp);
        cJSON_AddNumberToObject(marksObj, "ap", s[i].marks_info.ap);
        cJSON_AddNumberToObject(marksObj, "pst", s[i].marks_info.pst);
        cJSON_AddNumberToObject(marksObj, "cag", s[i].marks_info.cag);
        cJSON_AddNumberToObject(marksObj, "fe", s[i].marks_info.fe);

        cJSON_AddNumberToObject(marksObj, "itfa_credithours", s[i].marks_info.itfa_credithours);
        cJSON_AddNumberToObject(marksObj, "cp_credithours", s[i].marks_info.cp_credithours);
        cJSON_AddNumberToObject(marksObj, "ap_credithours", s[i].marks_info.ap_credithours);
        cJSON_AddNumberToObject(marksObj, "pst_credithours", s[i].marks_info.pst_credithours);
        cJSON_AddNumberToObject(marksObj, "cag_credithours", s[i].marks_info.cag_credithours);
        cJSON_AddNumberToObject(marksObj, "fe_credithours", s[i].marks_info.fe_credithours);

        cJSON_AddNumberToObject(marksObj, "itfa_gradescore", s[i].marks_info.itfa_gradescore);
        cJSON_AddNumberToObject(marksObj, "cp_gradescore", s[i].marks_info.cp_gradescore);
        cJSON_AddNumberToObject(marksObj, "ap_gradescore", s[i].marks_info.ap_gradescore);
        cJSON_AddNumberToObject(marksObj, "pst_gradescore", s[i].marks_info.pst_gradescore);
        cJSON_AddNumberToObject(marksObj, "cag_gradescore", s[i].marks_info.cag_gradescore);
        cJSON_AddNumberToObject(marksObj, "fe_gradescore", s[i].marks_info.fe_gradescore);

        // Add marks object inside student object
        cJSON_AddItemToObject(studentObj, "marks_info", marksObj);

        // Add student object to array
        cJSON_AddItemToArray(jsonArray, studentObj);
    }

    //  Convert JSON array to string
    char *json_str = cJSON_Print(jsonArray);

    //  Write JSON to file
    FILE *fp = fopen("D:\\code\\FE-CPP1-EMS\\Data\\students.json", "w");
    if (fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        cJSON_Delete(jsonArray);
        free(json_str);
        return;
    }

    fputs(json_str, fp);
    fclose(fp);

    printf("JSON data saved successfully!\n");

    // Clean up
    free(json_str);
    cJSON_Delete(jsonArray);
}
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
        saveDataArray(students, count, 1);
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

void searchStudent(struct Student *students, int cnt)
{
    char roll[10];
    printf("\nEnter Roll Number to search: ");
    scanf("%s", roll);
    int flag = 1;
    for (int i = 0; i < count; i++)
    {
        struct Student *s = students + i;
        if (strcmp((*s).roll_no, roll) == 0)
        {
            flag = 0;
            printf("\nStudent Found:\n");
            printf("---------------------------------------------------------------------------------------------\n");
            printf("| %-10s | %-20s | %-10s | %-6s |\n",
                   "Roll No", "Name", "Semester", "CGPA");
            printf("---------------------------------------------------------------------------------------------\n");

            printf("| %-10s | %-20s | %-10s | %-6.2f |\n",
                   s->roll_no, s->name, s->semester, s->cgpa);

            printf("---------------------------------------------------------------------------------------------\n");
        }
    }
    if (flag)
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

int loadData(struct Student *students, int maxCount)
{
    FILE *file = fopen("D:\\code\\FE-CPP1-EMS\\Data\\students.json", "r");
    if (!file)
    {
        perror("Error opening file");
        return 0;
    }
    // Get file size
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    // Read file into buffer
    char *data = (char *)malloc(length + 1);
    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);
    // Parse JSON array
    cJSON *jsonArray = cJSON_Parse(data);
    free(data);
    if (!jsonArray || !cJSON_IsArray(jsonArray))
    {
        printf("Error: Invalid JSON format.\n");
        cJSON_Delete(jsonArray);
        return 0;
    }
    int cnt = cJSON_GetArraySize(jsonArray);
    if (cnt > maxCount)
        cnt = maxCount; // prevent overflow

    for (int i = 0; i < cnt; i++)
    {
        cJSON *studentObj = cJSON_GetArrayItem(jsonArray, i);
        strcpy(students[i].roll_no, cJSON_GetObjectItem(studentObj, "roll_no")->valuestring);
        strcpy(students[i].name, cJSON_GetObjectItem(studentObj, "name")->valuestring);
        strcpy(students[i].semester, cJSON_GetObjectItem(studentObj, "semester")->valuestring);
        students[i].cgpa = (float)cJSON_GetObjectItem(studentObj, "cgpa")->valuedouble;

        cJSON *marksObj = cJSON_GetObjectItem(studentObj, "marks_info");
        struct marks *m = &students[i].marks_info;
        if (marksObj && cJSON_IsObject(marksObj))
        {
            cJSON *temp;
            temp = cJSON_GetObjectItem(marksObj, "itfa");
            if (temp)
                m->itfa = temp->valueint;

            temp = cJSON_GetObjectItem(marksObj, "cp");
            if (temp)
                m->cp = temp->valueint;

            temp = cJSON_GetObjectItem(marksObj, "ap");
            if (temp)
                m->ap = temp->valueint;

            temp = cJSON_GetObjectItem(marksObj, "pst");
            if (temp)
                m->pst = temp->valueint;

            temp = cJSON_GetObjectItem(marksObj, "cag");
            if (temp)
                m->cag = temp->valueint;

            temp = cJSON_GetObjectItem(marksObj, "fe");
            if (temp)
                m->fe = temp->valueint;

            temp = cJSON_GetObjectItem(marksObj, "itfa_credithours");
            if (temp)
                m->itfa_credithours = temp->valueint;

            temp = cJSON_GetObjectItem(marksObj, "cp_credithours");
            if (temp)
                m->cp_credithours = temp->valueint;

            temp = cJSON_GetObjectItem(marksObj, "ap_credithours");
            if (temp)
                m->ap_credithours = temp->valueint;

            temp = cJSON_GetObjectItem(marksObj, "pst_credithours");
            if (temp)
                m->pst_credithours = temp->valueint;
            temp = cJSON_GetObjectItem(marksObj, "cag_credithours");
            if (temp)
                m->cag_credithours = temp->valueint;
            temp = cJSON_GetObjectItem(marksObj, "fe_credithours");
            if (temp)
                m->fe_credithours = temp->valueint;
            temp = cJSON_GetObjectItem(marksObj, "itfa_gradescore");
            if (temp)
                m->itfa_gradescore = (float)temp->valuedouble;
            temp = cJSON_GetObjectItem(marksObj, "cp_gradescore");
            if (temp)
                m->cp_gradescore = (float)temp->valuedouble;
            temp = cJSON_GetObjectItem(marksObj, "ap_gradescore");
            if (temp)
                m->ap_gradescore = (float)temp->valuedouble;
            temp = cJSON_GetObjectItem(marksObj, "pst_gradescore");
            if (temp)
                m->pst_gradescore = (float)temp->valuedouble;
            temp = cJSON_GetObjectItem(marksObj, "cag_gradescore");
            if (temp)
                m->cag_gradescore = (float)temp->valuedouble;
            temp = cJSON_GetObjectItem(marksObj, "fe_gradescore");
            if (temp)
                m->fe_gradescore = (float)temp->valuedouble;
        }
        else
        {
            printf("Warning: 'marks_info' missing for student %d!\n", i + 1);
        }
        cJSON *attendanceArray = cJSON_GetObjectItem(studentObj, "attendance");
        if (cJSON_IsArray(attendanceArray))
        {
            int len = cJSON_GetArraySize(attendanceArray);
            for (int j = 0; j < SUBJECTS && j < len; j++)
            {
                cJSON *attItem = cJSON_GetArrayItem(attendanceArray, j);
                if (cJSON_IsNumber(attItem))
                    students[i].attendance[j] = attItem->valueint;
                else
                    students[i].attendance[j] = 0; // default to 0 if not numeric
            }
        }
        else
        {
            // If no attendance in file, default all to 0
            for (int j = 0; j < SUBJECTS; j++)
                students[i].attendance[j] = 0;
        }
    }
    printf("Loaded %d students from JSON file.\n", cnt);
    return cnt;
}

void menu(struct Student *s)
{
    students = s;
    int choice;
    do
    {
        printf("\n =================================== Student Management System ==================================\n");
        printf("\t1. Add Student\n");
        printf("\t2. Display All Students\n");
        printf("\t3. Search Student\n");
        printf("\t4. Edit Student\n");
        printf("\t5. Delete Student\n");
        printf("\t6. Save & Exit\n");
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
            searchStudent(students, count);
            break;
        case 4:
            editStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            saveDataArray(students, count, 1);
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    free(students);
}

// sitiing arrangement
void sittingArrangement(int count, struct Student *students)
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