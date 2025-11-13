#include <stdio.h>
#include <stdlib.h>
#include "../header files/studentmanagement.h"
#include "../header files/Portal.h"
// #include "../header files/resultprocessing.h"
#include "../header files/sittingarrangement.h"
#include "../header files/attendancemanagement.h"
int count;
struct Student *s;
// struct Student s[] = {
//     {
//         "cs-001", "Ali", "fall", 0.0,
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0}
//     },
//     {
//         "cs-002", "Abdul Wahab", "fall", 0.0,
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0}
//     },
//     {
//         "cs-003", "rafay", "fall", 0.0,
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0}
//     },
//     {
//         "cs-091", "DKJ", "fall", 0.0,
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0}
//     },
//     {
//         "0s-020", "r", "fa", 0.0,
//         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//         {0, 0, 0, 0, 0, 0}
//     }
// };
void main(void)
{
    s = calloc(20 , sizeof(struct Student));
    count = loadData(s, 5);
    // ems_init();
    // portal();
    // menu(&s);
    attendance_management(s, count);
    // sittingArrangement(count, s);
}