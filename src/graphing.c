#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "header.h"

Equation *equations = NULL;
int numOfEquations = 0;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

bool windowOpen = false;
double xMin = -10;
double xMax = 10;
double yMin = -10;
double yMax = 10;

bool createGraphWindow()
{
    window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    windowOpen = true;
    return true;
}

void closeGraphWindow()
{
    if (windowOpen)
    {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        window = NULL;
        renderer = NULL;
        windowOpen = false;
    }
    SDL_Delay(16);
}

void drawText(const char *text, int x, int y)
{
    SDL_Color textColor = {0, 0, 0, 255}; // Black color
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

char text[20];
void setXValue(double x)
{
    sprintf(text, "%.1f", x);
}

void getXValue(char *value)
{
    strcpy(value, text);
}

double evaluateExpression(char *expression, double x)
{
    setXValue(x);
    Queue *infix = createQueue();
    Queue *postfix = createQueue();
    if (!tokenize(infix, expression))
    {
        return 0;
    }
    infixToPostfix(infix, postfix);
    char *result = malloc(100);
    postfixEvaluateComp(postfix, result);
    double value = atof(result);
    freeQueue(infix);
    freeQueue(postfix);
    return value;
}

void drawGraph(Equation *equations, int numOfEquations)
{
    if (!windowOpen)
    {
        if (!createGraphWindow())
        {
            return;
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color for axes

    // Draw axes
    SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2); // X-axis
    SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT);  // Y-axis

    // Draw units and numbering
    int unit_size = 40; // Increase the interval between numbers
    for (int i = 0; i < SCREEN_WIDTH; i += unit_size)
    {
        SDL_RenderDrawLine(renderer, i, SCREEN_HEIGHT / 2 - 5, i, SCREEN_HEIGHT / 2 + 5);
        if (i != SCREEN_WIDTH / 2)
        {
            char text[20];
            sprintf(text, "%.1f", xMin + (xMax - xMin) * (i / (double)SCREEN_WIDTH));
            drawText(text, i, SCREEN_HEIGHT / 2 + 10);
        }
    }
    for (int i = 0; i < SCREEN_HEIGHT; i += unit_size)
    {
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 - 5, i, SCREEN_WIDTH / 2 + 5, i);
        if (i != SCREEN_HEIGHT / 2)
        {
            char text[20];
            sprintf(text, "%.1f", (SCREEN_HEIGHT / 2 - i) * (xMax - xMin) / SCREEN_WIDTH);
            drawText(text, SCREEN_WIDTH / 2 + 10, i);
        }
    }

    SDL_Color colors[] = {
        {139, 0, 0, 255},   // Dark Red
        {0, 100, 0, 255},   // Dark Green
        {0, 0, 139, 255},   // Dark Blue
        {139, 139, 0, 255}, // Dark Yellow
        {139, 0, 139, 255}, // Dark Magenta
        {0, 139, 139, 255}, // Dark Cyan
        {255, 140, 0, 255}, // Dark Orange
        {75, 0, 130, 255},  // Dark Purple
        {0, 128, 128, 255}, // Dark Teal
        {85, 107, 47, 255}  // Dark Olive
    };
    int num_colors = sizeof(colors) / sizeof(colors[0]);

    for (int i = 0; i < numOfEquations; i++)
    {
        SDL_SetRenderDrawColor(renderer, colors[i % num_colors].r, colors[i % num_colors].g, colors[i % num_colors].b, colors[i % num_colors].a);

        for (int x = 1; x < SCREEN_WIDTH; x++)
        {
            double x_val = xMin + (xMax - xMin) * (x / (double)SCREEN_WIDTH); // Scale x value
            double y_val = evaluateExpression(equations[i].equation, x_val);

            int y = (int)(-y_val * SCREEN_WIDTH / (xMax - xMin) + SCREEN_HEIGHT / 2); // Scale and invert y value

            SDL_RenderDrawPoint(renderer, x, y);
        }
    }

    SDL_RenderPresent(renderer);
}

int plot()
{
    drawTitle(2);
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    if (TTF_Init() == -1)
    {
        printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
        return -1;
    }

    font = TTF_OpenFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf", 10); // Smaller font size
    if (font == NULL)
    {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        return -1;
    }
    drawGraph(equations, numOfEquations);
    printf("Enter the range for x-axis (e.g., -10 10): ");
    scanf("%lf %lf", &xMin, &xMax);
    getchar(); // Consume the newline character left by scanf

    drawTitle(2);
    char input[256];

    while (true)
    {
        printf("Y%d = ", numOfEquations + 1);
        getStrInput(input);
        if (numOfEquations < 10)
        {
            equations = (Equation *)realloc(equations, (numOfEquations + 1) * sizeof(Equation));
            equations[numOfEquations].equation = (char *)malloc(strlen(input) + 1);
            strcpy(equations[numOfEquations].equation, input);
            equations[numOfEquations].color = numOfEquations;
            numOfEquations++;
            drawGraph(equations, numOfEquations);
        }
        else
        {
            printf("Maximum number of equations reached\n");
        }
        SDL_Delay(100); // Add delay to reduce CPU usage
    }

    TTF_CloseFont(font);
    TTF_Quit();
    closeGraphWindow();
    SDL_Quit();
    return 0;
}

void clearGraph()
{
    if (windowOpen)
    {
        numOfEquations = 0;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}

void graphing()
{
    showGraphingMenu();
}