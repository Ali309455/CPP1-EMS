#include<stdio.h>
#include "../header files/studentmanagement.h"
#include "../header files/attendancemanagement.h"
#include "../header files/Portal.h"
#include "../header files/resultprocessing.h"


void main(void)
{
printf("Hellow World");
ems_init();
ams_init();
rps_init();
signin();
}