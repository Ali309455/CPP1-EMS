#ifndef PORTAL_H
#define PORTAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

// Structure to store portal credentials and security questions
struct portal_info
{
    char teacher_password[20];
    char admin_password[20];
    char q1[25];
    char q2[25];
};

// Function declarations
void load_credentials(struct portal_info *cred, int);
void save_password(struct portal_info cred);
void forget_password(struct portal_info cred);
void change_password(int choice, struct portal_info *cred);
void Admin_interface(struct portal_info *cred);
void first_time_login(struct portal_info *cred);
int login(struct portal_info cred);
int portal();
#endif // PORTAL_H
