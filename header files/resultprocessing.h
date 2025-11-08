#ifndef RESULTPROCESSING_H
#define RESULTPROCESSING_

#include <stdio.h>


// ======================= CONSTANTS =======================
#define MAX 100

// ======================= STRUCTURES ======================
struct marks
{
    int itfa;
    int cp;
    int ap;
    int pst;
    int cag;
    int fe;

    int itfa_credithours;
    int cp_credithours;
    int ap_credithours;
    int pst_credithours;
    int cag_credithours;
    int fe_credithours;

    float itfa_gradescore;
    float cp_gradescore;
    float ap_gradescore;
    float pst_gradescore;
    float cag_gradescore;
    float fe_gradescore;
};

struct Student
{
    char roll_no[20];
    char name[20];
    char year_sem[20];
    float cgpa;
    struct marks marks_info;
};

// ======================= GLOBAL VARIABLES =======================
extern int CNT;  // defined in resultprocessing.c

// ======================= FUNCTION DECLARATIONS =======================

// Load data from JSON file into Student array
int loadData(struct Student *students, int maxCount);

// Save array of Students into JSON file
void saveDataArray(struct Student *s, int count);

// Calculate grade point based on marks
float grade_points(int marks);

// Print all student data in table format
void printdata(struct Student *pstr);

// Add marks interactively
void add_marks_data(struct Student *arr, int count);

// Display main menu for result processing
void printMenu(void);

// Calculate CGPA for all students
void calculate_cgpa(struct Student *pstr, int count);

// Edit a specific student’s marks using roll number
void edit_marks_data(struct Student *pstr, char roll_no[19]);

// Search and display a specific student’s marks
void search_marks_data(struct Student *pstr, char roll_no[19]);

// Delete a student’s record by roll number
void delete_marks_data(struct Student *pstr, char roll_no[19]);

// Entry point for marks and result tabulation menu
void tabulation(void);

#endif // RESULTPROCESSING_H
