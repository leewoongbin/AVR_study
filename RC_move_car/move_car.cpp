#include <Arduino.h>
#include "move_car.h"

#define ENA   6
#define EN1   7
#define EN2   9 ///3

#define EN3   4
#define EN4   8 ///2
#define ENB   5

void init_move_car()
{
  pinMode(ENA, OUTPUT);  // ENA
  pinMode(EN1, OUTPUT);  // EN1
  pinMode(EN2, OUTPUT);  // EN2

  pinMode(ENB, OUTPUT);  // ENB
  pinMode(EN3, OUTPUT);  // EN3
  pinMode(EN4, OUTPUT);  // EN4
	
}

void _move(int direction,int carSpeed)
{
	if( direction == 1 ) {  // forward
      digitalWrite(EN1, HIGH);
      digitalWrite(EN2, LOW);
      analogWrite(ENA, carSpeed);
      digitalWrite(EN3, HIGH);
      digitalWrite(EN4, LOW);
      analogWrite(ENB, carSpeed);
    }
    else if( direction == 2 ) {  // left
      digitalWrite(EN1, LOW);
      digitalWrite(EN2, HIGH);
      analogWrite(ENA, carSpeed);
      digitalWrite(EN3, HIGH);
      digitalWrite(EN4, LOW);
      analogWrite(ENB, carSpeed);
    }
    else if( direction == 3 ) {  // RIGHT
      digitalWrite(EN1, HIGH);
      digitalWrite(EN2, LOW);
      analogWrite(ENA, carSpeed);
      digitalWrite(EN3, LOW);
      digitalWrite(EN4, HIGH);
      analogWrite(ENB, carSpeed);
    }
    else if( direction == 4 ) {  // backward
      digitalWrite(EN1, LOW);
      digitalWrite(EN2, HIGH);
      analogWrite(ENA, carSpeed);
      digitalWrite(EN3, LOW);
      digitalWrite(EN4, HIGH);
      analogWrite(ENB, carSpeed);
    }
    else if( direction == 0 ) {  // stop
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
    }
	
	
}