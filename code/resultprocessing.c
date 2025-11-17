#include "../header files/resultprocessing.h"
#include "../header files/studentmanagement.h"
#include <string.h>
#include <stdlib.h>
#include "../header files/cJSON.h"

int CNT;
// struct Student *students;

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
    printf("\t -----------------> MARKS AND RESULT PROCESSIONG \t <-----------------\n");
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

    int choice;
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