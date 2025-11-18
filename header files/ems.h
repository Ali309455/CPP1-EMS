#ifndef PORTAL_H
#define PORTAL_H

#include <stdio.h>
#define SUBJECTS 6
#define MAX_STUDENTS 100

//----------------------------------------------------
// MARKS STRUCTURE
//----------------------------------------------------
struct marks {
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
};

//----------------------------------------------------
// MAIN STUDENT STRUCTURE
//----------------------------------------------------
struct Student {
    char roll_no[10];
    char name[50];
    char semester[20];
    float cgpa;
    struct marks marks_info;
    int attendance[SUBJECTS];
};
//----------------------------------------------------
// MAIN CREDENTIAL STRUCTURE
//----------------------------------------------------
struct portal_info
{
    char teacher_password[20];
    char admin_password[20];
    char q1[25];
    char q2[25];
};
//----------------------------------------------------
// LOADING & SAVING (JSON / FILE)
//----------------------------------------------------
void saveDataArray(struct Student *s, int cnt, int);
int loadData(struct Student *students, int maxCount);
void load_credentials(struct portal_info *cred, int);
void save_password(struct portal_info cred);
//----------------------------------------------------
// ATTENDANCE MANAGEMENT FUNCTIONS
//----------------------------------------------------
void takeAttendance(struct Student *students, int totalStudents);
void displayAttendance(struct Student *students, int totalStudents);
void checkTotalAttendance(struct Student *students, int totalStudents);
void attendance_management(struct Student *students, int);
//----------------------------------------------------
// STUDENT MANAGEMENT FUNCTIONS
//----------------------------------------------------
void addStudent();
void displayStudents();
void searchStudent(struct Student *students, int cnt);
void editStudent();
void deleteStudent();
void menu(struct Student *s);

//----------------------------------------------------
// RESULT PROCESSING FUNCTIONS
//----------------------------------------------------
void printdata(struct Student *pstr, int );
void add_marks_data(struct Student *arr, int count);
void printMenu(void);
void calculate_cgpa(struct Student *pstr, int count);
void edit_marks_data(struct Student *pstr, char roll_no[19], int);
void search_marks_data(struct Student *pstr, char roll_no[19], int);
void delete_marks_data(struct Student *pstr, char roll_no[19]);
void tabulation(struct Student *pstr , int );

//----------------------------------------------------
// SITTING ARRANGEMENT
//----------------------------------------------------
void sittingArrangement(int count, struct Student *students);

//----------------------------------------------------
// PORTAL
//----------------------------------------------------
void load_credentials(struct portal_info *cred, int);
void save_password(struct portal_info cred);
void forget_password(struct portal_info cred);
void change_password(int choice, struct portal_info *cred);
void Admin_interface(struct portal_info *cred);
void first_time_login(struct portal_info *cred);
int login(struct portal_info cred);
int portal();

#endif
