#include <avr/io.h>
#include <avr/interrupt.h>

///volatile unsigned char cnt = 0;
///unsigned char cnt0 = 0;


void pwm()
{
	unsigned char i = 0;		

	
	for(i=0;i<200;i++)
	{
		if(i == 179) PORTA ^= 0x04;
		if(i == 159) PORTA ^= 0x02;

	}
	PORTA ^= 0x0F;


}


ISR(TIMER0_OVF_vect)
{
	pwm();
	
	TCNT0 = 255;
	
}
int main()
{
	DDRA = 0xFF;
	PORTA = 0xFF;


	cli();

	TCCR0 = 0x01;
	TIMSK = (0x01 << TOIE0);
	

	sei();

	while(1);


	return 0;
}
