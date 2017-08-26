#include <STC12C5A60S2.H>
#include "Board1.h"
#include "BackRoom.h"
#include "uart.h"
#include "mp3.h"

typedef unsigned char BYTE;
typedef unsigned int WORD;
#define FOSC 11059200L
#define MODE1T                      //Timer clock mode, comment this line is 12T mode, uncomment is 1T mode

#ifdef MODE1T
#define T1MS (65536-FOSC/1000)      //1ms timer calculation method in 1T mode
#else
#define T1MS (65536-FOSC/12/1000)   //1ms timer calculation method in 12T mode
#endif

//口令输入
sbit FROM_ROOM1 = P0^0;
sbit ROOM_2 = P2^7;

sbit LIGHT_1 = P0^1;
sbit LIGHT_2 = P0^2;
sbit LIGHT_3 = P0^3;
sbit LIGHT_4 = P0^4;
sbit ABC_SWITCH = P0^5; //ABC机关的开关
sbit LIGHT_INPUT_1 = P1^1;
sbit LIGHT_INPUT_2 = P1^2;
sbit LIGHT_INPUT_3 = P1^3;
sbit LIGHT_INPUT_4 = P1^4;

int isIntroduceLight = 0;//是不是介绍过了激光

sbit INPUT_A = P3^7;
sbit GAME_A_LOCK = P3^2;

sbit TO_BOARD_2 = P0^6;

sbit GAME_B_BTN1 = P2^4;
sbit GAME_B_BTN2 = P2^5;
sbit GAME_B_LOCK = P2^6;//B机关成功 电磁锁的门

sbit GAME_C_1 = P3^4; //C机关指定摆放
sbit GAME_C_2 = P3^5;

sbit ROOM_3_DOOR = P3^6;//房间3的门


int i = 0;
int five_minute_light_step = 0;

void start();
void timer0();
void fiveMinutes();
void gameA();
void gameB();
void gameC();

void init()
{
	FROM_ROOM1 = 0;
	ROOM_2 = 1;
	
	LIGHT_1 = 1;
	LIGHT_2 = 1;
	LIGHT_3 = 1;
	LIGHT_4 = 1;
	LIGHT_INPUT_1 = 1;
	LIGHT_INPUT_2 = 1;
	LIGHT_INPUT_3 = 1;
	LIGHT_INPUT_4 = 1;
	ABC_SWITCH = 1;
	
	INPUT_A = 0;
	GAME_A_LOCK = 1;
	
	GAME_B_BTN1 = 0;
	GAME_B_BTN2 = 0;
	GAME_B_LOCK = 1;
	
	GAME_C_1 = 0;
	GAME_C_2 = 0;
	
	ROOM_3_DOOR = 1;
}
void main()
{
	init();
	uart_init();
	mp3_init();
	timer0();
	//定时器暂停
	ET0 = 0;

	delay_ms(100);	
	
	while(1)
	{
		switch(step)
		{
			case 0:
				start();
				break;
			case 1:
				fiveMinutes();
				break;
			case 2:
				break;
		}
	}
}

void start()
{
	if(FROM_ROOM1 == 1) //口令正确 打开门
	{
		delay_ms(2000);
		ROOM_2 = 0;
		play_mp3(0,MUSIC_301);
		setStep(1);
	}
}

void checkLightStep()
{
	if(five_minute_light_step == 1)
	{
		LIGHT_1 = 1;
		LIGHT_2 = 0;
		LIGHT_3 = 0;
		LIGHT_4 = 0;
		
		if(isIntroduceLight == 0)
		{
			play_mp3(0,MUSIC_303); // 第一次触发介绍激光
			isIntroduceLight = 1;
		}
	}
	else if(five_minute_light_step == 2)
	{
		LIGHT_1 = 1;
		LIGHT_2 = 1;
		LIGHT_3 = 0;
		LIGHT_4 = 0;
	}
	else if(five_minute_light_step == 3)
	{
		LIGHT_1 = 1;
		LIGHT_2 = 1;
		LIGHT_3 = 1;
		LIGHT_4 = 0;
	}
	else if(five_minute_light_step == 4)
	{
		LIGHT_1 = 1;
		LIGHT_2 = 1;
		LIGHT_3 = 1;
		LIGHT_4 = 1;
	}
}

