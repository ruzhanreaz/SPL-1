#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "normalCalculator.h"

int main()
{
    printf("\033[H\033[J");
    char infix[100];
    char postfix[100];
    printf("Normal Mode         Press 'm' for Menu\n");
    printf("--------------------------------------------------\n");
    while (1)
    {

        // printf("Enter the infix expression: ");
        fgets(infix, 100, stdin);
        if (infix[0] == 'm' || infix[0] == 'M')
        {
            printf("\033[H\033[J");
            display_menu();
            printf("Normal Mode         Press 'm' for Menu\n");
            printf("--------------------------------------------------\n");
            continue;
        }

        infix[strcspn(infix, "\n")] = '\0';
        infixToPostfix(infix, postfix);
        // printf("The postfix expression is: %s\n", postfix);
        // printf("The result of the expression is: %d\n", evaluatePostfix(postfix));
        printf("%d\n", evaluatePostfix(postfix));
        printf("--------------------------------------------------\n");
    }

    return 0;
}
