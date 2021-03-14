#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "AI.h"
#include "boardList.h"

// This function prints the board
void print_fun(int board[3][3],char player1_char,char player2_char,char player1_color, char player2_color)
{
    // start with row
    for(int i=0;i<3;i++)
	{
        // print out vertical legend
		if(i==0)
			printf("C ");
		if(i==1)
			printf("B ");
		if(i==2)
			printf("A ");
	
        // find corresponding column    
		for(int j=0;j<3;j++)
		{
			if(board[i][j]==0) // empty space
				printf(" ");
			else if (board[i][j]==1) // player 1
			{
				if (player1_color== 'r')
				{
					printf("\x1b[31m%c\x1b[0m",player1_char); //Red
				}
				else if (player1_color== 'g')
				{
					printf("\x1b[32m%c\x1b[0m",player1_char); //Green
				}
				else if (player1_color== 'y')
				{
					printf("\x1b[33m%c\x1b[0m",player1_char); // Yellow
				}
				else if (player1_color== 'b')
				{
					printf("\x1b[34m%c\x1b[0m",player1_char); // Blue
				}
				else
				{
					printf("%c\x1b[0m",player1_char); // Default color (theme dependent)
				}
			}
			else if (board[i][j]==2) // player 2
			{
				if (player2_color== 'r')
				{
					printf("\x1b[31m%c\x1b[0m",player2_char); //Red
				}
				else if (player2_color== 'g')
				{
					printf("\x1b[32m%c\x1b[0m",player2_char); //Green
				}
				else if (player2_color== 'y')
				{
					printf("\x1b[33m%c\x1b[0m",player2_char); // Yellow
				}
				else if (player2_color== 'b')
				{
					printf("\x1b[34m%c\x1b[0m",player2_char); // Blue
				}
				else
				{
					printf("%c\x1b[0m",player2_char); // Default color (theme dependent)
				}
			}
				
			// print out lines in between columns 
            if(j!=2)
				printf("|");
		}
		if(i!=2) // print out lines between rows
			printf("\n  -----\n");
		else if(i==2) // prints out horizontal legend
			printf("\n  1 2 3\n");
	}
}

//This function checks if there is empty place in board.
int is_there_empty_cell(int board[3][3])
{
	int count=0;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
				if(board[i][j]==0)
					count++;	
		}
	}
	if (count!=0)
		return 1; // we have empty cell
	else
		return 0; // we do not have empty cell
}

// win condition
int IsWin(int board[3][3])
{
	
	int win_flag=0;
	if(((board[0][0]==1)&&(board[1][0]==1)&&(board[2][0]==1))||
		((board[0][1]==1)&&(board[1][1]==1)&&(board[2][1]==1))||
		((board[0][2]==1)&&(board[1][2]==1)&&(board[2][2]==1))||
		((board[0][0]==1)&&(board[0][1]==1)&&(board[0][2]==1))||
		((board[1][0]==1)&&(board[1][1]==1)&&(board[1][2]==1))||
		((board[2][0]==1)&&(board[2][1]==1)&&(board[2][2]==1))||
		((board[0][0]==1)&&(board[1][1]==1)&&(board[2][2]==1))||
		((board[0][2]==1)&&(board[1][1]==1)&&(board[2][0]==1)))
		{
			win_flag =1;
		}
	
	else if(((board[0][0]==2)&&(board[1][0]==2)&&(board[2][0]==2))||
				((board[0][1]==2)&&(board[1][1]==2)&&(board[2][1]==2))||
				((board[0][2]==2)&&(board[1][2]==2)&&(board[2][2]==2))||
				((board[0][0]==2)&&(board[0][1]==2)&&(board[0][2]==2))||
				((board[1][0]==2)&&(board[1][1]==2)&&(board[1][2]==2))||
				((board[2][0]==2)&&(board[2][1]==2)&&(board[2][2]==2))||
				((board[0][0]==2)&&(board[1][1]==2)&&(board[2][2]==2))||
				((board[0][2]==2)&&(board[1][1]==2)&&(board[2][0]==2)))
				{
					win_flag =2;
				}

	return win_flag;		
}

// enters int 1 or 2 in desired position (Human)
void entered_one_char(int board [3][3],int player_num)
{
	int valid_entered = 0;
	int c;
	int r;
	while(valid_entered == 0)
	{
		char letters_num[2];
		c=0;
		r=0;
		scanf("%s",letters_num);
		
		if (letters_num[0]=='A')
		{
			r=2;
		}
		else if(letters_num[0]=='B')
		{
			r=1;
		}
		else if(letters_num[0]=='C')
		{
			r=0;
		}
		
		if (letters_num[1]=='1')
		{
			c=0;
		}
		else if(letters_num[1]=='2')
		{
			c=1;
		}
		else if(letters_num[1]=='3')
		{
			c=2;
		}

		if (board[r][c] == 0)
		{
			valid_entered = 1;
		}
		else
		{
			printf("The entered position is not available! Please try again...\n");
		}
	}
	board [r][c]=player_num; 
}

