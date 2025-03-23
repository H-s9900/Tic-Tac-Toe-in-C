#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define BOARD_SIZE 3
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 650
#define CELL_SIZE (SCREEN_WIDTH / BOARD_SIZE)
#define X_PLAYER 1
#define O_PLAYER -1

typedef enum
{
    MENU,
    GAME,
    SCOREBOARD,
    SETTINGS,
    MODE_SELECTION
} GameScreen;
GameScreen currentScreen = MENU;

typedef struct
{
    int player;
    int computer;
    int draw;
} Score;

Score score = {0, 0, 0};
int board[BOARD_SIZE][BOARD_SIZE] = {0};
int currentPlayer;
bool gameOver = false;
int winner = 0;
bool scoreUpdated = false;
bool twoPlayerMode = false;

void DrawBoard();
void DrawSymbols();
void HandleClick();
int CheckWinner();
void ResetGame();
void ComputerMove();
void DrawScores();
void DrawMainMenu();
void DrawScoreboard();
void DrawSettings();
void DrawWinningLine();
void DrawModeSelection();

int main()
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tic-Tac-Toe");
    SetTargetFPS(60);
    srand(time(NULL));
    ResetGame();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
        case MENU:
            DrawMainMenu();
            break;
        case MODE_SELECTION:
            DrawModeSelection();
            break;
        case GAME:
            if (!gameOver && !twoPlayerMode && currentPlayer == O_PLAYER)
            {
                ComputerMove();
                winner = CheckWinner();
                if (winner != 0)
                    gameOver = true;
                currentPlayer = X_PLAYER;
            }
            DrawBoard();
            DrawSymbols();
            DrawScores();
            DrawWinningLine();

            if (gameOver)
            {
                if (!scoreUpdated)
                {
                    if (winner == X_PLAYER)
                    {
                        score.player++;
                    }
                    else if (winner == O_PLAYER)
                    {
                        if (twoPlayerMode)
                            score.player++; // Assigning score to Player O instead of Computer
                        else
                            score.computer++;
                    }
                    else
                    {
                        score.draw++;
                    }

                    scoreUpdated = true;
                }

                const char *resultText;
                if (winner == X_PLAYER)
                    resultText = "Player X Wins!";
                else if (winner == O_PLAYER)
                    resultText = twoPlayerMode ? "Player O Wins!" : "Computer Wins!";
                else
                    resultText = "It's a Draw!";

                DrawText(resultText, SCREEN_WIDTH / 2 - MeasureText(resultText, 30) / 2, SCREEN_HEIGHT / 2, 30, BLACK);
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                HandleClick();
            break;
        case SCOREBOARD:
            DrawScoreboard();
            break;
        case SETTINGS:
            DrawSettings();
            break;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

Vector2 lineStart = {0, 0};
Vector2 lineEnd = {0, 0};

void DrawMainMenu()
{
    DrawText("Tic-Tac-Toe", 200, 100, 40, BLACK);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        if (mouse.y > 200 && mouse.y < 250)
            currentScreen = MODE_SELECTION;
        if (mouse.y > 300 && mouse.y < 350)
            currentScreen = SCOREBOARD;
        if (mouse.y > 400 && mouse.y < 450)
            currentScreen = SETTINGS;
        if (mouse.y > 500 && mouse.y < 550)
            CloseWindow();
    }
    DrawRectangle(200, 200, 200, 50, LIGHTGRAY);
    DrawText("Play", 270, 215, 20, BLACK);
    DrawRectangle(200, 300, 200, 50, LIGHTGRAY);
    DrawText("Scoreboard", 220, 315, 20, BLACK);
    DrawRectangle(200, 400, 200, 50, LIGHTGRAY);
    DrawText("Settings", 220, 415, 20, BLACK);
    DrawRectangle(200, 500, 200, 50, LIGHTGRAY);
    DrawText("Exit", 270, 515, 20, BLACK);
}

void DrawModeSelection()
{
    DrawText("Select Mode", 220, 100, 40, BLACK);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        if (mouse.y > 200 && mouse.y < 250)
        {
            twoPlayerMode = false;
            currentScreen = GAME;
            ResetGame();
        }
        if (mouse.y > 300 && mouse.y < 350)
        {
            twoPlayerMode = true;
            currentScreen = GAME;
            ResetGame();
        }
    }
    DrawRectangle(200, 200, 200, 50, LIGHTGRAY);
    DrawText("Single Player", 220, 215, 20, BLACK);
    DrawRectangle(200, 300, 200, 50, LIGHTGRAY);
    DrawText("Two Players", 220, 315, 20, BLACK);
}

