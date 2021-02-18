#define F_CPU 16000000UL
 
//1. baud rate를 선택
#define USART_BAUDRATE 9600


#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
unsigned char rx_flag=1;




void USART_Init(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/*Enable receiver and transmitter */
	UCSR0B = (1<<TXEN0)|(1<<RXEN0);
	/* Set frame format: 8data, 2stop bit */

	DDRB = 0xFF;
	cli();
	TCCR0B = 0x01;
	TIMSK0 = (0x01 << TOIE0);
	sei();

}




unsigned char RX0_ch(void)
{
	while(!(UCSR0A&(1<<RXC0)));
	rx_flag=1;
	return UDR0;

}

void TX0_ch(unsigned char data)
{
	while(!(UCSR0A&(1<<UDRE0)));

	UDR0=data;

}

void TX0_STR(unsigned char* str)
{
	int i;
	
	for(i=0;*(str+i)!='\0';i++)
	{
		TX0_ch(*(str+i));
		
	}
}






int main(void)
{
	unsigned char ptr[100][100];
	unsigned char rxs_buf[100];
	unsigned char rx_buf;
	
	unsigned char* LINE="\r\n=======================================\r\n";
	

	int i=0,j=0,k=0,l=0;

	

	USART_Init(UBRR_VALUE);
	
	
	

	while(1)
	{
	  rx_buf = RX0_ch();
	  TX0_ch(rx_buf);
    
	  i++;
	  if(rx_buf=='\n')
	  {
	   
		for(j=0;rxs_buf[j]!='\r';j++)
		{
		  ptr[k][l]=rxs_buf[j];
		  if(rxs_buf[j]==',')
		  {
		    ptr[k][l]=0;
		    k++;	
		    l=0;

		  }
		  else
		  {
		    l++;
		  }
	

		}		

  
		if(strncmp(rxs_buf,"$GPGGA",6)==0)
	    {
			///TX0_STR("TIME");
			
			

	    }
	    else if(strncmp(rxs_buf,"$GPGGV",6)==0)
	    {
	    

	    }
	    else if(strncmp(rxs_buf,"$GPGSA",6)==0)
	    {}
	    else if(strncmp(rxs_buf,"$GPRMC",6)==0)
	    {}

	    else if(strncmp(rxs_buf,"$GPVTG",6)==0)
	    {}	

	    
		
	    k=0; 
	    i=0;
	  }

      
	  
	}


	



}
