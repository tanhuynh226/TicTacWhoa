/*********************************************************************/
/* TicTacWhoa.c: Assignment 5                                        */
/* Author: Tan Huynh                                                 */
/* Version: 2.0                                                      */
/*                                                                   */
/* Modifications:                                                    */
/* 03/13/21 TH  Added partial save replay support                    */
/* 03/12/21 TH  Added takeback move support                          */
/* 03/12/21 TH  Initial linked list implementation                   */
/* 03/11/21 TH  Level 2 and 3 AIs & updated settings to use struct   */
/* 03/10/21 TH  Decomposing and creating Makefile                    */
/* 01/23/21 TH  Initial version 1.0                                  */
/*********************************************************************/
#include <stdio.h>
#include "AI.h"
#include "game.h"
#include "settings.h"

// Handle Menu Options
int print_menu()
{
	int select=0;
	printf("1. Start New Game (Human v. Human)\n");
	printf("2. Start New Game (Human v. AI)\n");
	printf("3. Game Settings\n");
	printf("4. Exit Game\n");
	printf("Choose Option: ");
	scanf("%d",&select);
	getchar(); // one solution for clearing the "\n" char from the input
	return select;
}

// Main Program for Tic-Tac-Whoa (modified to use struct for player settings)
int main()
{
    // initialize game	
    struct playerSettings player1 = {'X', 'd'};
    struct playerSettings player2 = {'O', 'd'};

	printf("Welcome to Secure-Tic-Tac-Whoa!\n");
	int done=0;
	while(done==0)
	{
		int board[3][3]={{0,0,0},{0,0,0},{0,0,0}};
		int option = print_menu();
		switch(option)
		{
			case 1:
				HumanVsHuman(board,player1.pChar,player2.pChar,player1.pColor,player2.pColor);
				break;
			case 2:
                HumanVsAI(board,player1.pChar,player2.pChar,player1.pColor,player2.pColor);
				break;
			case 3:
				settings(&player1.pChar,&player2.pChar,&player1.pColor,&player2.pColor);
				break;
			case 4:
				printf("Thanks for playing. Exiting game...\n");
				done=1;
				break;
		}
		
	}
	return 0;
}

/* EOF */
