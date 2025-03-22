#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "header.h"
#include "graph.h"

Equation *equations = NULL;
int numOfEquations = 0;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;
TTF_Font *labelFont = NULL;

bool windowOpen = false;
double xMin = -10;
double xMax = 10;
double yMin = -10;
double yMax = 10;

SDL_Color colors[] = {
    {255, 0, 0, 255},    // Bright Red
    {0, 128, 0, 255},    // Green
    {0, 0, 255, 255},    // Blue
    {255, 165, 0, 255},  // Orange
    {128, 0, 128, 255},  // Purple
    {0, 139, 139, 255},  // Teal
    {255, 0, 255, 255},  // Magenta
    {184, 134, 11, 255}, // Dark Goldenrod
    {0, 0, 0, 255},      // Black
    {165, 42, 42, 255},  // Brown
    {64, 224, 208, 255}, // Turquoise
    {50, 205, 50, 255}   // Lime Green
};
int num_colors = sizeof(colors) / sizeof(colors[0]);

bool createGraphWindow()
{
    // Initialize SDL if not already initialized
    if (SDL_WasInit(SDL_INIT_VIDEO) == 0)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            return false;
        }
    }

    // Initialize TTF if not already initialized
    if (TTF_WasInit() == 0)
    {
        if (TTF_Init() == -1)
        {
            printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
            return false;
        }
    }

    window = SDL_CreateWindow("Function Grapher", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        window = NULL;
        return false;
    }

    // Try to load a font if not already loaded
    if (font == NULL || labelFont == NULL)
    {
        const char *fontPaths[] = {
            "/usr/share/fonts/truetype/msttcorefonts/Arial.ttf",
            "/usr/share/fonts/TTF/Arial.ttf",
            "Arial.ttf",
            "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"};

        int fontCount = sizeof(fontPaths) / sizeof(fontPaths[0]);

        // Try to load the font from different locations
        for (int i = 0; i < fontCount && font == NULL; i++)
        {
            font = TTF_OpenFont(fontPaths[i], 12);
        }

        for (int i = 0; i < fontCount && labelFont == NULL; i++)
        {
            labelFont = TTF_OpenFont(fontPaths[i], 14);
        }

        if (font == NULL)
        {
            printf("Warning: Failed to load font! TTF_Error: %s\n", TTF_GetError());
            printf("Continuing with default rendering...\n");
        }

        if (labelFont == NULL)
        {
            labelFont = font;
        }
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
        if (font != NULL)
        {
            TTF_CloseFont(font);
            font = NULL;
        }

        if (labelFont != NULL && labelFont != font)
        {
            TTF_CloseFont(labelFont);
            labelFont = NULL;
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        window = NULL;
        renderer = NULL;
        windowOpen = false;
    }

    // Small delay to ensure everything is properly closed
    SDL_Delay(16);
}

void drawText(const char *text, int x, int y)
{
    if (!renderer || !font)
        return;

    SDL_Color textColor = {0, 0, 0, 255}; // Black color
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, textColor);
    if (!textSurface)
    {
        printf("Unable to render text surface! TTF_Error: %s\n", TTF_GetError());
        return;
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture)
    {
        printf("Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void drawColoredText(const char *text, int x, int y, SDL_Color color, TTF_Font *useFont)
{
    if (!renderer)
        return;

    SDL_Surface *textSurface = TTF_RenderText_Solid(useFont ? useFont : font, text, color);
    if (!textSurface)
    {
        return;
    }
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture)
    {
        SDL_FreeSurface(textSurface);
        return;
    }
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
        return NAN;
    }
    infixToPostfix(infix, postfix);
    char *result = malloc(100);
    if (!result)
    {
        freeQueue(infix);
        freeQueue(postfix);
        return NAN;
    }

    postfixEvaluateComp(postfix, result);
    double value = atof(result);
    free(result);
    freeQueue(infix);
    freeQueue(postfix);
    return value;
}

