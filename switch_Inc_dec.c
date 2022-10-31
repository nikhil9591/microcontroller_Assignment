/*
  16x2 LCD (8-bit mode) interfacing with LPC2148(ARM7)
  http://www.electronicwings.com/arm7/lcd-16x2-interfacing-with-lpc2148-8-bit-mode
*/

#include <lpc214x.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"

void delay_ms(uint16_t j) /* Function for delay in milliseconds  */
{
    uint16_t x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<3000; x++);    /* loop to generate 1 millisecond delay with Cclk = 60MHz */
	}
}

void LCD_CMD(char command)
{
	IO0PIN = ( (IO0PIN & 0xFFFF00FF) | (command<<8) );
	IO0SET = 0x00000040; /* EN = 1 */
	IO0CLR = 0x00000030; /* RS = 0, RW = 0 */
	delay_ms(2);
	IO0CLR = 0x00000040; /* EN = 0, RS and RW unchanged(i.e. RS = RW = 0) */
	delay_ms(5);
}

void LCD_INIT(void)
{
	IO0DIR = 0x0000FFF0; /* P0.8 to P0.15 LCD Data. P0.4,5,6 as RS RW and EN */
	delay_ms(20);
	LCD_CMD(0x38);  /* Initialize lcd */
	LCD_CMD(0x0C);   /* Display on cursor off */
	LCD_CMD(0x06);  /* Auto increment cursor */
	LCD_CMD(0x01);   /* Display clear */
	LCD_CMD(0x80);  /* First line first position */
}
void LCD_CHAR (char msg)
{
		IO0PIN = ( (IO0PIN & 0xFFFF00FF) | (msg<<8) );
		IO0SET = 0x00000050; /* RS = 1, , EN = 1 */
		IO0CLR = 0x00000020; /* RW = 0 */
		delay_ms(2);
		IO0CLR = 0x00000040; /* EN = 0, RS and RW unchanged(i.e. RS = 1, RW = 0) */
		delay_ms(5);
}


void LCD_STRING (char* msg)
{
	uint8_t i=0;
	while(msg[i]!=0)
	{
		IO0PIN = ( (IO0PIN & 0xFFFF00FF) | (msg[i]<<8) );
		IO0SET = 0x00000050; /* RS = 1, , EN = 1 */
		IO0CLR = 0x00000020; /* RW = 0 */
		delay_ms(1);
		IO0CLR = 0x00000040; /* EN = 0, RS and RW unchanged(i.e. RS = 1, RW = 0) */
		delay_ms(2);
		i++;
	}
	
	//while(*msg!='\0') {
  //      LCD_CHAR(*msg++);
 //   }

}



int switches(uint8_t j, char *val_j)

{

	LCD_STRING("Val of j is:");
	while(1)
{
	IO1DIR = 0x00;
	
		if((IO1PIN & (1<<16))==0) // condition for p1.16 pin
{
		j = j+1;                  // increment j by 1
		sprintf(val_j,"%d ",j);   // pushing j value to val_j character array 
		LCD_STRING(val_j);	      // passing array value to lcd diplay 
		
		LCD_CMD(0x8C);            // holding the posintion of lcd with output
}

else if((IO1PIN & (1<<17))==0) //condition for p1.17 pin

{
		j = j-1;                // decrement j by 1
		sprintf(val_j,"%d ",j);  // pushing j value to val_j character array
		LCD_STRING(val_j);	    // passing array value to lcd diplay
		
		LCD_CMD(0x8C);					// holding the posintion of lcd with output
	
}
		
	}	
}


int main(void)
{
	uint8_t j;
	j = 0;
	char val_j[10];
	LCD_INIT();
	switches(j,val_j);
	return 0;
}



