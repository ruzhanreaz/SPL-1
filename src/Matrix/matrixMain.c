#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void matrixMenu()
{
    while (1)
    {
        drawTitle(2);
        printf("1. Set Matrix\n");
        printf("2. Show Matrix\n");
        printf("3. Show All Matrix\n");
        printf("4. LU Decomposition\n");
        printf("5. QR Decomposition\n");
        printf("6. Clear Matrix\n");
        printf("7. Clear All Matrix\n");
        printf("8. Back\n");
        printf("9. Reset\n");
        printf("10. Exit\n");
        drawLine();
        printf("Select an option: ");
        char str[MAX_INPUT_SIZE];
        getStrInput(str);
        checkInput(str);
        int option = atoi(str);
        switch (option)
        {
        case 1:
            setMatrix();
            matrix();
            break;
        case 2:
            showMatrix();
            matrix();
            break;
        case 3:
            showAllMatrix();
            matrix();
            break;
        case 4:
            luDecomposition();
            matrix();
            break;
        case 5:
            qrDecomposition();
            matrix();
            break;
        case 6:
            clearMatrix();
            matrix();
            break;
        case 7:
            clearAllMatrix();
            matrix();
            break;
        case 8:
            matrix();
            break;
        case 9:
            matrixReset();
            matrix();
            break;
        case 10:
            clearAllMatrix();
            clearScreen();
            exit(0);
        default:
            matrix();
            break;
        }
    }
}
void matrix()
{
    drawTitle(3);
    char expression[MAX_INPUT_SIZE];
    while (1)
    {
        getStrInput(expression);
        checkInput(expression);
        int isValid = 1;
        Queue *infixQueue = createQueue();
        isValid = tokenize(infixQueue, expression);
        if (!isValid || isQueueEmpty(infixQueue))
        {
            freeQueue(infixQueue);
            continue;
        }
        // printQueue(infixQueue);
        Queue *postfixQueue = createQueue();
        infixToPostfix(infixQueue, postfixQueue);
        // printQueue(postfixQueue);
        freeQueue(infixQueue);
        char result[MAX_INPUT_SIZE];
        postfixEvaluateMat(postfixQueue, result);
        freeQueue(postfixQueue);
        if (result[0] != '\0' && !isMatrix(result))
        {
            outputString(result);
        }
        else if (result[0] != '\0')
        {
            Matrix matrix = getMatrix(result);
            if (matrix.matrix == NULL)
            {
                printf("Matrix not found\n");
            }
            else
            {
                drawTitle(3);
                printf("Matrix: %s\n", "Result");
                for (int i = 0; i < matrix.rows; i++)
                {
                    for (int j = 0; j < matrix.cols; j++)
                    {
                        printf("%-10s", modifyDouble(matrix.matrix[i][j]));
                    }
                    printf("\n");
                }
                drawLine();

                printf("Do you want to save the result? (y/n): ");
                char str[MAX_INPUT_SIZE];
                getStrInput(str);
                checkInput(str);
                if (str[0] == 'y' || str[0] == 'Y')
                {
                    printf("Enter matrix name: ");
                    getStrInput(str);
                    checkInput(str);
                    if (isMatrix(str))
                    {
                        printf("Matrix name already exists or invalid name\n");
                    }
                    else if (!validateMatrixName(str))
                    {
                        printf("Invalid matrix name\n");
                    }
                    else
                    {
                        saveMatrix(str, &matrix);
                        saveMainMatrix(str, &matrix);
                    }
                }
                else
                {
                    drawTitle(3);
                    continue;
                }
            }
        }
    }
}