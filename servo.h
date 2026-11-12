void PWM_INIT(void)
{
	PINSEL1 |= 1<<10; //to select p0.21 pin as pwm5 functionality
	PWMMR0 = 300000;
	PWMMR5 = 15000;
	PWMMCR = 0X02; //reset PWMTC if PWMTC == PWMMR0
	PWMPCR = 1<<13; //to enable PWM5 output
	PWMTCR = 0X09;//PWM and Timer enabled
	PWMLER = 0X21;// LER configured as to enable PWM0 and PWM5

}
void PWM_0deg(void)
{
	PWMMR5 = 15000;
	PWMLER = 0X20;
}
void PWM_90deg(void)
{
	PWMMR5 = 30000;
	PWMLER = 0X20;
}

