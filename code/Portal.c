#include"../header files/Portal.h"
#include<stdio.h>

void signin(){
    int roll = 0;
    printf("Enter Your Roll No: ");
    scanf("%d", &roll);
    printf("Your roll No is: %d", roll);
    if(roll == 1){
        printf("\nWelcome to Student Portal");
    }
}