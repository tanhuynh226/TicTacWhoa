/***************************************************************/
/* TicTacWhoa.c: Assignment 1 - Childhood Game Implementation  */
/* author: Tan Huynh                                           */
/*                                                             */
/* modifications:                                              */
/* 2021/01/15   TH   Complete overhaul of colorPicker()        */
/*                   Added colorPrompt(), colorBoard()         */
/* 2021/01/13   TH   Moved postgame code to gameResult()       */
/* 2021/01/11   TH   Fixed player 2 v. AI                      */
/*                   Added colorPicker(), storeAIMove()        */
/* 2021/01/10   TH   Implemented AI()                          */
/* 2021/01/08   TH   Implemented board(), checkBoard(),        */
/*                   Added initial settings()                  */
/*                   Optimized markMove()                      */
/* 2021/01/07   TH   Initial version                           */
/*                   Added initial menu and markMove()         */
/***************************************************************/

// Header files
#include <stdio.h>
#include <stdlib.h> //for system() and exit()
#include <unistd.h> //for sleep()

// Declaring functions
void board();
void rowColumnConvert(char row, int column);
void markMove(int player, int row, int column);
void invalid();
int checkBoard();
void gameResult();
void settings();
void colorPrompt(int player);
void colorPicker(int player);
void colorBoard(int index);
void storeAIMove(int i);
void AI(int player, int row, int column);

// Declaring global variables
char game[9];
char concatGame[9][10];
int turn = 0;
int rowInt = 0;
int columnInt = 0;
char playerOne = 'X';
char playerTwo = 'O';
int status = 0;
int settingsOption = 0;
int colorsOptionP1 = 0;
int colorsOptionP2 = 0;
char AIMove[2] = {' ', ' '};

// Main function
int main()
{
    int option = 0;
    char row = ' ';
    int playerNumber = 0;
    do
    {
        system("clear");
        turn = 1;
        status = 0;
        playerNumber = 0;
        for (int i = 0; i < 9; i++) // Reset board
            game[i] = ' ';
        printf("Welcome to Secure-Tic-Tac-Whoa!");
        printf("\n1. Start New Game (Human v. Human)");
        printf("\n2. Start New Game (Human v. AI)");
        printf("\n3. Game Settings");
        printf("\n4. Exit Game\n");
        printf("\nChoose Option: ");
        scanf(" %d", &option);

        switch(option) {
            case 1:
                printf("\nHuman v. Human game started");
                do
                {
                    system("clear");
                    board();

                    printf("\n\nPlayer ");
                    if (turn == 1)
                    {
                        colorPicker(1);
                        printf("%c\x1B[0m, please choose your move: ", playerOne);
                    }
                    else
                    {
                        colorPicker(2);
                        printf("%c\x1B[0m, please choose your move: ", playerTwo);
                    }
                    
                    scanf(" %c%d", &row, &columnInt);

                    printf("\nPlayer ");
                    if (turn == 1)
                    {
                        colorPicker(1);
                        printf("%c \x1B[0mchose %c%d", playerOne, row, columnInt);
                    }
                    else
                    {
                        colorPicker(2);
                        printf("%c \x1B[0mchose %c%d", playerTwo, row, columnInt);
                    }

                    rowColumnConvert(row, columnInt);
                    markMove(playerNumber, rowInt, columnInt); 

                    status = checkBoard();
                } while (status == 0);
                board();
                gameResult();
                break;
            case 2:
                system("clear");
                printf("1. Play as player 1");
                printf("\n2. Play as player 2\n");
                printf("\nChoose option: ");
                scanf(" %d", &playerNumber);
                printf("Human v. AI game started");
                do
                {
                    if (playerNumber == 1)
                    {
                        system("clear");
                        board();
                        printf("\n\nPlayer ");
                        colorPicker(1);
                        printf("%c\x1B[0m, please choose your move: ", playerOne);  
                    }
                    else 
                    {
                        AI(playerNumber, rowInt, columnInt);
                        system("clear");
                        printf("\nPlayer ");
                        colorPicker(1);
                        printf("%c \x1B[0mchose %c%c", playerOne, AIMove[0], AIMove[1]);
                        board();
                        status = checkBoard();
                        if (status == 1)
                        {
                            if (turn == 1)
                                turn++;
                            else if (turn == 2)
                                turn--;
                            break;
                        }
                        printf("\n\nPlayer ");
                        colorPicker(2);
                        printf("%c\x1B[0m, please choose your move: ", playerTwo); 
                    }
                    scanf(" %c%d", &row, &columnInt);
                    
                    rowColumnConvert(row, columnInt);
                    markMove(playerNumber, rowInt, columnInt);

                    if (playerNumber == 1)
                    {
                        status = checkBoard();
                        if (status == 1)
                        {
                            turn++;
                            break;
                        }
                        AI(playerNumber, rowInt, columnInt);
                        printf("\nPlayer ");
                        colorPicker(2);
                        printf("%c \x1B[0mchose %c%c", playerTwo, AIMove[0], AIMove[1]);
                    }

                    status = checkBoard();
                } while (status == 0);
                board();
                gameResult();
                break;
            case 3:
                settingsOption = 0;
                do
                {
                    settings();
                } while (settingsOption != 5);               
                break;
            case 4:
                printf("\nExiting...\n\n");
                fflush(stdout);
                sleep(1);
                break;
            default:
                printf("\nInvalid option. Please try again.\n");
                sleep(1);
                break;
        }
    } while (option != 4);
    return 0; 
}

