#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


#define ROWGREEN0	PA0
#define ROWRED0		PA1
#define ROWGREEN1	PA2
#define ROWRED1		PA3
#define ROWGREEN2	PA4
#define ROWRED2		PA5

#define COL0		PB4
#define COL1		PB5
#define COL2		PB6

#define BUTTONS		PA6
#define MODE		PA7
#define SPEAKER		PB3


#define BUTTON_NONE	0
#define BUTTON_OK	1
#define BUTTON_NEXT	2

#define MODE_KIvKI				0
#define MODE_PLAYER1vKI			1
#define MODE_KIvPLAYER2			2
#define MODE_PLAYER1vPLAYER2	3


// function prototyps
void initPorts(void);
void initTimers(void);
void startUp(void);
void celebrateVictory(uint8_t player);
void wait(uint32_t time);

uint8_t getButtonState(void);
uint8_t getModeState(void);
uint16_t readAnalogPin(uint8_t pin);

void nextField(void);
void switchPlayer(void);
bool strokeCheck(void);		// 1 = stroke; 0 = no stroke
void autoPlay(uint8_t turns);

void playSound(uint8_t tone);


// global variabls
uint8_t colCounter=0;
uint16_t blinkTimer=0;

enum Padding {EMPTY=0, GREEN=1, RED=2};
enum Padding gameMap[3][3]={0};		// [x][y] // 0=EMPTY; 1=GREEN=CIRCLE; 2=RED=CROSS
enum Padding outputCol[3]={0};

uint8_t playerPosX=3;
uint8_t playerPosY=3;
enum Padding player=RED;
enum Padding otherPlayer=GREEN;

enum Padding stroke[3][3]={0};

uint8_t mode;
uint8_t turns=0;
bool tie=false;

uint32_t soundTime;


int main(void)
{	
	initPorts();
	initTimers();
	startUp();
	mode=getModeState();
	
	while(1)
	{
		switch(mode)
		{
			case MODE_PLAYER1vPLAYER2:
			{
				if(getButtonState() == BUTTON_NEXT)
				{
					playSound(150);
					nextField();
				}
				if((getButtonState() == BUTTON_OK) && (gameMap[playerPosX][playerPosY]==EMPTY))
				{
					if((gameMap[playerPosX][playerPosY]==EMPTY))
					{
						playSound(250);
						gameMap[playerPosX][playerPosY]=player;
						
						if(strokeCheck() == true)
						{
							celebrateVictory(player);
						}
						
						turns++;
						switchPlayer();
						nextField();
					}
				}
				break;
			}
			case MODE_PLAYER1vKI:
			{
				if(player == 1)
				{
					if(getButtonState() == BUTTON_NEXT)
					{
						playSound(150);
						nextField();
					}
					if((getButtonState() == BUTTON_OK) && (gameMap[playerPosX][playerPosY]==EMPTY))
					{
						playSound(250);
						gameMap[playerPosX][playerPosY]=player;
						
						if(strokeCheck() == true)
						{
							celebrateVictory(player);
						}
						
						switchPlayer();
						playerPosX=3;
						playerPosY=3;
						turns++;						
					}
				}
				else
				{
					autoPlay(turns);
					switchPlayer();
					turns++;
					nextField();
				}
				break;
			}
			case MODE_KIvPLAYER2:
			{
				if(player == 1)
				{
					autoPlay(turns);
					switchPlayer();
					turns++;
					nextField();
				}
				else
				{
					if(getButtonState() == BUTTON_NEXT)
					{
						playSound(150);
						nextField();
					}
					if((getButtonState() == BUTTON_OK) && (gameMap[playerPosX][playerPosY]==EMPTY))
					{
						playSound(250);
						gameMap[playerPosX][playerPosY]=player;
						
						if(strokeCheck() == true)
						{
							celebrateVictory(player);
						}
						
						switchPlayer();
						playerPosX=3;
						playerPosY=3;
						turns++;						
					}
				}
				break;
			}
			case MODE_KIvKI:
			{
				autoPlay(turns);
				switchPlayer();
				turns++;
			}
		}
		
		if(turns >= 9)
		{
			tie=true;
			
			playSound(200);
			soundTime=100;
			wait(400);
			playSound(100);
			soundTime=100;
			wait(400);
			playSound(255);
			soundTime=400;
			
			while(1);
		}
	}	
}

