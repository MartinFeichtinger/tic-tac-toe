#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

enum padding {EMPTY=0, CIRCLE=1, CROSS=2};
enum padding gameField[3][3];	// [x][y]

void printField();
void clearField();
bool strokeCheck();		// 1 = stroke; 0 = no stroke
void autoPlay(uint8_t counter);

int main()
{
	uint8_t counter=0;
	uint8_t x=0;
	uint8_t y=0;
	uint8_t player;
	uint8_t gameMode;
	
	printf("Choose a game mode:\n");
	printf("1:1v1	2:1vCOM\n");
	
	do{
		scanf("%hhd", &gameMode);
	}
	while((gameMode < 1) || (gameMode > 2));
	
	
	system("clear");
	clearField();
	printField();
	
	while(counter<9)
	{	
		if(counter%2 == 0)
		{
			player=1;
		}
		else
		{
			player=2;
			
			if(gameMode == 2)		// gameMode = 1vCOM
			{
				autoPlay(counter);
				goto label2;
			}
		}
		
		printf("Spieler %d gib deine Koordinaten ein (X-->ENTER-->Y-->ENTER)\n", player);
		label1:
		
		while(1)
		{
			scanf("%hhd", &x);
			scanf("%hhd", &y);
			
			if(x<0 || x>2 || y<0 || y>2)
			{
				printf("Die Koodinaten befinden sich nicht mehr auf dem Spielfeld. Versuch es noch einmal...\n");
			}
			else
			{
				break;
			}
		}
		
		if(gameField[x][y] == EMPTY)
		{
			if(player == 1)
			{
				gameField[x][y]=CIRCLE;
			}
			else
			{
				gameField[x][y]=CROSS;
			}
		}
		else
		{
			printf("Das Feld ist bereits belegt. Versuche es noch einmal...\n");
			//counter--;
			goto label1;
		}
		
		label2:
		printField();
		
		if(counter>=4)		// the game needs at least 5 moves untile someone can win. counter>=4 since the counter starts with 0
		{
			if(strokeCheck())
			{
				printf("Spieler %d hat gewonnen!\n", player);
				break;
			}
		}
		
		counter++;
	}
}


void printField()
{
	system("clear");
	
	//printf(" 0 1 2\n");
	
	for(int y=0; y<3; y++)
	{
		//printf("%d", y);
		for(int x=0; x<3; x++)
		{
			if(gameField[x][y]==EMPTY)
			{
				printf(" ");
			}
			
			else if(gameField[x][y]==CIRCLE)
			{
				printf("0");
			}
			
			else if(gameField[x][y]==CROSS)
			{
				printf("X");
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

void clearField()
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			gameField[j][i]=EMPTY;
		}
	}
}

bool strokeCheck()
{
	enum padding firstChar;
	
	// Check 1: all rows
	for(int row=0; row<3; row++)
	{
		firstChar=gameField[0][row];
		
		if(firstChar == EMPTY) continue;				// only full lines can be a stroke
		if(gameField[1][row] != firstChar) continue;	// if the first and second charakter is different skip the rest
		
		if(gameField[2][row] == firstChar)
		{
			return true;
		}
		
	}
	
	// Check 2: all columns
	for(int col=0; col<3; col++)
	{
		firstChar=gameField[col][0];
		
		if(firstChar == EMPTY) continue;				// only full lines can be a stroke
		if(gameField[col][1] != firstChar) continue;	// if the first and second charakter is different skip the rest
		
		if(gameField[col][2] == firstChar)
		{
			return true;
		}
		
	}
	
	// Check 3: the first diagonal
	firstChar=gameField[0][0];
	
	if(firstChar != EMPTY)
	{
		if((gameField[1][1] == firstChar) && (gameField[2][2] == firstChar))
		{
			return true;
		}
	}	
	
	
	// Check 4: the second diagonal
	firstChar=gameField[0][2];
	
	if(firstChar != EMPTY)
	{
		if((gameField[1][1] == firstChar) && (gameField[2][0] == firstChar))
		{
			return true;
		}
	}	
	
	return false;
}

void autoPlay(uint8_t counter)
{
	if(counter == 1)
	{
		if(gameField[1][1] == EMPTY)
		{
			gameField[1][1]=CROSS;
		}
		else
		{
			gameField[0][0]=CROSS;
		}
	}
	else
	{	
		// check possible win
		for(int y=0; y<3; y++)
		{
			for(int x=0; x<3; x++)
			{
				if(gameField[x][y] == EMPTY)
				{
					gameField[x][y]=CROSS;
					if(strokeCheck())
					{
						return;
					}
					else
					{
						gameField[x][y]=EMPTY;
					}
				}
			}
		}
		
		// check possible loss
		for(int y=0; y<3; y++)
		{
			for(int x=0; x<3; x++)
			{
				if(gameField[x][y] == EMPTY)
				{
					gameField[x][y]=CIRCLE;
					if(strokeCheck())
					{
						gameField[x][y]=CROSS;
						return;
					}
					else
					{
						gameField[x][y]=EMPTY;
					}
				}
			}
		}
		
		// no chace for victory or loss
		for(int y=0; y<3; y++)
		{
			for(int x=0; x<3; x++)
			{
				if(gameField[x][y] == EMPTY)
				{
					gameField[x][y]=CROSS;
					return;
				}
			}
		}
	}
}