// Print board function
void board()
{
    printf("\nC ");
    colorBoard(0);
    printf("%c \x1B[0m| ", game[0]);
    colorBoard(1);
    printf("%c \x1B[0m| ", game[1]);
    colorBoard(2);
    printf("%c\x1B[0m", game[2]);
    printf("\n  ---------");
    printf("\nB ");
    colorBoard(3);
    printf("%c \x1B[0m| ", game[3]);
    colorBoard(4);
    printf("%c \x1B[0m| ", game[4]);
    colorBoard(5);
    printf("%c\x1B[0m", game[5]);
    printf("\n  ---------");
    printf("\nA ");
    colorBoard(6);
    printf("%c \x1B[0m| ", game[6]);
    colorBoard(7);
    printf("%c \x1B[0m| ", game[7]);
    colorBoard(8);
    printf("%c\x1B[0m", game[8]);
    printf("\n  1   2   3");
}

// Add color to board function
void colorBoard(int index)
{
    if (game[index] == playerOne)
        colorPicker(1);
    else if (game[index] == playerTwo)
        colorPicker(2);
}
// Convert row and column to proper array index function
void rowColumnConvert(char row, int column)
{
     if (row == 'C')
        rowInt = 0;
     else if (row == 'B')
        rowInt = 1;
     else if (row == 'A')
        rowInt = 2;
     columnInt--;
}

// Player mark move function
void markMove(int player, int row, int column)
{
    if (player == 0)
    {
        if (turn == 1 && game[3 * row + column] == ' ')
            game[3 * row + column] = playerOne;
        else if (turn == 2 && game[3 * row + column] == ' ')
            game[3 * row + column] = playerTwo;
        else
            invalid();

        if (turn == 1)
            turn++;
        else
            turn--;
    }
    else if (player == 1 && game[3 * row + column] == ' ')
        game[3 * row + column] = playerOne;
    else if (player == 2 && game[3 * row + column] == ' ')
        game[3 * row + column] = playerTwo;
    else
        invalid();
}

// Error handling function if player enters invalid move
void invalid()
{
    printf("\nError: Invalid move!");
    printf("\nExiting...\n\n");
    fflush(stdout);
    sleep(1);
    exit(0);
}

// Check board state function
int checkBoard()
{
    if (game[0] == game[1] && game[1] == game[2] && game[0] != ' ')
        return 1;
    else if (game[3] == game[4] && game[4] == game[5] && game[3] != ' ')
        return 1;
    else if (game[6] == game[7] && game[7] == game[8] && game[6] != ' ')
        return 1;
    else if (game[0] == game[3] && game[3] == game[6] && game[0] != ' ')
        return 1;
    else if (game[1] == game[4] && game[4] == game[7] && game[1] != ' ')
        return 1;
    else if (game[2] == game[5] && game[5] == game[8] && game[2] != ' ')
        return 1;
    else if (game[2] == game[4] && game[4] == game[6] && game[2] != ' ')
        return 1;
    else if (game[0] == game[4] && game[4] == game[8] && game[0] != ' ')
        return 1;
    else if (game[0] != ' ' && game[1] != ' ' && game[2] != ' ' && game[3] != ' ' && game[4] != ' ' && game[5] != ' ' && game[6] != ' ' && game[7] != ' ' && game[8] != ' ')
        return 2;
    else
        return 0; 
}

// Game result function
void gameResult()
{
    if (status == 1)
    {
        printf("\n\nPlayer ");
        if (turn == 1)
        {
            colorPicker(2);
            printf("%c \x1B[0mwins! Game over!\n", playerTwo);
        }
        else if (turn == 2)
        {
            colorPicker(1);
            printf("%c \x1B[0mwins! Game over!\n", playerOne);
        }
    }
    else if (status == 2)
        printf("\n\nDraw! Game over!\n");
    sleep(1);
    printf("\nReturning to main menu in 5 seconds...");
    fflush(stdout);
    sleep(5);
}

// Store AI move function 
void storeAIMove(int i)
{
    if (i == 0) 
    {
        AIMove[0] = 'C';
        AIMove[1] = '1';
    }
    else if (i == 1) 
    {
        AIMove[0] = 'C';
        AIMove[1] = '2';
    }
    else if (i == 2) 
    {
        AIMove[0] = 'C';
        AIMove[1] = '3';
    }
    else if (i == 3) 
    {
        AIMove[0] = 'B';
        AIMove[1] = '1';
    }
    else if (i == 4) 
    {
        AIMove[0] = 'B';
        AIMove[1] = '2';
    }
    else if (i == 5) 
    {
        AIMove[0] = 'B';
        AIMove[1] = '3';
    }
    else if (i == 6) 
    {
        AIMove[0] = 'A';
        AIMove[1] = '1';
    }
    else if (i == 7) 
    {
        AIMove[0] = 'A';
        AIMove[1] = '2';
    }
    else if (i == 8) 
    {
        AIMove[0] = 'A';
        AIMove[1] = '3';
    }
}

