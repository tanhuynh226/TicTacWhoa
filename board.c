#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Create a new board
CURBOARD *newBoard(int board[3][3])
{
    CURBOARD *s;
    s = malloc(sizeof(CURBOARD));
    if (!s)
    {
        perror("Out of memory! Aborting...");
        exit(10);
    }
    s->board = board;
    return s;
}

// Delete existing board
void deleteBoard(CURBOARD *s)
{
    free(s);
}