//检查有没有碰到激光
void checkTouchLight()
{
	if(five_minute_light_step == 1)
	{
		if(LIGHT_INPUT_1 == 0)//被挡住了
		{
			ABC_SWITCH = 0;
		}
		else
		{
			ABC_SWITCH = 1;
		}
	}
	else if(five_minute_light_step == 2)
	{
		if((LIGHT_INPUT_1 == 0) || (LIGHT_INPUT_2 == 0))//被挡住了
		{
			ABC_SWITCH = 0;
		}
		else
		{
			ABC_SWITCH = 1;
		}
	}
	else if(five_minute_light_step == 3)
	{
		if((LIGHT_INPUT_1 == 0) || (LIGHT_INPUT_2 == 0) || (LIGHT_INPUT_3 == 0))//被挡住了
		{
			ABC_SWITCH = 0;
		}
		else
		{
			ABC_SWITCH = 1;
		}
	}
	else if(five_minute_light_step == 4)
	{
		if((LIGHT_INPUT_1 == 0) || (LIGHT_INPUT_2 == 0) || (LIGHT_INPUT_3 == 0) || (LIGHT_INPUT_4 == 0))//被挡住了
		{
			ABC_SWITCH = 0;
		}
		else
		{
			ABC_SWITCH = 1;
		}
	}
}

int gameStep = 1;
void fiveMinutes()
{
	ET0 = 1;
	while(1)
	{
		checkTouchLight();
		if(gameStep == 1)
		{
			gameA();
		}
		else if(gameStep == 2)
		{
			gameB();
		}
		else if(gameStep == 3)
		{
			gameC();
		}
	}
}

void gameA()
{
	if(INPUT_A == 1)
	{
		delay_ms(50);
		if(INPUT_A == 1)
		{
			play_mp3(0,MUSIC_302);
			i = TICKER;	//计时器归0
			GAME_A_LOCK = 0;//打开电磁锁
			gameStep = 2;
		}
	}
}

int isGameBButton1Pressed = 0;
int isGameBButton2Pressed = 0;
int gameBMyAnswer[4] = {0,0,0,0};
void gameB()
{
	int btn = 0;
		
	if((isGameBButton1Pressed == 0)&&(GAME_B_BTN1 == 1))
	{
		isGameBButton1Pressed = 1;
	}
	
	if((isGameBButton2Pressed == 0)&&(GAME_B_BTN2 == 1))
	{
		isGameBButton2Pressed = 1;
	}
	
	if((isGameBButton1Pressed == 1)&&(isGameBButton2Pressed == 1))//同时按下
	{
		while((isGameBButton1Pressed == 1)&&(isGameBButton2Pressed == 1)){}; //直到松开
		isGameBButton1Pressed = 0;
		isGameBButton2Pressed = 0;
		
		btn = 3;
	}
	
	if((isGameBButton1Pressed == 1)&&(isGameBButton2Pressed == 0))
	{
		while((isGameBButton1Pressed == 1)&&(isGameBButton2Pressed == 0));
		isGameBButton1Pressed = 0;
		isGameBButton2Pressed = 0;
		btn = 1;
	}
	
	if((isGameBButton1Pressed == 0)&&(isGameBButton2Pressed == 1))
	{
		while((isGameBButton1Pressed == 0)&&(isGameBButton2Pressed == 1));
		isGameBButton1Pressed = 0;
		isGameBButton2Pressed = 0;
		btn = 2;
	}

	if(btn != 0)
	{
		gameBMyAnswer[0] = gameBMyAnswer[1];
		gameBMyAnswer[1] = gameBMyAnswer[2];
		gameBMyAnswer[2] = gameBMyAnswer[3];
		gameBMyAnswer[3] = btn;

		if((gameBMyAnswer[0] == gameBAnswer[0])&&
		(gameBMyAnswer[1] == gameBAnswer[1])&&
		(gameBMyAnswer[2] == gameBAnswer[2])&&
		(gameBMyAnswer[3] == gameBAnswer[3]))//正确
		{
			play_mp3(0,MUSIC_304);
			i = TICKER;	//计时器归0
			GAME_B_LOCK = 0;//电磁锁断电
			gameStep = 3;
		}
	}
}

void gameC()
{
	if((GAME_C_1 == 1)&&(GAME_C_2 == 1))
	{
		play_mp3(0,MUSIC_305);
		i = TICKER;	//计时器归0
		ET0 = 0;//计时器停止
		gameStep = 4;
		setStep(2);
		LIGHT_1 = 1;
		LIGHT_2 = 1;
		LIGHT_3 = 1;
		LIGHT_4 = 1;
		ROOM_3_DOOR = 0;
	}
}

void Timer_Routine(void) interrupt 1
{
	TL0 = T1MS;                     //reload timer0 low byte
    TH0 = T1MS >> 8;                //reload timer0 high byte

    i--;

    if(i == 0)
	{
		i = TICKER;		
		//5分钟到了
		five_minute_light_step++;
		checkLightStep();
    }        
}


void timer0()
{
    i = TICKER;	
	
#ifdef MODE1T
    AUXR = 0x80;                    //timer0 work in 1T mode
#endif
    TMOD |= 0x01;                    //set timer0 as mode1 (16-bit)
    TL0 = T1MS;                     //initial timer0 low byte
    TH0 = T1MS >> 8;                //initial timer0 high byte
    TR0 = 1;                        //timer0 start running
    ET0 = 1;                        //enable timer0 interrupt
    EA = 1;                         //open global interrupt switch
}