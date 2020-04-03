#include <LPC214x.h>

#define LCD_RS (1<<10)
#define LCD_RW (1<<12)
#define LCD_EN (1<<13)

void lcd_cmd (unsigned char val);
void lcd_data (unsigned char val);
void delay (unsigned int);
unsigned char cmd1[5] = {0x0E,0x38,0x06,0x01,0x80};//0x38 two line Selection,0x0E Display On,0x06 increment right,0x01 clear display,0x80 first row
unsigned char msg1[] = "Angad Kumar";
unsigned char msg2[] = "VTU:10751";

int main()
{
	unsigned int i;
	PINSEL1 = 0x00000000;
	IODIR0 |= 0x00FF3400;//rs=0.10,rw=0.12,en=0.13,D0-D7=P0.16-P0.23
	IOCLR0 = 0x00FF3400;
  for (i=0; i<5; i++)
	 lcd_cmd(cmd1[i]);

	for (i=0; msg1[i] != '\0' ; i++)
	 lcd_data (msg1[i]);
	
	lcd_cmd (0xc0);

	for (i=0; msg2[i] != '\0' ; i++)
	 lcd_data (msg2[i]);

	while(1);
}
void lcd_cmd(unsigned char val)
{
	IO0PIN = (val<<16);
	IOCLR0 = LCD_RS;//Control Signl
	IOCLR0 = LCD_RW;//write  always 0
	IOSET0 = LCD_EN;//High to low Pulse
	delay(10);
	IOCLR0= LCD_EN;
	delay(20);

}

void lcd_data(unsigned char val)
{
	IO0PIN = (val<<16);
	IOSET0 = LCD_RS;// '1' means data
	IOCLR0 = LCD_RW;//write means 0 bit
	IOSET0 = LCD_EN;//High to low pulse
	delay(10);
	IOCLR0= LCD_EN;
	delay(20);

}
void delay (unsigned int value)
{
	unsigned int i,j;
	for(i=value; i>0; i--)
	{
   	for (j=0; j<value; j++);
	}
}