void drawLegend(Equation *equations, int numOfEquations)
{
    if (!renderer || numOfEquations <= 0)
        return;

    int legendX = 10;
    int legendY = 10;
    int legendSpacing = 25;

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 240, 240, 240, 200);

    int maxWidth = 200;
    for (int i = 0; i < numOfEquations; i++)
    {
        int textLength = strlen(equations[i].equation);
        if (textLength * 8 + 30 > maxWidth)
        {
            maxWidth = textLength * 8 + 30;
        }
    }
    maxWidth = (maxWidth > SCREEN_WIDTH - 20) ? SCREEN_WIDTH - 20 : maxWidth;

    SDL_Rect legendBg = {legendX - 5, legendY - 5, maxWidth, numOfEquations * legendSpacing + 10};
    SDL_RenderFillRect(renderer, &legendBg);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &legendBg);

    for (int i = 0; i < numOfEquations; i++)
    {
        SDL_Rect colorBox = {legendX, legendY + i * legendSpacing, 15, 15};
        SDL_SetRenderDrawColor(renderer, colors[i % num_colors].r, colors[i % num_colors].g, colors[i % num_colors].b, colors[i % num_colors].a);
        SDL_RenderFillRect(renderer, &colorBox);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &colorBox);

        char legendText[256];
        sprintf(legendText, "Y%d = %s", i + 1, equations[i].equation);
        drawColoredText(legendText, legendX + 25, legendY + i * legendSpacing, colors[i % num_colors], labelFont);
    }
}

void drawGrid()
{
    if (!renderer)
        return;

    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);

    int minorGridSize = 10;

    for (int x = minorGridSize; x < SCREEN_WIDTH; x += minorGridSize)
    {
        if (x % 50 != 0)
        {
            SDL_RenderDrawLine(renderer, x, 0, x, SCREEN_HEIGHT);
        }
    }

    for (int y = minorGridSize; y < SCREEN_HEIGHT; y += minorGridSize)
    {
        if (y % 50 != 0)
        {
            SDL_RenderDrawLine(renderer, 0, y, SCREEN_WIDTH, y);
        }
    }

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

    int majorGridSize = 50;
    for (int x = majorGridSize; x < SCREEN_WIDTH; x += majorGridSize)
    {
        SDL_RenderDrawLine(renderer, x, 0, x, SCREEN_HEIGHT);
    }
    for (int y = majorGridSize; y < SCREEN_HEIGHT; y += majorGridSize)
    {
        SDL_RenderDrawLine(renderer, 0, y, SCREEN_WIDTH, y);
    }
}

void drawAxesLabels()
{
    if (!renderer)
        return;

    SDL_Color black = {0, 0, 0, 255};
    drawColoredText("X", SCREEN_WIDTH - 15, SCREEN_HEIGHT / 2 - 20, black, labelFont);

    drawColoredText("Y", SCREEN_WIDTH / 2 + 10, 10, black, labelFont);

    char title[50];
    sprintf(title, "Function Grapher (%.1f to %.1f)", xMin, xMax);
    drawColoredText(title, SCREEN_WIDTH / 2 - 120, 10, black, labelFont);
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

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    drawGrid();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = -1; i <= 1; i++)
    {
        SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2 + i, SCREEN_WIDTH, SCREEN_HEIGHT / 2 + i);
    }

    for (int i = -1; i <= 1; i++)
    {
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 + i, 0, SCREEN_WIDTH / 2 + i, SCREEN_HEIGHT);
    }

    int majorTickSize = 50;
    for (int i = 0; i < SCREEN_WIDTH; i += majorTickSize)
    {
        SDL_RenderDrawLine(renderer, i, SCREEN_HEIGHT / 2 - 5, i, SCREEN_HEIGHT / 2 + 5);
        if (i != SCREEN_WIDTH / 2)
        {
            char text[20];
            double xVal = xMin + (xMax - xMin) * (i / (double)SCREEN_WIDTH);
            sprintf(text, "%.1f", xVal);
            drawText(text, i - 10, SCREEN_HEIGHT / 2 + 10);
        }
    }

    for (int i = 0; i < SCREEN_HEIGHT; i += majorTickSize)
    {
        SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2 - 5, i, SCREEN_WIDTH / 2 + 5, i);
        if (i != SCREEN_HEIGHT / 2)
        {
            char text[20];
            double yVal = (SCREEN_HEIGHT / 2 - i) * (yMax - yMin) / SCREEN_HEIGHT;
            sprintf(text, "%.1f", yVal);
            drawText(text, SCREEN_WIDTH / 2 + 10, i - 5);
        }
    }

    drawAxesLabels();

    for (int i = 0; i < numOfEquations; i++)
    {
        if (!equations[i].equation)
            continue;

        SDL_SetRenderDrawColor(renderer, colors[i % num_colors].r, colors[i % num_colors].g, colors[i % num_colors].b, colors[i % num_colors].a);

        int numSamples = SCREEN_WIDTH * 10;

        double prevY = NAN;
        int prevScreenX = -1;
        int prevScreenY = -1;
        bool drawing = false;

        for (int j = 0; j < numSamples; j++)
        {
            double x_val = xMin + (xMax - xMin) * (j / (double)numSamples);
            double y_val = evaluateExpression(equations[i].equation, x_val);

            int screenX = (int)(j * SCREEN_WIDTH / numSamples);
            int screenY;

            if (isnan(y_val) || isinf(y_val) || y_val > yMax * 1.5 || y_val < yMin * 1.5)
            {
                drawing = false;
                continue;
            }
            screenY = (int)(-y_val * SCREEN_HEIGHT / (yMax - yMin) + SCREEN_HEIGHT / 2);

            if (screenY >= 0 && screenY < SCREEN_HEIGHT)
            {
                if (!drawing)
                {
                    drawing = true;
                }
                else
                {
                    double rate = fabs((y_val - prevY) / (xMax - xMin) * numSamples / SCREEN_WIDTH);
                    int threshold = 50 + (int)(rate * 5);
                    if (threshold > SCREEN_HEIGHT / 3)
                        threshold = SCREEN_HEIGHT / 3;

                    if (abs(screenY - prevScreenY) < threshold)
                    {
                        SDL_RenderDrawLine(renderer, prevScreenX, prevScreenY, screenX, screenY);
                    }
                    else
                    {
                        SDL_Rect pointRect = {screenX - 1, screenY - 1, 3, 3};
                        SDL_RenderFillRect(renderer, &pointRect);
                    }
                }

                prevY = y_val;
                prevScreenX = screenX;
                prevScreenY = screenY;
            }
            else
            {

                drawing = false;
            }
        }
    }

    drawLegend(equations, numOfEquations);

    SDL_RenderPresent(renderer);
}

