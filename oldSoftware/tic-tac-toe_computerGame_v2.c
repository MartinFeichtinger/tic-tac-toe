/*
 * This should be the final version of the tic-tac-toe_bot.
 * Later this program will be integrated into an 8-bit microprocessor.
 * Therefore it must be as clean as possible.
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>		// for system("clear");
#include <unistd.h>		// for sleep
#include <time.h>		// for random seed

// fieldContent and currentPlayer
#define EMPTY				0
#define PLAYER1				1
#define PLAYER2				2
#define PLAYER1_VICTORY		3
#define PLAYER2_VICTORY		4

// gameMode
#define PLAYER1vsPLAYER2	1
#define PLAYER1vsBOT		2
#define BOTvsPLAYER2		3
#define BOTvsBOT			4

#define DEBUG				false

// custom datatypes and structs
typedef struct {
	uint8_t x;
	uint8_t y;
} Position;


// main function prototypes
uint8_t selectGameMode();
void clearGameBoard(uint8_t gameBoard[3][3]);
void printGameBoard(uint8_t gameBoard[3][3]);
Position getValidUserInputPos(uint8_t currentPlayer, uint8_t gameBoard[3][3]);
Position getBotInput(uint8_t currentPlayer, uint8_t turnCounter, uint8_t gameBoardCopy[3][3]);
bool checkForVictory(uint8_t player, uint8_t gameBoard[3][3]);


// sub function prototypes
uint8_t findEmptyFields(uint8_t gameBoardCopy[3][3], uint8_t emptyFields[9][2]);


/************* main ****************/		// muas ma no a cleanen standard überlegen
int main()
{
	Position pos;
	uint8_t gameBoard[3][3];	// [x][y] => [col][row]
	
	while(true)
	{
		uint8_t gameMode = selectGameMode();
		uint8_t currentPlayer = PLAYER1;
		bool victory=false;
			

		clearGameBoard(gameBoard);
		printGameBoard(gameBoard);
		
		for(int turnCounter=0; turnCounter<9; turnCounter++)
		{
			if(DEBUG) printf("currentPlayer=%d\n", currentPlayer);
			if(DEBUG) printf("turnCounter=%d\n", turnCounter);
			
			switch(gameMode)
			{
				case PLAYER1vsPLAYER2:
				{
					pos = getValidUserInputPos(currentPlayer, gameBoard);
					break;
				}
				case PLAYER1vsBOT:
				{
					if(currentPlayer == PLAYER1)
					{
						pos = getValidUserInputPos(currentPlayer, gameBoard);
					}
					else // currentPlayer == PLAYER2
					{
						pos = getBotInput(currentPlayer, turnCounter, gameBoard);
					}
					break;
				}
				case BOTvsPLAYER2:
				{
					if(currentPlayer == PLAYER1)
					{
						pos = getBotInput(currentPlayer, turnCounter, gameBoard);
					}
					else // currentPlayer == PLAYER2
					{
						pos = getValidUserInputPos(currentPlayer, gameBoard);
					}				
					break;
				}
				case BOTvsBOT:
				{
					pos = getBotInput(currentPlayer, turnCounter, gameBoard);
					break;
				}
				
			}
			
			if(DEBUG) printf("pos.x=%d, pos.y=%d\n", pos.x, pos.y);
			gameBoard[pos.x][pos.y] = currentPlayer;
			victory = checkForVictory(currentPlayer, gameBoard);
			printGameBoard(gameBoard);
			if(victory) break;
			currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1; // switch player
		}
		
		if(victory)
		{
			printf("PLAYER%d hat gewonnen!\n", currentPlayer);
		}
		else
		{
			printf("Das Spiel ist unentschieden ausgegangen!\n");
		}
		
		printf("Möchtest du noch eine Runde spielen [ja][nein]?\n");
		char input[10];
		scanf("%s", input);
		if(strcmp(input, "nein") == 0 || strcmp(input, "Nein") == 0)
		{
			break;
		}
		
		printf("\n\n");
	}
}

