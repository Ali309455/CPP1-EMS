#include "../header files/studentmanagement.h"

// void ems_init(void) {
//     printf("EMS initialized.\n");
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header files/cJSON.h"

struct Student *students ;

int count = 0;

void saveDataArray(struct Student *s, int count)
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
        for (int j = 0; j < SUBJECTS; j++)
            attendanceArr[j] = 0;
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
        saveDataArray(students, count);
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
        printf("%s\n", students[i].roll_no);
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


// void sittingArrangement()
// {
//     int rooms, capacity;
//     printf("Enter number of rooms: ");
//     scanf("%d", &rooms);
//     printf("Enter capacity of each room: ");
//     scanf("%d", &capacity);

//     int totalSeats = rooms * capacity;

//     if (count > totalSeats)
//     {
//         printf("Not enough seats for all students! Total seats: %d, Students: %d\n",
//                totalSeats, count);
//         return;
//     }

//     printf("\n===== Sitting Arrangement =====\n");

//     int studentIndex = 0;

//     for (int r = 1; r <= rooms; r++)
//     {
//         printf("\nRoom %d:\n", r);
//         for (int s = 1; s <= capacity; s++)
//         {
//             if (studentIndex < count)
//             {
//                 struct Student *st = students + studentIndex;
//                 printf("%s(%s)\t", (*st).name, (*st).roll_no);
//                 studentIndex++;
//             }
//             else
//             {
//                 printf("Empty\t");
//             }
//         }
//         printf("\n");
//     }
// }

void menu(struct Student *s)
{
    students = s;
    // memset(students, 0, sizeof(students));
    // count =    loadData(students, 4);
    int choice;

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
            printf("%s", students[0].roll_no);
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
            printf("%d\n", count);
            saveDataArray(students, count);
            printf("Data saved. Exiting...\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    free(students);
}