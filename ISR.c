#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char cnt = 0;
volatile unsigned char i = 0;

unsigned char cnt0 = 0;

ISR(TIMER0_OVF_vect)
{
	
	cnt ++;
	if(cnt==44){
		PORTA ^= 0xFF;
		TCNT0=255;
		cnt=0;
	}

}
int main()
{
	DDRA = 0xFF;
	PORTA = 0xFF;


	cli();

	TCCR0 = 0x01;
	TIMSK = (0x01 << TOIE0);
	TCNT0 = 255;

	sei();

	while(1);


	return 0;
}
