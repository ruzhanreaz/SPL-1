#include <stdio.h>
#include "menu.h"

void display_menu()
{
    int choice;
    printf("\nMenu:\n");
    printf("1. Normal Mode\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice)
    {
    case 1:
        printf("\033[H\033[J");
        break;
    default:
        printf("Invalid choice! Returning to Normal Mode...\n");
    }
}