// enters int 1 or 2 in desired position (modified to work for Human vs. AI)
void ai_entered_one_char(int board [3][3],int player_num,int takeback,char letters_num[2])
{
	int valid_entered = 0;
	int c;
	int r;
	while(valid_entered == 0)
	{
		c=0;
		r=0;
		if (letters_num[0]=='A')
		{
			r=2;
		}
		else if(letters_num[0]=='B')
		{
			r=1;
		}
		else if(letters_num[0]=='C')
		{
			r=0;
		}
		
		if (letters_num[1]=='1')
		{
			c=0;
		}
		else if(letters_num[1]=='2')
		{
			c=1;
		}
		else if(letters_num[1]=='3')
		{
			c=2;
		}

		if (board[r][c] == 0 || (board[r][c] == 1 && takeback == 2))
		{
			valid_entered = 1;
		}
		else
		{
			printf("The entered position is not available! Please try again...\n");
            scanf("%s", letters_num);
		}
	}
    if (takeback == 2)
        board [r][c]=0;
    else
	    board [r][c]=player_num; 
}

// Handle a Human v. Human game
// *Note: the code that is commented out indicates where the linked list functions would be if I was able to get them to work
void HumanVsHuman(int board[3][3],char player1_char,char player2_char,char player1_color,char player2_color)
{
    //CURBOARD *s = NULL;
    //NLIST *l = NULL;
	printf("Human v. Human game started\n");
	print_fun(board,player1_char,player2_char,player1_color,player2_color);
	int tie=1;
    //l = newNodeList();
	while((is_there_empty_cell(board)))
	{
		printf("Player 1, please choose your move:");
		entered_one_char(board,1);
		print_fun(board,player1_char,player2_char,player1_color,player2_color);
        //s = newBoard(board);
        //addNode(l,s);
		int win_flag = IsWin(board);
		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("Player 2 wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
		else if (is_there_empty_cell(board)==0)
			break;
	
		printf("Player 2, please choose your move:");
		entered_one_char(board,2);
		print_fun(board,player1_char,player2_char,player1_color,player2_color);
		//s = newBoard(board);
        //addNode(l,s);
        win_flag = IsWin(board);
		if(win_flag != 0)
		{
			if (win_flag == 1)
			{
				printf("Player 1 wins! Game Over!\n\n");
			}
			else if (win_flag == 2)
			{
				printf("Player 2 wins! Game Over!\n\n");
			}
			tie=0;
			break;
		}
	}
	if (tie==1)
		printf("The game is a tie!\n");
    CreateSaveReplay(IsWin(board), player1_char, player2_char, player1_color, player2_color, 0);
}

// Handle a Human v. AI game
void HumanVsAI(int board[3][3], char player1_char, char player2_char, char player1_color, char player2_color)
{
    int select=0;
    while (select==0)
    {
        printf("1. Level 1 - Inky\n");
	    printf("2. Level 2 - Blinky\n");
	    printf("3. Level 3 - Pinky\n");
        printf("4. Back to main menu\n");
	    printf("Choose Option: ");
	    scanf("%d",&select);
	    getchar();
        switch(select)
        {
            case 1:
                Human_Vs_Inky(board,player1_char,player2_char,player1_color,player2_color);
                break;
            case 2:
                Human_Vs_Blinky(board,player1_char,player2_char,player1_color,player2_color);
                break;
            case 3:
                Human_Vs_Pinky(board,player1_char,player2_char,player1_color,player2_color);
                break;
            case 4:
                printf("Heading back to main menu...\n");
                select=1;
                break;
            }	
    }
}

// Create a save replay text file
void CreateSaveReplay(int win_flag, char player1_char, char player2_char, char player1_color, char player2_color, int whoplayer2)
{
    int option;
    printf("1. Create a save replay text file\n");
    printf("2. Back to main menu\n");
    printf("Choose option: ");
    scanf("%d", &option);
    if (option == 1)
    {
        int hours, minutes, day, month, year;
        char name[20];
        char ftype[] = ".txt";
        printf("Enter a name for the save replay text file (up to 20 characters): ");
        scanf("%s", name);
        strcat(name, ftype);
        FILE *text;
        text = fopen(name, "w");
        fprintf(text, "#TicTacWowWeeWow\n");
        fprintf(text, "Version: v2.0\n");
        fprintf(text, "Filename: %s\n", name);
        
        // Pull current date and time
        time_t now;
        time(&now);
        struct tm *local = localtime(&now);
        hours = local->tm_hour;
        minutes = local->tm_min;
        day = local->tm_mday;
        month = local->tm_mon + 1;
        year = local->tm_year + 1900;
        if (hours < 12)
            fprintf(text, "Date: %d/%02d/%02d %02d:%02dam\n\n", year, month, day, hours, minutes);
        else
            fprintf(text, "Date: %d/%02d/%02d %02d:%02dpm\n\n", year, month, day, hours - 12, minutes);

        fprintf(text, "#Settings\n");
        // Player 1 is always human
        if (player1_color == 'r')
            fprintf(text, "Player 1 (Human): '%c', 'Red'\n", player1_char);
        else if (player1_color == 'g')
            fprintf(text, "Player 1 (Human): '%c', 'Green'\n", player1_char);
        else if (player1_color == 'y')
            fprintf(text, "Player 1 (Human): '%c', 'Yellow'\n", player1_char);
        else if (player1_color == 'B')
            fprintf(text, "Player 1 (Human): '%c', 'Blue'\n", player1_char);
        else
            fprintf(text, "Player 1 (Human): '%c', 'Default'\n", player1_char);

        // Player 2 could be human or one of the three AIs
        if (player2_color == 'r' && whoplayer2 == 0)
            fprintf(text, "Player 2 (Human): '%c', 'Red'\n\n", player2_char);
        else if (player2_color == 'g' && whoplayer2 == 0)
            fprintf(text, "Player 2 (Human): '%c', 'Green'\n\n", player2_char);
        else if (player2_color == 'y' && whoplayer2 == 0)
            fprintf(text, "Player 2 (Human): '%c', 'Yellow'\n\n", player2_char);
        else if (player2_color == 'b' && whoplayer2 == 0)
            fprintf(text, "Player 2 (Human): '%c', 'Blue'\n\n", player2_char);
        else if (player2_color == 'd' && whoplayer2 == 0)
            fprintf(text, "Player 2 (Human): '%c', 'Default'\n\n", player2_char);
        else if (player2_color == 'r' && whoplayer2 == 1)
            fprintf(text, "Player 2 (AI - Inky): '%c', 'Red'\n\n", player2_char);
        else if (player2_color == 'g' && whoplayer2 == 1)
            fprintf(text, "Player 2 (AI - Inky): '%c', 'Green'\n\n", player2_char);
        else if (player2_color == 'y' && whoplayer2 == 1)
            fprintf(text, "Player 2 (AI - Inky): '%c', 'Yellow'\n\n", player2_char);
        else if (player2_color == 'b' && whoplayer2 == 1)
            fprintf(text, "Player 2 (AI - Inky): '%c', 'Blue'\n\n", player2_char);
        else if (player2_color == 'd' && whoplayer2 == 1)
            fprintf(text, "Player 2 (AI - Inky): '%c', 'Default'\n\n", player2_char);
        else if (player2_color == 'r' && whoplayer2 == 2)
            fprintf(text, "Player 2 (AI - Blinky): '%c', 'Red'\n\n", player2_char);
        else if (player2_color == 'g' && whoplayer2 == 2)
            fprintf(text, "Player 2 (AI - Blinky): '%c', 'Green'\n\n", player2_char);
        else if (player2_color == 'y' && whoplayer2 == 2)
            fprintf(text, "Player 2 (AI - Blinky): '%c', 'Yellow'\n\n", player2_char);
        else if (player2_color == 'b' && whoplayer2 == 2)
            fprintf(text, "Player 2 (AI - Blinky): '%c', 'Blue'\n\n", player2_char);
        else if (player2_color == 'd' && whoplayer2 == 2)
            fprintf(text, "Player 2 (AI - Blinky): '%c', 'Default'\n\n", player2_char);
        else if (player2_color == 'r' && whoplayer2 == 3)
            fprintf(text, "Player 2 (AI - Pinky): '%c', 'Red'\n\n", player2_char);
        else if (player2_color == 'g' && whoplayer2 == 3)
            fprintf(text, "Player 2 (AI - Pinky): '%c', 'Green'\n\n", player2_char);
        else if (player2_color == 'y' && whoplayer2 == 3)
            fprintf(text, "Player 2 (AI - Pinky): '%c', 'Yellow'\n\n", player2_char);
        else if (player2_color == 'b' && whoplayer2 == 3)
            fprintf(text, "Player 2 (AI - Pinky): '%c', 'Blue'\n\n", player2_char);
        else if (player2_color == 'd' && whoplayer2 == 3)
            fprintf(text, "Player 2 (AI - Pinky): '%c', 'Default'\n\n", player2_char);

        fprintf(text, "#Winner\n");
        fprintf(text, "Player %d\n\n", win_flag);
        fprintf(text, "#EOF");
        fclose(text);
        printf("%s was stored successfully.\n", name);
    }
} 
