#include <stdio.h>
#include "game.h"
#include "AI.h"

// Handle a Human v. Inky game
void Human_Vs_Inky(int board[3][3],char player1_char,char player2_char,char player1_color,char player2_color) // Human is always player1 and Inky is player2
{
	printf("Human v. Inky game started\n");
	print_fun(board,player1_char,player2_char,player1_color,player2_color);
	int tie=1;
    int takeback=1;
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
				printf("Inky wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;

		printf("Inky is choosing its move:\n");
        int foundMove = 0;
        // AI chooses next available move
		for (int i=0; i<3; i++)
		{
			for (int j=0; j<3; j++)
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
				printf("Inky wins! Game Over!\n\n");
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
    CreateSaveReplay(IsWin(board), player1_char, player2_char, player1_color, player2_color, 1);
}
