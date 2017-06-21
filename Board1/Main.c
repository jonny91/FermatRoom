#include <STC12C5A60S2.H>
#include "Board1.h"
#include "BackRoom.h"
#include "uart.h"
#include "mp3.h"

//第一个房间过来的信号 开始计时
sbit FROM_ROOM1 = P0^0;
sbit LIGHT_1 = P0^1;
sbit LIGHT_2 = P0^2;
sbit LIGHT_3 = P0^3;
sbit LIGHT_4 = P0^4;
sbit ABC_SWITCH = P0^5; //ABC机关的开关
sbit LIGHT_INPUT_1 = P1^1;
sbit LIGHT_INPUT_2 = P1^2;
sbit LIGHT_INPUT_3 = P1^3;
sbit LIGHT_INPUT_4 = P1^4;

sbit HUO_1 = P0^6;
sbit HUO_2 = P0^7;
sbit HUO_3 = P1^5;
sbit HUO_4 = P1^6;
sbit HUO_5 = P1^7;
sbit HUO_6 = P2^0;
sbit HUO_7 = P2^1;
sbit HUO_8 = P2^2;
sbit HUO_9 = P2^3;

sbit GAME_B_BTN1 = P2^4;
sbit GAME_B_BTN2 = P2^5;
sbit GAME_B_LOCK = P2^6;//B机关成功 电磁锁的门

sbit GAME_C_1 = P3^4; //C机关指定摆放
sbit GAME_C_2 = P3^5;

sbit ROOM_3_DOOR = P3^6;//房间3的门


int i = 0;
int five_minute_light_step = 0;
int myAnswer[10] = {0,0,0,0,0,0,0,0,0,0};
int answerLength = 10;

void start();
void timer0();
void fiveMinutes();
void gameA();
void gameB();
void gameC();

void init()
{
	FROM_ROOM1 = 0;
	LIGHT_1 = 1;
	LIGHT_2 = 1;
	LIGHT_3 = 1;
	LIGHT_4 = 1;
	LIGHT_INPUT_1 = 0;
	LIGHT_INPUT_2 = 0;
	LIGHT_INPUT_3 = 0;
	LIGHT_INPUT_4 = 0;
	ABC_SWITCH = 0;
	
	HUO_1 = 0;
	HUO_2 = 0;
	HUO_3 = 0;
	HUO_4 = 0;
	HUO_5 = 0;
	HUO_6 = 0;
	HUO_7 = 0;
	HUO_8 = 0;
	HUO_9 = 0;
	GAME_B_BTN1 = 0;
	GAME_B_BTN2 = 0;
	GAME_B_LOCK = 0;
	
	GAME_C_1 = 0;
	GAME_C_2 = 0;
	
	ROOM_3_DOOR = 0;
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
	if(FROM_ROOM1 == 1)
	{
		delay_ms(2000);
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
	
}


void gameB()
{
	int btn = 0;
	if(GAME_B_BTN1 == 0)
	{
		delay_ms(20);
		if(GAME_B_BTN1 == 1)
		{
			btn = 1;
		}
	}
	
	if(GAME_B_BTN1 == 0)
	{
		delay_ms(20);
		if(GAME_B_BTN1 == 1)
		{
			btn = 2;
		}
	}
	
	if(btn != 0)
	{
		int answerIndex = 0;
		for(answerIndex = 0 ; answerIndex < answerLength-1 ; answerIndex++ )
		{
			myAnswer[answerIndex] = myAnswer[answerIndex+1];
		}
		myAnswer[answerLength - 1] = btn;
		
		for(answerIndex == 0 ; answerIndex<answerLength ; answerIndex++)
		{
			if(CORRECT[answerIndex] == myAnswer[answerIndex])
			{
				if(answerIndex == answerLength - 1)
				{
					i = TICKER;	//计时器归0
					GAME_B_LOCK = 1;//电磁锁断电
					gameStep = 3;
					return;
				}
				else
				{
					return;
				}
			}
		}
	}
}

void gameC()
{
	if((GAME_C_1 == 1)&&(GAME_C_2 == 1))
	{
		i = TICKER;	//计时器归0
		ET0 = 0;//计时器停止
		gameStep = 4;
		setStep(2);
		LIGHT_1 = 1;
		LIGHT_2 = 1;
		LIGHT_3 = 1;
		LIGHT_4 = 1;
		ROOM_3_DOOR = 1;
	}
}

void Timer_Routine(void) interrupt 1
{
	TL0 = 0x00;
	TH0 = 0x4C;

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

		TMOD = 0x01;
		TL0 = 0x00;	
		TH0 = 0x4C;
		ET0 = 1;
    EA  = 1;
    TR0 = 1;

}