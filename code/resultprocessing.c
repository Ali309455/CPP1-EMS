#include "../header files/resultprocessing.h"
#include <string.h>
#include <stdlib.h>
#include "../header files/cJSON.h"

int CNT;
int load_Data(struct Student *students, int maxCount)
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

    int count = cJSON_GetArraySize(jsonArray);
    if (count > maxCount)
        count = maxCount; // prevent overflow

    for (int i = 0; i < count; i++)
    {
        cJSON *studentObj = cJSON_GetArrayItem(jsonArray, i);
        strcpy(students[i].roll_no, cJSON_GetObjectItem(studentObj, "roll_no")->valuestring);
        strcpy(students[i].name, cJSON_GetObjectItem(studentObj, "name")->valuestring);
        strcpy(students[i].year_sem, cJSON_GetObjectItem(studentObj, "year_sem")->valuestring);
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
    }
    return count;
}

void save_DataArray(struct Student *s, int count)
{
    cJSON *jsonArray = cJSON_CreateArray();

    for (int i = 0; i < count; i++)
    {
        // Create JSON object for each student
        cJSON *studentObj = cJSON_CreateObject();
        cJSON_AddStringToObject(studentObj, "roll_no", s[i].roll_no);
        cJSON_AddStringToObject(studentObj, "name", s[i].name);
        cJSON_AddStringToObject(studentObj, "year_sem", s[i].year_sem);
        cJSON_AddNumberToObject(studentObj, "cgpa", s[i].cgpa);

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

void printdata(struct Student *pstr)
{
    printf("=====================================================================================================\n");
    printf("| %-7s | %-10s | %-4s | %-4s | %-4s | %-4s | %-4s | %-4s | %-6s |\n",
           "Roll No", "Name", "ITFA", "CP", "AP", "PST", "CAG", "FE", "CGPA");
    printf("=====================================================================================================\n");

    for (int i = 0; i < CNT; i++)
    {
        struct marks m = pstr[i].marks_info;

        printf("| %-7s | %-10s | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | %-6.2f |\n",
               pstr[i].roll_no, pstr[i].name,
               m.itfa, m.cp, m.ap, m.pst, m.cag, m.fe,
               pstr[i].cgpa);
    }

    printf("=====================================================================================================\n");
}
void add_marks_data(struct Student *arr, int count)
{
    printf("-----> Enter -1 to exit add marks section <------ \n");
    for (int i = 0; i < count; i++)
    {
        printf("Enter %s(%s)   marks in itfa: ", arr[i].roll_no, arr[i].name);
        scanf("%d", &arr[i].marks_info.itfa);
        if (arr[i].marks_info.itfa == -1)
            break;
        printf("Enter %s(%s)  marks in cp: ", arr[i].roll_no, arr[i].name);
        scanf("%d", &arr[i].marks_info.cp);
        if (arr[i].marks_info.cp == -1)
            break;
        printf("Enter %s(%s)  marks in ap: ", arr[i].roll_no, arr[i].name);
        scanf("%d", &arr[i].marks_info.ap);
        if (arr[i].marks_info.ap == -1)
            break;
        printf("Enter %s(%s)  marks in pst: ", arr[i].roll_no, arr[i].name);
        scanf("%d", &arr[i].marks_info.pst);
        if (arr[i].marks_info.pst == -1)
            break;
        printf("Enter %s(%s)  marks in cag: ", arr[i].roll_no, arr[i].name);
        scanf("%d", &arr[i].marks_info.cag);
        if (arr[i].marks_info.cag == -1)
            break;
        printf("Enter %s(%s)  marks in fe: ", arr[i].roll_no, arr[i].name);
        scanf("%d", &arr[i].marks_info.fe);
        if (arr[i].marks_info.fe == -1)
            break;
        if (count == 0)
        {
            printf("-----> Same credit hours will be added for every Student <------\n");
            printf("Enter %s(%s)  itfa_credithours: ", arr[i].roll_no, arr[i].name);
            scanf("%d", &arr[i].marks_info.itfa_credithours);
            if (arr[i].marks_info.itfa_credithours == -1)
                break;
            printf("Enter %s(%s)  cp_credithours: ", arr[i].roll_no, arr[i].name);
            scanf("%d", &arr[i].marks_info.cp_credithours);
            if (arr[i].marks_info.cp_credithours == -1)
                break;
            printf("Enter %s(%s)  ap_credithours: ", arr[i].roll_no, arr[i].name);
            scanf("%d", &arr[i].marks_info.ap_credithours);
            if (arr[i].marks_info.ap_credithours == -1)
                break;
            printf("Enter %s(%s)  pst_credithours: ", arr[i].roll_no, arr[i].name);
            scanf("%d", &arr[i].marks_info.pst_credithours);
            if (arr[i].marks_info.pst_credithours == -1)
                break;
            printf("Enter %s(%s)  cag_credithours: ", arr[i].roll_no, arr[i].name);
            scanf("%d", &arr[i].marks_info.cag_credithours);
            if (arr[i].marks_info.itfa == -1)
                break;
            printf("Enter %s(%s)  fe_credithours: ", arr[i].roll_no, arr[i].name);
            scanf("%d", &arr[i].marks_info.fe_credithours);
        }
        else {
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
    printf("\t ------> MARKS AND RESULT PROCESSIONG \t <------\n");
    printf("\t1. Add marks data\n");
    printf("\t2. Update marks data\n");
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
    printdata(pstr);
}
void edit_marks_data(struct Student *pstr, char roll_no[19])
{
    int index = 0;
    for (int i = 0; i < CNT; i++)
    {
        if (strcasecmp(pstr[i].roll_no, roll_no) == 0)
        {
            index = i;
            break;
        }
    }
    if (pstr[index].roll_no != NULL)
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
void search_marks_data(struct Student *pstr, char roll_no[19])
{
    for (int i = 0; i < CNT; i++)
    {
        if (strcasecmp(pstr[i].roll_no, roll_no) == 0)
        {
            printf("=====================================================================================================\n");
            printf("| %-7s | %-10s | %-4s | %-4s | %-4s | %-4s | %-4s | %-4s | %-6s |\n",
                   "Roll No", "Name", "ITFA", "CP", "AP", "PST", "CAG", "FE", "CGPA");
            printf("=====================================================================================================\n");

            struct marks m = pstr[i].marks_info;

            printf("| %-7s | %-10s | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | %-6.2f |\n",
                   pstr[i].roll_no, pstr[i].name,
                   m.itfa, m.cp, m.ap, m.pst, m.cag, m.fe,
                   pstr[i].cgpa);

            printf("=====================================================================================================\n");
        }
    }
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
void tabulation(void)
{
    struct Student students[MAX] = {};

    int choice;
    CNT = load_Data(students, MAX);
    printf("\t-------> THE DATA IS <-------\n ");
    printdata(students);
    while (1)
    {
        printMenu();
        printf("Enter Your Choice ( 1-5 ) : ");
        scanf("%d", &choice);
        char roll_no[19];
        if (choice >= 1 && choice <= 4)
        {
            switch (choice)
            {
            case 1:
                CNT = load_Data(students, MAX);
                add_marks_data(students, CNT);
                save_DataArray(students, CNT);
                printf("\t ------> Your marks data is saved successfully and the data is : \n");
                printdata(students);
                break;
            case 2:
                if (CNT == 0)
                {
                    printf("NO DATA STORED\n");
                    break;
                }
                printf("Enter Roll No: ");
                scanf("%s", roll_no);
                edit_marks_data(students, roll_no);
                break;
            case 3:
                if (CNT == 0)
                {
                    printf("NO DATA STORED\n");
                    break;
                }
                printf("Enter Roll No: ");
                scanf("%s", roll_no);
                search_marks_data(students, roll_no);
                break;
            case 4:
                if (CNT == 0)
                {
                    printf("NO DATA STORED\n");
                    break;
                }
                calculate_cgpa(students, CNT);
                break;

            default:
                break;
            }
        }
        else
        {
            save_DataArray(students, CNT);
            return;
        }
    }
}