void playSound(uint8_t tone)
{
	DDRB|=(1<<SPEAKER);
	TCCR1B|=(1<<CS11)|(1<<CS10);	// set prescaler to 4
	OCR1C=tone;
	soundTime=10;
}

void celebrateVictory(uint8_t player)
{
	wait(1000);
	playerPosX=3;
	playerPosY=3;
	
	playSound(200);
	soundTime=100;
	wait(400);
	playSound(210);
	soundTime=100;
	wait(400);
	playSound(255);
	soundTime=400;
	
	while(1)
	{
		for(uint8_t y=0; y<3; y++)
		{
			for(uint8_t x=0; x<3; x++)
			{
				if(stroke[x][y] == player)
				{
					gameMap[x][y]=player;
				}
			}
		}
		wait(500);
		for(uint8_t y=0; y<3; y++)
		{
			for(uint8_t x=0; x<3; x++)
			{
				if(stroke[x][y] == player)
				{
					gameMap[x][y]=EMPTY;
				}
			}
		}
		wait(500);
	}
}

void autoPlay(uint8_t turns)
{
	playerPosX=3;
	playerPosY=3;
	wait(1000);
	
	if(turns == 0)
	{	
		uint8_t rand=readAnalogPin(MODE)%4;
		
		switch(rand)
		{
			case 0: gameMap[1][0]=player; break;
			case 1: gameMap[0][1]=player; break;
			case 2: gameMap[2][1]=player; break;
			case 3: gameMap[1][2]=player; break;			
		}
	}
	else if(turns == 1)
	{
		if(gameMap[1][1] == EMPTY)
		{
			gameMap[1][1]=player;
		}
		else
		{
			uint8_t rand=blinkTimer%4;
		
			switch(rand)
			{
				case 0: gameMap[0][0]=player; break;
				case 1: gameMap[0][2]=player; break;
				case 2: gameMap[2][0]=player; break;
				case 3: gameMap[2][2]=player; break;			
			}
		}
	}
	else
	{	
		// check possible win
		for(int y=0; y<3; y++)
		{
			for(int x=0; x<3; x++)
			{
				if(gameMap[x][y] == EMPTY)
				{
					gameMap[x][y]=player;
					if(strokeCheck())
					{
						celebrateVictory(player);
						return;
					}
					else
					{
						memset(stroke, EMPTY, sizeof(stroke));
						gameMap[x][y]=EMPTY;
					}
				}
			}
		}
		
		// check possible loss
		for(int y=0; y<3; y++)
		{
			for(int x=0; x<3; x++)
			{
				if(gameMap[x][y] == EMPTY)
				{
					gameMap[x][y]=otherPlayer;
					if(strokeCheck())
					{
						memset(stroke, EMPTY, sizeof(stroke));
						gameMap[x][y]=player;
						return;
					}
					else
					{
						memset(stroke, EMPTY, sizeof(stroke));
						gameMap[x][y]=EMPTY;
					}
				}
			}
		}
		
		
		// no chace for victory or loss
		uint8_t rand=blinkTimer%3+1;
		
		do{
			for(int y=0; y<3; y++)
			{
				for(int x=0; x<3; x++)
				{
					if(gameMap[x][y] == EMPTY)
					{
						if(rand<=1)
						{
							gameMap[x][y]=player;
							return;
						}
						else
						{
							rand--;
						}
					}
				}
			}
		}while(rand>0);
	}
}

bool strokeCheck()
{
	enum Padding firstChar;
	
	// Check 1: all rows
	for(int row=0; row<3; row++)
	{
		firstChar=gameMap[0][row];
		
		if(firstChar == EMPTY) continue;				// only full lines can be a stroke
		if(gameMap[1][row] != firstChar) continue;		// if the first and second charakter is different skip the rest
		
		if(gameMap[2][row] == firstChar)
		{
			for(uint8_t col=0; col<3; col++) stroke[col][row]=player; 
			return true;
		}
		
	}
	
	// Check 2: all columns
	for(int col=0; col<3; col++)
	{
		firstChar=gameMap[col][0];
		
		if(firstChar == EMPTY) continue;				// only full lines can be a stroke
		if(gameMap[col][1] != firstChar) continue;		// if the first and second charakter is different skip the rest
		
		if(gameMap[col][2] == firstChar)
		{
			for(uint8_t row=0; row<3; row++) stroke[col][row]=player; 
			return true;
		}
		
	}
	
	// Check 3: the first diagonal
	firstChar=gameMap[0][0];
	
	if(firstChar != EMPTY)
	{
		if((gameMap[1][1] == firstChar) && (gameMap[2][2] == firstChar))
		{
			stroke[0][0]=player;
			stroke[1][1]=player;
			stroke[2][2]=player;
			return true;
		}
	}	
	
	
	// Check 4: the second diagonal
	firstChar=gameMap[0][2];
	
	if(firstChar != EMPTY)
	{
		if((gameMap[1][1] == firstChar) && (gameMap[2][0] == firstChar))
		{
			stroke[0][2]=player;
			stroke[1][1]=player;
			stroke[2][0]=player;
			return true;
		}
	}	
	
	return false;
}


