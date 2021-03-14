// Board structure
struct curBoard
{
    int board[3][3];
};

typedef struct curBoard CURBOARD; 

// Create a new board
CURBOARD *newBoard(int board[3][3]);

// Delete an existing board
void deleteBoard(CURBOARD *s);
