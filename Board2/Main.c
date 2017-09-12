#include <STC89C5xRC.H>
#include "Board2.h"
#include "BackRoom.h"
#include "uart.h"
#include "mp3.h"

sbit INPUT_A = P0^0;
sbit INPUT_B = P0^1;
sbit INPUT_C = P0^2;

sbit LIGHT_A = P1^0;
sbit LIGHT_B = P1^1;
sbit LIGHT_C = P1^2;

sbit OUTPUT_DOOR = P0^3;

sbit INDOOR = P0^4;//开始信号 输入高开始

void init()
{
	INDOOR = 0;
	INPUT_A = 0;
	INPUT_B = 0;
	INPUT_C = 0;
	
	LIGHT_A = 1;
	LIGHT_B = 1;
	LIGHT_C = 1;
	
	OUTPUT_DOOR = 1;
}

void CheckInput()
{
	if(INPUT_A == 0)
	{
		delay_ms(50);
		if(INPUT_A == 1)
		{
			//播放语音
			play_mp3(0,0x01);
			delay_ms(10000);
		}
	}
		
	if(INPUT_B == 0)
	{
		delay_ms(50);
		if(INPUT_B == 1)
		{
			//播放语音
			play_mp3(0,0x02);
			delay_ms(10000);
		}
	}
		
	if(INPUT_C == 0)
	{
		delay_ms(50);
		if(INPUT_C == 1)
		{
			//播放语音
			play_mp3(0,0x03);
			delay_ms(10000);
		}
	}
		
	if((INPUT_A == 1)&&(INPUT_B == 1)&&(INPUT_C == 1))
	{		
		setStep(2);
	}
}
void main()
{
	init();
	uart_init();
	mp3_init();

	delay_ms(100);	
	
	while(1)
	{
		switch(step)
		{
			case 0:
				if(INDOOR == 1)
				{
					setStep(1);
				}
				break;
			case 1:
				CheckInput();
				break;
			case 2:
				OUTPUT_DOOR = 0;
				break;
		}
		
		
		
	}
}