void switchPlayer(void)
{
	if(player == RED)
	{
		otherPlayer=RED;
		player=GREEN;
	}
	else
	{
		otherPlayer=GREEN;
		player=RED;
	}
}

void nextField()
{
	if(turns<=8)
	{
		do{
			if(playerPosX < 2)
			{
				playerPosX++;
			}
			else
			{
				if(playerPosY < 2)
				{
					playerPosY++;
					playerPosX=0;
				}
				else
				{
					playerPosX=0;
					playerPosY=0;
				}
			}
		}while(gameMap[playerPosX][playerPosY] != EMPTY);
			
		blinkTimer=0;

		wait(300);
	}
}					

void startUp()
{
	uint8_t tone=250;
	for(uint8_t row=0; row<3; row++)
	{
		for(uint8_t col=0; col<3; col++)
		{
			playSound(tone);
			gameMap[col][row]=GREEN;
			wait(200);
			tone-=3;
		}
	}
	
	
	for(uint8_t row=0; row<3; row++)
	{
		for(uint8_t col=0; col<3; col++)
		{
			playSound(tone);
			gameMap[col][row]=RED;
			wait(200);
			tone-=3;
		}
	}
	
	for(uint8_t row=0; row<3; row++)
	{
		for(uint8_t col=0; col<3; col++)
		{
			playSound(tone);
			gameMap[col][row]=EMPTY;
			wait(200);
			tone-=3;
		}
	}
	
	playerPosX=1;
	playerPosY=1;
	
	mode=getModeState();
}

void wait(uint32_t time)
{
	time*=20;
	for(volatile uint32_t i=0; i<time; i++);
	time=0;
}

uint8_t getModeState(void)
{
	uint16_t modeValue=readAnalogPin(MODE);
	static uint8_t modeStateOld;
	uint8_t modeState;
	
	/*
	 * KI v KI:				1024
	 * Player1 v KI:		689
	 * KI v Player2:		562
	 * Player1 v Player2:	444 
	 */
	
	if(modeValue >= 857)
	{
		modeState=(MODE_KIvKI);
	}
	else if(modeValue >= 625)
	{
		modeState=MODE_KIvPLAYER2;
	}
	else if(modeValue >= 503)
	{
		modeState=MODE_PLAYER1vKI;
	}
	else
	{
		modeState=MODE_PLAYER1vPLAYER2;
	}
	
	if(modeState == modeStateOld)
	{
		return modeState;
	}
	
	modeStateOld=modeState;
	return MODE_PLAYER1vPLAYER2;
}

uint8_t getButtonState()
{
	uint16_t buttonValue=readAnalogPin(BUTTONS);
	static uint8_t buttonStateOld;
	uint8_t buttonState;
	
	/*
	 * NEXT und OK:	1024
	 * NEXT:			689
	 * OK:				562
	 * NONE:			444 
	 */
	
	if(buttonValue >= 857)
	{
		buttonState=(BUTTON_OK|BUTTON_NEXT);
	}
	else if(buttonValue >= 625)
	{
		buttonState=BUTTON_OK;
	}
	else if(buttonValue >= 503)
	{
		buttonState=BUTTON_NEXT;
	}
	else
	{
		buttonState=BUTTON_NONE;
	}
	
	if(buttonState == buttonStateOld)
	{
		return buttonState;
	}
	
	buttonStateOld=buttonState;
	return BUTTON_NONE;
}

uint16_t readAnalogPin(uint8_t pin)
{	
	if(!((DDRA>>pin)&1))				// check if pin is an input
	{
		ADMUX=(pin-1);					// set mutiplexer at input pin
		ADCSRA|=(1<<ADSC);				// start conversation
		while(ADCSRA&(0x01<<ADSC)) {};	// wait untile the conversation is finished
	}
	
	return ADC;
}

