#include <STC12C5A60S2.H>
#include "BackRoom.h"

sbit OUTPUT = P2^2;

sbit btn1 = P0^0;
sbit btn2 = P0^1;
sbit btn3 = P0^2;
sbit btn4 = P0^3;
sbit btn5 = P0^4;
sbit btn6 = P0^5;
sbit btn7 = P0^6;
sbit btn8 = P0^7;
sbit btn9 = P2^0;

sbit light1 = P1^0;
sbit light2 = P1^1;
sbit light3 = P1^2;
sbit light4 = P1^3;
sbit light5 = P1^4;
sbit light6 = P1^5;
sbit light7 = P1^6;
sbit light8 = P1^7;
sbit light9 = P2^1;

int answerStep = 0;
int myAnswer[9] = {0,0,0,0,0,0,0,0,0};

int answer1[9] = {1,2,3,6,8,7,4,5,9};
int answer2[9] = {1,4,7,8,6,3,2,5,9};
int answer3[9] = {1,5,9,6,3,2,4,7,8};
int answer4[9] = {1,5,9,8,7,4,2,3,6};

int isBtn1_Click = 0;
int isBtn2_Click = 0;
int isBtn3_Click = 0;
int isBtn4_Click = 0;
int isBtn5_Click = 0;
int isBtn6_Click = 0;
int isBtn7_Click = 0;
int isBtn8_Click = 0;
int isBtn9_Click = 0;

void init()
{
	btn1 = 0;
	btn2 = 0;
	btn3 = 0;
	btn4 = 0;
	btn5 = 0;
	btn6 = 0;
	btn7 = 0;
	btn8 = 0;
	btn9 = 0;
	
	light1 = 1;
	light2 = 1;
	light3 = 1;
	light4 = 1;
	light5 = 1;
	light6 = 1;
	light7 = 1;
	light8 = 1;
	light9 = 1;
	
	OUTPUT = 1;
}

int check()
{
	int isCorrect1 = 0;
	int isCorrect2 = 0;
	int isCorrect3 = 0;
	int isCorrect4 = 0;
	
	if(answerStep == 9)
	{
		if((myAnswer[0] == answer1[0])&&
		(myAnswer[1] == answer1[1])&&
		(myAnswer[2] == answer1[2])&&
		(myAnswer[3] == answer1[3])&&
		(myAnswer[4] == answer1[4])&&
		(myAnswer[5] == answer1[5])&&
		(myAnswer[6] == answer1[6])&&
		(myAnswer[7] == answer1[7])&&
		(myAnswer[8] == answer1[8]))
		{
			isCorrect1 = 1;
		}
		
		if((myAnswer[0] == answer2[0])&&
		(myAnswer[1] == answer2[1])&&
		(myAnswer[2] == answer2[2])&&
		(myAnswer[3] == answer2[3])&&
		(myAnswer[4] == answer2[4])&&
		(myAnswer[5] == answer2[5])&&
		(myAnswer[6] == answer2[6])&&
		(myAnswer[7] == answer2[7])&&
		(myAnswer[8] == answer2[8]))
		{
			isCorrect2 = 1;
		}
		
		if((myAnswer[0] == answer3[0])&&
		(myAnswer[1] == answer3[1])&&
		(myAnswer[2] == answer3[2])&&
		(myAnswer[3] == answer3[3])&&
		(myAnswer[4] == answer3[4])&&
		(myAnswer[5] == answer3[5])&&
		(myAnswer[6] == answer3[6])&&
		(myAnswer[7] == answer3[7])&&
		(myAnswer[8] == answer3[8]))
		{
			isCorrect3 = 1;
		}
		
		if((myAnswer[0] == answer4[0])&&
		(myAnswer[1] == answer4[1])&&
		(myAnswer[2] == answer4[2])&&
		(myAnswer[3] == answer4[3])&&
		(myAnswer[4] == answer4[4])&&
		(myAnswer[5] == answer4[5])&&
		(myAnswer[6] == answer4[6])&&
		(myAnswer[7] == answer4[7])&&
		(myAnswer[8] == answer4[8]))
		{
			isCorrect4 = 1;
		}
		
		if((isCorrect1 == 1) || (isCorrect2 == 1) || (isCorrect3 == 1) || (isCorrect4 == 1))
		{
			OUTPUT = 0;
			while(1);
			return 1;
		}
		else
		{
			answerStep = 0;
			light1 = 1;
			light2 = 1;
			light3 = 1;
			light4 = 1;
			light5 = 1;
			light6 = 1;
			light7 = 1;
			light8 = 1;
			light9 = 1;
			
			btn1 = 0;
			btn2 = 0;
			btn3 = 0;
			btn4 = 0;
			btn5 = 0;
			btn6 = 0;
			btn7 = 0;
			btn8 = 0;
			btn9 = 0;
			
			isBtn1_Click = 0;
			isBtn2_Click = 0;
			isBtn3_Click = 0;
			isBtn4_Click = 0;
			isBtn5_Click = 0;
			isBtn6_Click = 0;
			isBtn7_Click = 0;
			isBtn8_Click = 0;
			isBtn9_Click = 0;
			
			isCorrect1 = 0;
			isCorrect2 = 0;
			isCorrect3 = 0;
			isCorrect4 = 0;
			
			return 0;
		}
	}
}

