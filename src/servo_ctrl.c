#define F_CPU 16000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define USART_BAUDRATE 9600

#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)


#define PULSE_MIN 1000 //최소 펄스 지정
#define PULSE_MAX 5000 //최대 펄스 지정

void INIT_TIMER(void)
{
  TCCR1A |= (1<<WGM11);
  TCCR1B |= (1<<WGM12) | (1<<WGM13); //고속 PWM 모드, TOP : ICR1
  TCCR1B |= (1<<CS11); //분주율 8, 2MHz
  ICR1 = PULSE_MAX; //20ms주기
  TCCR1A |= (1<<COM1A1); //비반전 모드
  DDRB = 0xFF  ; ///디지털 9번 핀 사용
}


int main(void)
{
  INIT_TIMER();
  int i;
    
  while (1) 
  {
    for(i=PULSE_MIN; i<=PULSE_MAX; i+=100)
    {
      OCR1A = i;
      _delay_ms(50);
    }
    for(i=PULSE_MAX; i>=PULSE_MIN; i-=100)
    {
      OCR1A = i;
      _delay_ms(50);
    }
  }
}