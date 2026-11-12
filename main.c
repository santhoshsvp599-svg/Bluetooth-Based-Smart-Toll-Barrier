#include<lpc21xx.h>
#include"lcd_header.h"
#include"uart_fun.h"
#include"servo.h"
#define led1 1<<10
#define led2 1<<11
void PROJECT_INIT(void);
void EXT_INT0_isr(void)__irq
{
	char *gate;
	LCD_STR("Vehicle IS DETECTED");	
	UART0_STR_TX_BLUETOOTH("Vehicle IS DETECTED\n");
	delay_ms(2000);
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);
	LCD_STR("GATE: OPEN (or) CLOSE : ");
	UART0_STR_TX_BLUETOOTH("GATE: OPEN (or) CLOSE\n");
	gate = UART0_STR_RX_BLUETOOTH();
	if((strcmp(gate,"open")==0)||(strcmp(gate,"OPEN")))
	{
		IOCLR0 = led1;
		
		PWM_90deg();
		UART0_STR_TX_BLUETOOTH("GATE OPENED\n");
		LCD_COMMAND(0X01);
		LCD_COMMAND(0X80);
		LCD_STR("GATE OPENED");	
		delay_ms(5000);
					
		IOSET0 = led1;
	}
	if((strcmp(gate,"close")==0)||(strcmp(gate,"CLOSE")))
	{
		IOCLR0 = led2;
		
		PWM_0deg();	
	}
	
	PWM_0deg();
	UART0_STR_TX_BLUETOOTH("GATE CLOSED\n");
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);
	LCD_STR("GATE CLOSED");	
	IOCLR0 = led2;
	delay_ms(2000);
	IOSET0 = led2;

	EXTINT = 0X01;
	VICVectAddr = 0;
}
int main()
{
	int cnt = 0;
	UART0_CONFIG_BLUETOOTH();
	PROJECT_INIT();
	PWM_INIT();
	PINSEL1|=1<<0;//SELECT P0.16 CONFIGURED AS EINT0 PIN
	IODIR0|= led1|led1;
	IOSET0 = led1|led2;

	//All are selected as IRQ
	VICIntSelect = 0X00000000;

	//allocate slot0 for EINT0
	VICVectCntl0 = (1<<5)|14;
	VICVectAddr0 = (int)EXT_INT0_isr;

	//falling edge triggered mode
	EXTMODE = 0X01;
	EXTPOLAR = 0X00;

	//To enable external interrupt0 and external interuupt 1
	VICIntEnable = (1<<14);

	while(1)
	{
		cnt++;
	}
}
void PROJECT_INIT(void)
{
	unsigned char project_name[40]="TITLE : TOLL BARRIER"; 	
	UART0_CONFIG_BLUETOOTH();
	LCD_INIT();
	LCD_COMMAND(0X80);
	LCD_STR(project_name);
	delay_ms(5000);
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);	
}
