#include <Arduino.h>
#include "rc_rx.h"



#define CH1_int 0     
#define CH1_pin 2     

#define CH2_int 1      
#define CH2_pin 3     

#define valid_pulse_limit 3000 
#define max_high_time 1895 
#define min_high_time 1090 

volatile unsigned long CH1_t=0, CH1_delta=0, CH2_t=0, CH2_delta=0 ;
float CH1,CH2;


void CH1_int_ISR()
{
  if ((micros()-CH1_t) < valid_pulse_limit){
    CH1_delta = micros()-CH1_t;
  }
  CH1_t = micros();
}

void CH2_int_ISR()
{
  if ((micros()-CH2_t) < valid_pulse_limit){
    CH2_delta = micros()-CH2_t;
  }
  CH2_t = micros();
}


void init_rc_rx(){
  
  pinMode(CH1_pin, INPUT);
  pinMode(CH2_pin, INPUT);
   
  attachInterrupt(CH1_int, CH1_int_ISR, CHANGE);
  attachInterrupt(CH2_int, CH2_int_ISR, CHANGE);
  
}

void read_rc_rx(){
  CH1 = ((float)CH1_delta-(float)min_high_time)*100/(max_high_time-min_high_time);
  CH2 = ((float)CH2_delta-(float)min_high_time)*100/(max_high_time-min_high_time);
 
}
