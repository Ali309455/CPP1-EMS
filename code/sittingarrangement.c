#include "../header files/sittingarrangement.h"
#include "../header files/studentmanagement.h"
// void sa_init(void) {
//     printf("sa initialized.\n");
// }
void sittingArrangement(int count, struct Student *students)
{
    int rooms, capacity;
    printf("Enter number of rooms: ");
    scanf("%d", &rooms);
    printf("Enter capacity of each room: ");
    scanf("%d", &capacity);

    int totalSeats = rooms * capacity;

    if (count > totalSeats)
    {
        printf("Not enough seats for all students! Total seats: %d, Students: %d\n",
               totalSeats, count);
        return;
    }

    printf("\n===== Sitting Arrangement =====\n");

    int studentIndex = 0;

    for (int r = 1; r <= rooms; r++)
    {
        printf("\nRoom %d:\n", r);
        for (int s = 1; s <= capacity; s++)
        {
            if (studentIndex < count)
            {
                struct Student *st = students + studentIndex;
                printf("%s(%s)\t", (*st).name, (*st).roll_no);
                studentIndex++;
            }
            else
            {
                printf("Empty\t");
            }
        }
        printf("\n");
    }
}
