#include<lpc21xx.h>
void UART0_CONFIG_BLUETOOTH(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX_BLUETOOTH(void);
char* UART0_STR_RX_BLUETOOTH(void);
void UART0_STR_TX_BLUETOOTH(unsigned char *);


void UART0_CONFIG_BLUETOOTH(void)
{
	PINSEL0=0X5;
	U0LCR = 0X83;//TO Select '8N1' Data frame format and DLAB as 1
	U0DLL = 97;//to set baud rate as 9600
	U0DLM = 0;
	U0LCR = 0X03;//DLAB = 0, TO ACCESS U0THR AND U0RBR Registers
}
unsigned char UART0_RX_BLUETOOTH(void)
{
	while((U0LSR&1)==0);
	return U0RBR;
}
void UART0_TX(unsigned char ch)
{
	while(((U0LSR>>5)&1)==0);
	U0THR = ch;
}
char* UART0_STR_RX_BLUETOOTH(void)
{
	unsigned char rxByte,i=0;
	static char str[20];
	while(1)
	{
		rxByte = UART0_RX_BLUETOOTH();
		if(rxByte=='\n')
		{
			str[i] = '\0';
			i=0;
			break;
		}
		str[i++]=rxByte;
	}
	return str;
}
void UART0_STR_TX_BLUETOOTH(unsigned char *str)
{
	while(*str)
	{
		UART0_TX(*str++);
	}
}