// AI Move function
void AI(int player, int row, int column)
{
    if (player == 1)
    {
        turn++;
        for (int i = 0; i < 9; i++) // Player 2 AI makes a move at the next empty square
        {
            if (game[i] == ' ')
            {
                game[i] = playerTwo;
                storeAIMove(i); 
                break;
            }
        }        
        turn--;
    }
    else if (player == 2)
    {
        turn--;
        for (int i = 0; i < 9; i++) // Player 1 AI makes a move at the next empty square
        {
            if (game[i] == ' ' && i != (3 * row + column))
            {
                game[i] = playerOne;
                storeAIMove(i); 
                break;
            }
        }
        turn++;
    }
}

// Settings menu function
void settings()
{
    system("clear");
    printf("1. Change player 1's character.");
    printf("\n2. Change player 1's color.");
    printf("\n3. Change player 2's character.");
    printf("\n4. Change player 2's color.");
    printf("\n5. Back to main menu.\n");
    printf("\nChoose option: ");
    scanf(" %d", &settingsOption);
    switch(settingsOption) {
        case 1:
            printf("\nWhat character should player 1 be changed to?");
            printf("\nEnter a character: ");
            scanf(" %c", &playerOne);
            printf("\nPlayer 1's character has successfully been set to ");
            colorPicker(1);
            printf("%c\x1B[0m!", playerOne);
            fflush(stdout);
            sleep(1);
            break;
        case 2:
            colorPrompt(1);
            printf("\nPlayer 1's color has successfully been set to ");
            colorPicker(1);
            printf("%c\x1B[0m!", playerOne);
            fflush(stdout);
            sleep(1);
            break;       
        case 3:
            printf("\nWhat character should player 2 be changed to?");
            printf("\nEnter a character: ");
            scanf(" %c", &playerTwo);
            printf("\nPlayer 2's character has successfully been set to ");
            colorPicker(2);
            printf("%c\x1B[0m!", playerTwo);
            fflush(stdout);
            sleep(1);
            break;
        case 4:
            colorPrompt(2);
            printf("\nPlayer 2's color has successfully been set to ");
            colorPicker(2);
            printf("%c\x1B[0m!", playerTwo);
            fflush(stdout);
            sleep(1); 
            break;
        case 5:
            printf("\nReturning to main menu...");
            fflush(stdout);
            sleep(2);
            break;
    }   
}

// Color prompt function
void colorPrompt(int player)
{
    printf("\nWhat color should player %d be changed to?\n", player);
    printf("\n1. Black");
    printf("\n2. Red");
    printf("\n3. Green");
    printf("\n4. Yellow");
    printf("\n5. Blue");
    printf("\n6. Magenta");
    printf("\n7. Cyan");
    printf("\n8. White");
    printf("\n9. Reset to terminal default\n");
    printf("\nChoose option: ");
    if (player == 1)
        scanf(" %d", &colorsOptionP1);
    else if (player == 2)
        scanf(" %d", &colorsOptionP2);
    else
        printf("Invalid option. Going back to the previous menu...\n");
    sleep(1);
}

// Color picker function
void colorPicker(int player)
{
    if (player == 1)
    {
        switch(colorsOptionP1) {
            case 1:
                printf("\x1B[30m"); 
                break;
            case 2:
                printf("\x1B[31m"); 
                break;
            case 3:
                printf("\x1B[32m"); 
                break;
            case 4:
                printf("\x1B[33m"); 
                break;
            case 5:
                printf("\x1B[34m"); 
                break;
            case 6:
                printf("\x1B[35m");
                break;
            case 7:
                printf("\x1B[36m");
                break; 
            case 8:
                printf("\x1B[37m"); 
                break;
            case 9:
                printf("\x1B[0m"); 
                break;
            default:
                break;
        } 
    }
    else if (player == 2)
    {
        switch(colorsOptionP2) {
            case 1:
                printf("\x1B[30m"); 
                break;
            case 2:
                printf("\x1B[31m"); 
                break;
            case 3:
                printf("\x1B[32m"); 
                break;
            case 4:
                printf("\x1B[33m"); 
                break;
            case 5:
                printf("\x1B[34m"); 
                break;
            case 6:
                printf("\x1B[35m");
                break;
            case 7:
                printf("\x1B[36m");
                break; 
            case 8:
                printf("\x1B[37m"); 
                break;
            case 9:
                printf("\x1B[0m"); 
                break;
            default:
                break;
        }        
    } 
}
/* EOF */
