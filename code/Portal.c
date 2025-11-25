#include "../header files/Portal.h"
#include "../header files/studentmanagement.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "../header files/cJSON.h"

// loads credentials from a json file
void load_credentials(struct portal_info *cred, int flag)
{
    if (cred == NULL)
    {
        printf("Error: NULL pointer passed to load_credentials.\n");
        return;
    }
    // --- Open file for reading ---
    FILE *file = fopen("../Data/credentials.json", "r");
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
    // --- Copy data into structure and ensure null termination ---
    strncpy(cred->teacher_password, teacher->valuestring, sizeof(cred->teacher_password) - 1);
    strncpy(cred->admin_password, admin->valuestring, sizeof(cred->admin_password) - 1);
    strncpy(cred->q1, cJSON_GetObjectItem(json, "q1")->valuestring, sizeof(cred->q1) - 1);
    strncpy(cred->q2, cJSON_GetObjectItem(json, "q2")->valuestring, sizeof(cred->q2) - 1);

    cred->teacher_password[sizeof(cred->teacher_password) - 1] = '\0';
    cred->admin_password[sizeof(cred->admin_password) - 1] = '\0';
if (flag == 1)
    printf("Credentials loaded successfully.\n");
    cJSON_Delete(json);
}

// saves password in json file
void save_password(struct portal_info cred)
{
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "teacher_password", cred.teacher_password);
    cJSON_AddStringToObject(json, "admin_password", cred.admin_password);
    cJSON_AddStringToObject(json, "q1", cred.q1);
    cJSON_AddStringToObject(json, "q2", cred.q2);

    FILE *file = fopen("../Data/credentials.json", "w");
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

// forget password functionality
void forget_password(struct portal_info cred)
{
    char ans1[25];
    char ans2[25];
    printf(" -----> You need to answer these 2 security Questions <----\n");
    printf("Q1: What is your favorite color?\n");
    scanf("%s", &ans1);
    printf("Q2: What is your favorite animal?\n");
    scanf("%s", &ans2);
    if (strcmp(ans1, cred.q1) == 0 && strcmp(ans2, cred.q2) == 0)
    {
        printf("Admin Password: %s\n", cred.admin_password);
        printf("Teacher Password: %s\n", cred.teacher_password);
        printf("Press any key to continue ....\n");
        getch();
    }
    else
    {
        printf("Wrong Answers\n");
        printf("Press any key to continue ....\n");
        getch();
    }
}

// change save_password functionality
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
    case 0:
        printf("Exiting Security Dashboard ..\n");
        return;
    default:
        printf("Invalid Choice");
        break;
    }
}

// Admin Interface
void Admin_interface(struct portal_info *cred)
{
    int admin_choice;
    printf("---------------------> Admin Interface <---------------------\n");
    printf("Enter 1 to change password of Teachers\n");
    printf("Enter 2 to change Password of Admin\n");
    printf("Enter 3 if you forget password\n");
    printf("Enter 0 to exit Security Dashboard\n");
    printf("Enter your choice: ");
    scanf("%d", &admin_choice);
    change_password(admin_choice, cred);
}

// when no credentials file this function is called
void first_time_login(struct portal_info *cred)
{
    char password[30];
    printf("------------------------------> YOUR USING THE SYSTEM FIRST TIME SET ADMIN AND TEACHER PASSWORDS <-----------------\n");

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

// login interface of the EMS
int login(struct portal_info cred)
{
    char password[30];
    int status_choice, forget_choice;
    printf("------------------------------------> WELCOME TO EXAMINATION MANAGEMENT SYSTEM <----------------------\n");
    printf("\n0-> Student \n1-> Teacher\n2-> Admin \n \n");
    printf("Enter your status: ");
    scanf("%d", &status_choice);
    if (status_choice == 1 || status_choice == 2)
    {
        printf("\n1-> Enter Password \n0-> forget PAssword\nEnter your Choice: ");scanf("%d",&forget_choice);
        if(forget_choice == 1 ){
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
        }}
        else if(forget_choice == 0){
            forget_password(cred);
        }
        else{
            printf("Invalid Choice...");
        }
    }
    else
    {
        printf("----------> Student Interface <----------\n");
        return 0;
    }
}

// main function of this file
int portal(void)
{
    struct portal_info credentials;
    // setting all credentials to 0
    memset(&credentials, 0, sizeof(credentials));
    load_credentials(&credentials, 0);
    // checks if credentials are empty
    if (strlen(credentials.admin_password) == 0){
        clearScreen();
        first_time_login(&credentials);}
    int status = login(credentials);
    return status;
}