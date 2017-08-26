
void delay_ms(int count)  // /* X1ms */	 —” ±1ms≥Ã–Ú
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
}


unsigned int step = 0;

void setStep(int s)
{
	step = s;
}