void updateGraphWindow()
{
    if (windowOpen)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                closeGraphWindow();
                exit(0);
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    closeGraphWindow();
                    exit(0);
                }
            }
        }

        SDL_Delay(10);
    }
}

void changeXRange()
{
    printf("Enter the range for x-axis (e.g., -10 10): ");
    scanf("%lf %lf", &xMin, &xMax);
    getchar();

    if (xMin >= xMax)
    {
        printf("Invalid range! Setting default range (-10 to 10).\n");
        xMin = -10;
        xMax = 10;
    }

    double rangeRatio = SCREEN_HEIGHT / (double)SCREEN_WIDTH;
    double xRange = xMax - xMin;
    yMin = -(xRange * rangeRatio) / 2;
    yMax = (xRange * rangeRatio) / 2;

    printf("Y range automatically set to [%.1f, %.1f] for proper scaling\n", yMin, yMax);
    printf("Press enter to continue\n");
    while (getchar() != '\n')
        ;

    if (numOfEquations > 0)
    {
        drawGraph(equations, numOfEquations);
    }
}

bool validateEquation(char *equation)
{
    if (!equation || strlen(equation) == 0)
    {
        return false;
    }

    int validPoints = 0;
    int testPoints = 5;

    for (int i = 0; i < testPoints; i++)
    {
        double testX = xMin + (i * (xMax - xMin) / (testPoints - 1));
        double testY = evaluateExpression(equation, testX);

        if (!isnan(testY) && !isinf(testY))
        {
            validPoints++;
        }
    }

    return validPoints > 0;
}

void addEquation(char *input)
{
    if (strlen(input) == 0)
    {
        printf("Empty equation, please try again\n");
        return;
    }

    if (!validateEquation(input))
    {
        printf("Warning: Equation may not be valid in the current range.\n");
        printf("Do you still want to add it? (y/n): ");
        char response[10];
        getStrInput(response);

        if (response[0] != 'y' && response[0] != 'Y')
        {
            return;
        }
    }

    if (numOfEquations < num_colors)
    {
        Equation *newEquations = (Equation *)realloc(equations, (numOfEquations + 1) * sizeof(Equation));
        if (newEquations == NULL)
        {
            printf("Memory allocation error! Cannot add equation.\n");
            return;
        }

        equations = newEquations;
        equations[numOfEquations].equation = (char *)malloc(strlen(input) + 1);
        if (equations[numOfEquations].equation == NULL)
        {
            printf("Memory allocation error! Cannot add equation.\n");
            return;
        }

        strcpy(equations[numOfEquations].equation, input);
        equations[numOfEquations].color = numOfEquations;
        numOfEquations++;

        drawGraph(equations, numOfEquations);
    }
    else
    {
        printf("Maximum number of equations reached (%d)\n", num_colors);
    }
}

