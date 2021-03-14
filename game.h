// This function prints the board
void print_fun(int board[3][3],char player1_char,char player2_char,char player1_color, char player2_color);

//This function checks if there is empty place in board.
int is_there_empty_cell(int board[3][3]);

// win condition
int IsWin(int board[3][3]);

// enters int 1 or 2 in desired position (Human)
void entered_one_char(int board [3][3],int player_num);

// enters int 1 or 2 in desired position (AI)
void ai_entered_one_char(int board [3][3],int player_num,int takeback,char letters_num[2]);

// Handle a Human v. Human game
void HumanVsHuman(int board[3][3],char player1_char,char player2_char,char player1_color,char player2_color);

// Handle a Human v. AI game
void HumanVsAI(int board[3][3], char player1_char, char player2_char, char player1_color, char player2_color);

// Create a save replay text file
void CreateSaveReplay(int win_flag,char player1_char, char player2_char, char player1_color, char player2_color, int whoplayer2);
