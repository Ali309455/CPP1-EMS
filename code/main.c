#include <stdio.h>
#include <stdlib.h>
#include "../header files/studentmanagement.h"
#include "../header files/attendancemanagement.h"
#include "../header files/Portal.h"
// #include "../header files/resultprocessing.h"
#include "../header files/sittingarrangement.h"
int count;
struct Student *s;
void main(void)
{
    s = malloc(4 * sizeof(struct Student));
    count = loadData(s, 5);
    // ems_init();
    ams_init();
    // portal();
    menu(s);
    sittingArrangement(count, s);
}