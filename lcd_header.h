#include<lpc21xx.h>
#include<string.h>
#define lcd_d 0x0f<<23
#define RS 1<<27
#define E 1<<28

void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char *);
void LCD_INTEGER(int);
void LCD_FLOAT(float);
void delay_ms(unsigned int);

void LCD_INIT(void)
{
	IODIR1 = lcd_d|RS|E;
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X02);
	LCD_COMMAND(0X0C);
	LCD_COMMAND(0X28);
}
void LCD_COMMAND(unsigned char cmd)
{
	IOCLR1 = lcd_d;
	IOSET1 = (cmd&0XF0)<<19;
	IOCLR1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
	
	IOCLR1 = lcd_d;
	IOSET1 = (cmd&0X0F)<<23;
	IOCLR1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;		
}
void LCD_DATA(unsigned char d)
{
   IOCLR1 = lcd_d;
	IOSET1 = (d&0XF0)<<19;
	IOSET1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
	
	IOCLR1 = lcd_d;
	IOSET1 = (d&0X0F)<<23;
	IOSET1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
}
void LCD_STR(unsigned char *str)
{
	int cnt=0;
	while(*str)
	{
		cnt++;
		LCD_DATA(*str++);
		if(cnt==16)
			LCD_COMMAND(0XC0);
	}
}
void LCD_INTEGER(int n)
{
	unsigned char arr[5];
	int i;
	if(n==0)
	{
		LCD_DATA(n);
	}
	else
	{
		if(n<0)
		{
			n=-n;
			LCD_DATA('-');
		}
		while(n!=0)
		{
			arr[i++] = n%10;
			n=n/10;
		}
		for(i=i-1;i>=0;i--)
		{
			LCD_DATA(arr[i]+48);
		}
	}
}
void LCD_FLOAT(float f)
{
	int n = f;
	LCD_INTEGER(n);
	LCD_DATA('.');
	n = (f-n)*100;
	LCD_INTEGER(n);
}
void delay_ms(unsigned int ms)
{
	unsigned int i;
	for( ;ms>0;ms--)
	{
		for(i=12000;i>0;i--)
		{
		
		}
	}
}
