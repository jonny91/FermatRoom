#include <STC89C5xRC.H>
#include "Board2.h"
#include "BackRoom.h"
#include "uart.h"
#include "mp3.h"

sbit INPUT_A = P0^0;
sbit INPUT_B = P0^1;
sbit INPUT_C = P0^2;

sbit OUTPUT_DOOR = P0^3;

void init()
{
	INPUT_A = 0;
	INPUT_B = 0;
	INPUT_C = 0;
	
	OUTPUT_DOOR = 0;
}
void main()
{
	init();
	uart_init();
	mp3_init();

	delay_ms(100);	
	
	while(1)
	{
		if(INPUT_A == 0)
		{
			delay_ms(50);
			if(INPUT_A == 1)
			{
				//播放语音
				playMp3(0x01);
				delay_ms(10000);
			}
		}
		
		if(INPUT_B == 0)
		{
			delay_ms(50);
			if(INPUT_B == 1)
			{
				//播放语音
				playMp3(0x02);
				delay_ms(10000);
			}
		}
		
		if(INPUT_C == 0)
		{
			delay_ms(50);
			if(INPUT_C == 1)
			{
				//播放语音
				playMp3(0x03);
				delay_ms(10000);
			}
		}
		
		if((INPUT_A == 1)&&(INPUT_B == 1)&&(INPUT_C == 1))
		{
			OUTPUT_DOOR = 1;
			break;
		}
	}
}