#ifndef RESULTPROCESSING_H
#define RESULTPROCESSING_

#include <stdio.h>
#include "../header files/studentmanagement.h"

// ======================= GLOBAL VARIABLES =======================
  // defined in resultprocessing.c

// ======================= FUNCTION DECLARATIONS =======================

// Load data from JSON file into Student array
// int load_Data(struct Student *students, int maxCount);

// Save array of Students into JSON file
// void save_DataArray(struct Student *s, int count);

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
void tabulation(struct Student *pstr , int );

#endif // RESULTPROCESSING_H