uint8_t selectGameMode()
{
	int userInput;
	
	printf("Grias eich und olle herzlich Willkommen zu aner wahnsigen TikTakToe-Partie!\n");
	printf("1.PLAYER1vsPLAYER2   2.PLAYER1vsBOT   3.BOTvsPLAYER   4.BOTvsBOT\n");
	
	do
	{
		printf("Wähle einen GameMode aus: [1-4]\n");
		scanf("%d", &userInput);
	}
	while(userInput>4 || userInput<1);
	
	return userInput;
}

void clearGameBoard(uint8_t gameBoard[3][3])
{
	for(int y=0; y<3; y++)
	{
		for(int x=0; x<3; x++)
		{
			gameBoard[x][y]=EMPTY;
		}
	}
}

void printGameBoard(uint8_t gameBoard[3][3])
{
	if(DEBUG==false) system("clear");
	
	for(int y=0; y<3; y++)
	{
		for(int x=0; x<3; x++)
		{
			if(!DEBUG)
			{
				if(gameBoard[x][y]==EMPTY)
				{
					printf(" ");
				}
				else if(gameBoard[x][y]==PLAYER1 || gameBoard[x][y]==PLAYER1_VICTORY)
				{
					printf("X");
				}
				else if(gameBoard[x][y]==PLAYER2 || gameBoard[x][y]==PLAYER2_VICTORY)
				{
					printf("0");
				}
			}
			else
			{
				printf("%d", gameBoard[x][y]);
			}

			
			if(x<2)
			{
				printf("|");
			}
		}
		
		printf("\n");
		
		if(y<2)
		{
			printf("-----");
			printf("\n");
		}
	}
	printf("\n");
}

Position getValidUserInputPos(uint8_t currentPlayer, uint8_t gameBoard[3][3])
{
	Position pos;
	bool validInput=false;
	
	printf("PLAYER%d wähle ein Feld aus [X-->ENTER-->Y-->ENTER]\n", currentPlayer);
	do
	{
		scanf("%hhd", &pos.x);
		scanf("%hhd", &pos.y);
		
		if(pos.x<0 || pos.x>2 || pos.y<0 || pos.y>2)
		{
			printf("Dieses Feld  befinden sich nicht mehr auf dem Spielfeld. Versuch es noch einmal...\n");
		}
		else
		{
			if(gameBoard[pos.x][pos.y] == EMPTY)
			{
				validInput=true;
			}
			else
			{
				printf("Dieses Feld ist bereits belegt. Versuch es noch einmal...\n");
			}
		}
		
	} while(!validInput);
	
	return pos;
}