void main()
{
	init();
	
	while(1)
	{
		if((btn1 == 1)&&(isBtn1_Click == 0))
		{
			delay_ms(50);
			if(btn1 == 0)
			{
				isBtn1_Click = 1;
				myAnswer[answerStep] = 1;			
				light1 = 0;
				answerStep++;
				if(check() == 1)
				{
					return;
				}
			}
		}
		
		if((btn2 == 1)&&(isBtn2_Click == 0))
		{
			delay_ms(50);
			if(btn2 == 0)
			{
				isBtn2_Click = 1;
				myAnswer[answerStep] = 2;
				light2 = 0;
				answerStep++;
				if(check() == 1)
				{
					return;
				}
			}
		}
		
		if((btn3 == 1)&&(isBtn3_Click == 0))
		{
			delay_ms(50);
			if(btn3 == 0)
			{
				isBtn3_Click = 1;
				myAnswer[answerStep] = 3;
				light3 = 0;
				answerStep++;
				if(check() == 1)
				{
					return;
				}
			}
		}
		
		if((btn4 == 1)&&(isBtn4_Click == 0))
		{
			delay_ms(50);
			if(btn4 == 0)
			{
				isBtn4_Click = 1;
				myAnswer[answerStep] = 4;
				light4 = 0;
				answerStep++;
				if(check() == 1)
				{
					return;
				}
			}
		}
		
		if((btn5 == 1)&&(isBtn5_Click == 0))
		{
			delay_ms(50);
			if(btn5 == 0)
			{
				isBtn5_Click = 1;
				myAnswer[answerStep] = 5;
				light5 = 0;
				answerStep++;
				if(check() == 1)
				{
					return;
				}
			}
		}
		
		if((btn6 == 1)&&(isBtn6_Click == 0))
		{
			delay_ms(50);
			if(btn6 == 0)
			{
				isBtn6_Click = 1;
				myAnswer[answerStep] = 6;
				light6 = 0;
				answerStep++;
				if(check() == 1)
				{
					return;
				}
			}
		}
		
		if((btn7 == 1)&&(isBtn7_Click == 0))
		{
			delay_ms(50);
			if(btn7 == 0)
			{
				isBtn7_Click = 1;
				myAnswer[answerStep] = 7;
				light7 = 0;
				answerStep++;
				if(check() == 1)
				{
					return;
				}
			}
		}
		
		if((btn8 == 1)&&(isBtn8_Click == 0))
		{
			delay_ms(50);
			if(btn8 == 0)
			{
				isBtn8_Click = 1;
				myAnswer[answerStep] = 8;
				light8 = 0;
				answerStep++;
				if(check() == 1)
				{
					return;
				}
			}
		}
		
		if((btn9 == 1)&&(isBtn9_Click == 0))
		{
			delay_ms(50);
			if(btn9 == 0)
			{
				isBtn9_Click = 1;
				myAnswer[answerStep] = 9;
				light9 = 0;
				answerStep++;
				if(check() == 1)
				{
					return;
				}
			}
		}
	}
	
	while(1);
}
