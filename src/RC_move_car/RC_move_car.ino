#include "rc_rx.h"
#include "move_car.h"

#define dt 20         

unsigned  long t=0;
 
int carDirection = 0; ///stop

int carSpeed = 200; ///0~255

void setup()
{
  Serial.begin(115200); // Initlizing serial port before calling init_rc_rx() function 
  init_rc_rx();
  init_move_car();
}

void loop()
{ 
  t = micros()/1000;
  
  read_rc_rx();       
  
  Serial.print(CH1);
  Serial.print("\t");
  Serial.print(CH2);
  Serial.print("\t");
  
  Serial.println(((micros()/1000)- (float)t)*100/dt);
  
  if(CH1 > 100) carDirection = 1;  ///foward
  else if(CH1 < 2) carDirection = 4; ///backward
  else if(CH2 > 100) carDirection = 2; //left
  else if(CH2 < 2) carDirection = 3;  //right
  else if((48<CH1 && CH1<51)||(48<CH2 && CH2<51) ) carDirection = 0; //stop

  _move(carDirection,carSpeed);
  Serial.println(carDirection);
  
  while (dt > (micros()/1000)- t){

  }
  
  
}