void DrawScoreboard()
{
    DrawText("Scoreboard", 220, 100, 40, BLACK);
    char scoreText[100];
    sprintf(scoreText, "Player X Wins: %d", score.player);
    DrawText(scoreText, 220, 200, 30, BLACK);
    if (twoPlayerMode)
        sprintf(scoreText, "Player O Wins: %d", score.computer);
    else
        sprintf(scoreText, "Computer Wins: %d", score.computer);
    DrawText(scoreText, 220, 250, 30, BLACK);

    sprintf(scoreText, "Draws: %d", score.draw);
    DrawText(scoreText, 220, 300, 30, BLACK);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        currentScreen = MENU;
}

void DrawSettings()
{
    DrawText("Settings (Coming Soon)", 150, 200, 30, BLACK);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        currentScreen = MENU;
}

void ResetGame()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = 0;
        }
    }
    currentPlayer = X_PLAYER;
    gameOver = false;
    winner = 0;
    scoreUpdated = false;
    lineStart = (Vector2){0, 0};
    lineEnd = (Vector2){0, 0};
}
void DrawWinningLine()
{
    if (gameOver && winner != 0)
    {
        DrawLineEx(lineStart, lineEnd, 5, GREEN);
    }
}

void DrawBoard()
{
    for (int i = 1; i < BOARD_SIZE; i++)
    {
        DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, SCREEN_WIDTH, BLACK);
        DrawLine(0, i * CELL_SIZE, SCREEN_WIDTH, i * CELL_SIZE, BLACK);
    }
}

void DrawSymbols()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == X_PLAYER)
            {
                DrawText("X", j * CELL_SIZE + CELL_SIZE / 3, i * CELL_SIZE + CELL_SIZE / 4, 50, RED);
            }
            else if (board[i][j] == O_PLAYER)
            {
                DrawText("O", j * CELL_SIZE + CELL_SIZE / 3, i * CELL_SIZE + CELL_SIZE / 4, 50, BLUE);
            }
        }
    }
}

void DrawScores()
{
    char scoreText[50];
    sprintf(scoreText, "Player: %d | Computer: %d | Draws: %d", score.player, score.computer, score.draw);
    DrawText(scoreText, 10, SCREEN_HEIGHT - 40, 20, DARKGRAY);
}

void ComputerMove()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = O_PLAYER;
                return;
            }
        }
    }
}

int CheckWinner()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        // Check rows
        if (board[i][0] != 0 && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            lineStart = (Vector2){0, i * CELL_SIZE + CELL_SIZE / 2};
            lineEnd = (Vector2){SCREEN_WIDTH, i * CELL_SIZE + CELL_SIZE / 2};
            return board[i][0];
        }

        // Check columns
        if (board[0][i] != 0 && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            lineStart = (Vector2){i * CELL_SIZE + CELL_SIZE / 2, 0};
            lineEnd = (Vector2){i * CELL_SIZE + CELL_SIZE / 2, SCREEN_WIDTH};
            return board[0][i];
        }
    }

    // Check main diagonal
    if (board[0][0] != 0 && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        lineStart = (Vector2){0, 0};
        lineEnd = (Vector2){SCREEN_WIDTH, SCREEN_WIDTH};
        return board[0][0];
    }

    // Check anti-diagonal
    if (board[0][2] != 0 && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        lineStart = (Vector2){SCREEN_WIDTH, 0};
        lineEnd = (Vector2){0, SCREEN_WIDTH};
        return board[0][2];
    }

    bool isDraw = true;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 0)
            { // If there is an empty cell, it's not a draw
                isDraw = false;
                break;
            }
        }
    }

    if (isDraw)
        return 2; // Return 2 to indicate a draw
    return 0;     // No winner yet
}

void HandleClick()
{
    Vector2 mouse = GetMousePosition();

    // If game is over, check for a click in the bottom area to go back to menu
    if (gameOver)
    {
        if (mouse.y > SCREEN_HEIGHT - 50)
        { // Click detected in bottom area
            currentScreen = MENU;
            return;
        }
        else
        {
            ResetGame(); // Otherwise, reset game
            return;
        }
    }

    int row = mouse.y / CELL_SIZE;
    int col = mouse.x / CELL_SIZE;

    if (board[row][col] == 0)
    {
        board[row][col] = currentPlayer;
        winner = CheckWinner();
        gameOver = (winner != 0);
        if (!twoPlayerMode)
            currentPlayer = O_PLAYER;
        else
            currentPlayer = (currentPlayer == X_PLAYER) ? O_PLAYER : X_PLAYER;
    }
}
