#include <stdio.h>
#include "game.h"
#include "AI.h"

// Handle a Human v. Pinky game
void Human_Vs_Pinky(int board[3][3],char player1_char,char player2_char,char player1_color,char player2_color)
{
    int i, j;
	printf("Human v. Pinky game started\n");
	print_fun(board,player1_char,player2_char,player1_color,player2_color);
	int tie=1;
    int takeback = 1;
    int a, b, c, d;
	while((is_there_empty_cell(board)))
	{
        char letters_num[2];
		printf("Player 1, please choose your move:");
        scanf("%s", letters_num);
        a = letters_num[0];
        b = letters_num[1];
		ai_entered_one_char(board,1,takeback,letters_num);
		print_fun(board,player1_char,player2_char,player1_color,player2_color);
		int win_flag = IsWin(board);
		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("Pinky wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;

		printf("Pinky is choosing its move:\n");
        int foundMove = 0;
        // Checks if there is a way for player 1 to win and blocks that position
        for (i=0; i<3; i++)
		{
			for (j=0; j<3; j++)
			{
                if (board[i][j] == 0)
                {
                    board[i][j] = 1;
                    if (IsWin(board) == 1)
                    {
                        board[i][j] = 2;
                        c = i;
                        d = j;
                        foundMove = 1;
                        break;
                    }
                    else
                        board[i][j] = 0;
                }
            }
            if(foundMove)
                break;
        }
        if (foundMove == 0)
        {
		    for (i=0; i<3; i++)
		    {
			    for (j=0; j<3; j++)
			    {
				    if (board[i][j] == 0)
				    {
                        board[i][j] = 2;
                        c = i;
                        d = j;
                        foundMove = 1;
					    break;
				    }
			    }
                if(foundMove)
                    break;
		    }
        }
		
		print_fun(board,player1_char,player2_char,player1_color,player2_color);

        printf("1. Keep going\n");
        printf("2. Take back\n");
        printf("Choose option: ");
        scanf("%d", &takeback);
        if (takeback == 2)
        {
            board[a][b] = 0;
            board[c][d] = 0;
            ai_entered_one_char(board,1,takeback,letters_num);
            print_fun(board,player1_char,player2_char,player1_color,player2_color);
        }
        takeback = 1;

		win_flag = IsWin(board);
		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("Pinky wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;
	}
	if (tie==1)
	{
		printf("The game is a tie!\n");
	}
    CreateSaveReplay(IsWin(board), player1_char, player2_char, player1_color, player2_color, 3);
}