Position getBotInput(uint8_t currentPlayer, uint8_t turnCounter, uint8_t gameBoard[3][3])
{	
	// the computer needs some time to think ;)
	sleep(1);

	Position pos;
	uint8_t gameBoardCopy[3][3];
	memcpy(gameBoardCopy, gameBoard, sizeof(gameBoardCopy));
	srand(time(NULL));	// set random seed
	
	
	if(turnCounter == 0)
	{
		if(DEBUG) printf("dbo: randome outer center field\n");
		// select one of the four outer center fields
		switch(rand()%4)
		{
			case 0: pos.x=0; pos.y=1;	break;
			case 1: pos.x=1; pos.y=0;	break;
			case 2: pos.x=1; pos.y=2;	break;
			case 3: pos.x=2; pos.y=1;	break;		
		}
	}
	else if(turnCounter == 1)
	{
		// select the center
		if(gameBoardCopy[1][1] == EMPTY)
		{
			if(DEBUG) printf("dbo: select center\n");
			pos.x=1; pos.y=1;
		}
		// or else one of the four corners
		else
		{
			if(DEBUG) printf("dbo: randome cornere\n");
			switch(rand()%4)
			{
				case 0: pos.x=0; pos.y=0;	break;
				case 1: pos.x=0; pos.y=2;	break;
				case 2: pos.x=2; pos.y=0;	break;
				case 3: pos.x=2; pos.y=2;	break;
			}
		}
	}
	else // all further turns
	{
		uint8_t emptyFields[9][2]; // [fields][pos]
		uint8_t numEmptyFields = findEmptyFields(gameBoardCopy, emptyFields);
		
		// check for possible win
		for(int i=0; i<numEmptyFields; i++)
		{
			gameBoardCopy[emptyFields[i][0]][emptyFields[i][1]] = currentPlayer;
			if(checkForVictory(currentPlayer, gameBoardCopy))
			{
				pos.x=emptyFields[i][0];
				pos.y=emptyFields[i][1];
				if(DEBUG) printf("dbo: possible win\n");
				return pos;
			}
			else
			{
				gameBoardCopy[emptyFields[i][0]][emptyFields[i][1]] = EMPTY;
			}
		}
		
		// check for possible loss
		uint8_t opponent = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
		for(int i=0; i<numEmptyFields; i++)
		{
			gameBoardCopy[emptyFields[i][0]][emptyFields[i][1]] = opponent;
			if(checkForVictory(opponent, gameBoardCopy))
			{
				pos.x=emptyFields[i][0];
				pos.y=emptyFields[i][1];
				if(DEBUG) printf("dbo: possible loss\n");
				return pos;
			}
			else
			{
				gameBoardCopy[emptyFields[i][0]][emptyFields[i][1]] = EMPTY;
			}
		}
		
		// else select random field
		if(DEBUG) printf("dbo: randome field\n");
		uint8_t randomNumber = rand()%(numEmptyFields);
		pos.x=emptyFields[randomNumber][0];
		pos.y=emptyFields[randomNumber][1];
	}
	
	return pos;
}

uint8_t findEmptyFields(uint8_t gameBoardCopy[3][3], uint8_t emptyFields[9][2])
{
	uint8_t numEmptyFields=0;
	for(int y=0; y<3; y++)
	{
		for(int x=0; x<3; x++)
		{
			if(gameBoardCopy[x][y] == EMPTY)
			{
				emptyFields[numEmptyFields][0] = x;
				emptyFields[numEmptyFields][1] = y;
				numEmptyFields++;
			}
		}
	}
	
	return numEmptyFields;
}


bool checkForVictory(uint8_t player, uint8_t gameBoard[3][3])
{
	uint8_t victoryPlayer = (player == PLAYER1) ? PLAYER1_VICTORY : PLAYER2_VICTORY; 
	
	// Check 1: all rows
	for(int row=0; row<3; row++)
	{
		if(gameBoard[0][row] == player && gameBoard[1][row] == player && gameBoard[2][row]==player)
		{
			gameBoard[0][row]=victoryPlayer; gameBoard[1][row]=victoryPlayer; gameBoard[2][row]=victoryPlayer;
			return true;
		}
	}
	
	// Check 2: all columns
	for(int col=0; col<3; col++)
	{
		if(gameBoard[col][0] == player && gameBoard[col][1] == player && gameBoard[col][2]==player)
		{
			gameBoard[col][0]=victoryPlayer; gameBoard[col][1]=victoryPlayer; gameBoard[col][2]=victoryPlayer;
			return true;
		}
	}
	
	// Check 3: the first diagonal
	if(gameBoard[0][0] == player && gameBoard[1][1] == player && gameBoard[2][2]==player)
	{
		gameBoard[0][0]=victoryPlayer; gameBoard[1][1]=victoryPlayer; gameBoard[2][2]=victoryPlayer;
		return true;
	}
	
	// Check 4: the second diagonal
	if(gameBoard[2][0] == player && gameBoard[1][1] == player && gameBoard[0][2]==player)
	{
		gameBoard[2][0]=victoryPlayer; gameBoard[1][1]=victoryPlayer; gameBoard[0][2]=victoryPlayer;
		return true;
	}
	
	// no check positiv
	return false;
}