int plot()
{
    drawTitle(3);

    if (SDL_WasInit(SDL_INIT_VIDEO) == 0)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
            return -1;
        }
    }

    if (TTF_WasInit() == 0)
    {
        if (TTF_Init() == -1)
        {
            printf("TTF could not initialize! TTF_Error: %s\n", TTF_GetError());
            return -1;
        }
    }

    const char *fontPaths[] = {
        "/usr/share/fonts/truetype/msttcorefonts/Arial.ttf",
        "/usr/share/fonts/TTF/Arial.ttf",
        "Arial.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"};

    font = NULL;
    int fontCount = sizeof(fontPaths) / sizeof(fontPaths[0]);

    for (int i = 0; i < fontCount && font == NULL; i++)
    {
        font = TTF_OpenFont(fontPaths[i], 12);
    }

    if (font == NULL)
    {
        printf("Warning: Failed to load font! TTF_Error: %s\n", TTF_GetError());
        printf("Continuing with default rendering...\n");
    }

    labelFont = NULL;
    for (int i = 0; i < fontCount && labelFont == NULL; i++)
    {
        labelFont = TTF_OpenFont(fontPaths[i], 14);
    }

    if (labelFont == NULL)
    {
        labelFont = font;
    }

    if (!windowOpen && !createGraphWindow())
    {
        return -1;
    }

    changeXRange();

    char input[256];
    bool continueAdding = true;

    while (continueAdding)
    {
        printf("Enter equation Y%d = (or 'done' to return): ", numOfEquations + 1);
        getStrInput(input);
        checkInput(input);

        if (strcmp(input, "done") == 0 || strcmp(input, "exit") == 0 ||
            strcmp(input, "quit") == 0 || strcmp(input, "q") == 0)
        {
            continueAdding = false;
            break;
        }

        addEquation(input);

        updateGraphWindow();
    }

    return 0;
}

void clearGraph()
{
    if (windowOpen)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
}

void clearAllGraph()
{
    for (int i = 0; i < numOfEquations; i++)
    {
        if (equations[i].equation)
        {
            free(equations[i].equation);
            equations[i].equation = NULL;
        }
    }

    if (equations)
    {
        free(equations);
        equations = NULL;
    }

    numOfEquations = 0;

    if (windowOpen)
    {
        clearGraph();
    }

    printf("All equations cleared.\n");
}

void clearAGraph()
{
    if (numOfEquations == 0)
    {
        printf("No equations to clear.\n");
        return;
    }

    printf("Current equations:\n");
    for (int i = 0; i < numOfEquations; i++)
    {
        printf("%d. Y%d = %s\n", i + 1, i + 1, equations[i].equation);
    }

    printf("Enter the equation number to clear (1-%d): ", numOfEquations);
    char eqNum[10];
    getStrInput(eqNum);
    checkInput(eqNum);
    int eqNumInt = atoi(eqNum);

    if (eqNumInt < 1 || eqNumInt > numOfEquations)
    {
        printf("Invalid equation number\n");
        return;
    }

    free(equations[eqNumInt - 1].equation);

    for (int i = eqNumInt - 1; i < numOfEquations - 1; i++)
    {
        equations[i] = equations[i + 1];
    }

    numOfEquations--;

    if (numOfEquations > 0)
    {
        Equation *newEquations = (Equation *)realloc(equations, numOfEquations * sizeof(Equation));
        if (newEquations != NULL)
        {
            equations = newEquations;
        }

        drawGraph(equations, numOfEquations);
    }
    else
    {
        free(equations);
        equations = NULL;
        clearGraph();
    }

    printf("Equation cleared successfully.\n");
}

void drawALinearEquation(double m, double c)
{
    if (!windowOpen)
    {
        if (!createGraphWindow())
        {
            printf("Failed to initialize graph window!\n");
            return;
        }
    }

    if (numOfEquations >= num_colors)
    {
        printf("Maximum number of equations reached (%d)\n", num_colors);
        return;
    }

    char equation[256];
    if (c >= 0)
    {
        snprintf(equation, sizeof(equation), "%.2fx + %.2f", m, c);
    }
    else
    {
        snprintf(equation, sizeof(equation), "%.2fx - %.2f", m, -c);
    }

    if (!validateEquation(equation))
    {
        printf("Warning: Generated linear equation may not be valid in current range\n");
        return;
    }

    Equation *newEquations = (Equation *)realloc(equations, (numOfEquations + 1) * sizeof(Equation));
    if (newEquations == NULL)
    {
        printf("Memory allocation error! Cannot add linear equation.\n");
        return;
    }
    equations = newEquations;

    equations[numOfEquations].equation = (char *)malloc(strlen(equation) + 1);
    if (equations[numOfEquations].equation == NULL)
    {
        printf("Memory allocation error! Cannot add linear equation.\n");
        return;
    }

    strcpy(equations[numOfEquations].equation, equation);
    equations[numOfEquations].color = numOfEquations;
    numOfEquations++;

    drawGraph(equations, numOfEquations);
}