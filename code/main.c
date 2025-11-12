#include <stdio.h>
#include <stdlib.h>
#include "../header files/studentmanagement.h"
#include "../header files/Portal.h"
// #include "../header files/resultprocessing.h"
#include "../header files/sittingarrangement.h"
#include "../header files/attendancemanagement.h"
int count;
struct Student *s;
void main(void)
{
    s = calloc(20 , sizeof(struct Student));
    count = loadData(s, 5);
    // printf("here");
    // ems_init();
    // portal();
    menu(s);
    takeAttendance(s, count);
    // sittingArrangement(count, s);
}