void initPorts(void)
{
	// set digital inputs and outputs
	DDRA=0x3F;	// set all ROWxxx as output and BUTTONS and MODE as input
	DDRB|=0x78;	// set all COLx and speaker as output	//***speaker muss vieleich nicht hier sondern bei der Timer init gesetzt werden
	
	// set all outputs to zero
	PORTA&=~0x3F;
	PORTB&=~0x78;
	
	
	// cofigurate ADC for analog pins BUTTONS and MODE
	ADCSRA|=(1<<ADEN);				// enable ADC
	ADCSRA|=(1<<ADPS2)|(1<<ADPS1);	// set ADC prescaler to 64 (8MHz/64=125kHz ... should be between 50Hz and 200Hz)
	DIDR0|=(1<<ADC6D)|(1<<ADC5D);	// disable digital buffer of the analog pins to reduce power consumption
}

void initTimers(void)
{
	cli();
	
	/*
	 * Timer 0: multiplexing of the LEDs
	 * --------------------------------------------------------------
	 * this timer should run in the 8-bit Normal-Mode and trigger all 
	 * 10ms the timer0 interrupt.
	 * 
	 * for prescale=256:
	 * T=(1/8MHz)*256*256=8.2ms 
	 */
	TCCR0A=0;
	TCCR0B=(1<<CS01);	// prescaler=8
	TIMSK|=(1<<TOIE0);	// activate timer0 overflow interrupt
	TCNT0L=0;
	
	//Timer 1: PWM-signal for the speaker
	TCCR1A|=(1<<COM1B0);			// set to toggle on compare match
	TCCR1B=0;						// stop timer 1
	OCR1C=255;						// set period time
	OCR1B=0;						// toggle the output at this value
	
	sei();
}


ISR(TIMER0_OVF_vect)	// gets triggert ca. all 10ms
{
	
	outputCol[0]=gameMap[colCounter][0];
	outputCol[1]=gameMap[colCounter][1];
	outputCol[2]=gameMap[colCounter][2];
		
	// mark the position of the player with a blinking LED
	if(playerPosX == colCounter)
	{
		if(playerPosY >= 0 && playerPosY <=2)
		{
			if(outputCol[playerPosY] == EMPTY)
			{
				// blink in a propotion of 50 to 50
				if(blinkTimer <= 400)
				{
					outputCol[playerPosY]=player;	// player = GREEN or RED
				}
				else
				{
					outputCol[playerPosY]=EMPTY;
				}
			}
		}
	}
	
	if(tie)
	{
		for(uint8_t y=0; y<3; y++)
		{
			// blink in a propotion of 50 to 50
			if(blinkTimer <= 400)
			{
				outputCol[y]=gameMap[colCounter][y];	// player = GREEN or RED
			}
			else
			{
				outputCol[y]=EMPTY;
			}
		}
	}
	
	PORTA&=~0x3F;	// set all rows to 0
	PORTB&=~0x70;	// set all columns to 0
	
	for(uint8_t row=0; row<3; row++)
	{
		if(outputCol[row])
		{	
			/*
			 * green: gameMap[col][row]=1
			 * -----------------
			 * |row|gameMap|pin|
			 * | 0 |   1   | 0 |
			 * | 1 |   1   | 2 |
			 * | 2 |   1   | 4 |
			 * -----------------
			 * pin=row*2
			 * 
			 * red: gameMap[col][row]=2
			 * -----------------
			 * |row|gameMap|pin|
			 * | 0 |   2   | 1 |
			 * | 1 |   2   | 3 |
			 * | 2 |   2   | 5 |
			 * -----------------
			 * pin=row*2+1
			 * 
			 * pin=row*2+(gameMap-1)
			 */ 
			
			uint8_t pin=(row*2+(outputCol[row]-1));
			PORTA|=(1<<pin);
			
			PORTB|=(1<<(colCounter+4));
		}
	}
	
	if(colCounter>=2)
	{
		colCounter=0;
	}
	else
	{
		colCounter++;
	}
	
	if(blinkTimer>=800)
	{
		blinkTimer=0;
	}
	else
	{
		blinkTimer++;
	}
	
	if(soundTime <= 0)
	{
		TCCR1B=0;
		DDRB&=~(1<<SPEAKER);
	}
	else
	{
		soundTime--;
	}
	
	//PORTA=~(PORTA&1);
}
