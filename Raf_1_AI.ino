//
// Ultrasonic HR-SC04 sensor test
//
// http://robocraft.ru
//

#include "Ultrasonic.h"

// sensor connected to:
// Trig - 2, Echo - 3
Ultrasonic ultrasonic(12, 13);


void unStepMotor(int pin_1, int pin_2,int pin_3,int pin_4,int speedMotor){
  digitalWrite(pin_1,HIGH);
  digitalWrite(pin_2,LOW);
  digitalWrite(pin_3,LOW);
  digitalWrite(pin_4,HIGH);
  delay(speedMotor + 1);
  //
  digitalWrite(pin_1,HIGH);
  digitalWrite(pin_2,HIGH);
  digitalWrite(pin_3,LOW);
  digitalWrite(pin_4,LOW);
  delay(speedMotor + 1);
  //
  digitalWrite(pin_1,LOW);
  digitalWrite(pin_2,HIGH);
  digitalWrite(pin_3,HIGH);
  digitalWrite(pin_4,LOW);
  delay(speedMotor + 1);
  //
  digitalWrite(pin_1,LOW);
  digitalWrite(pin_2,LOW);
  digitalWrite(pin_3,HIGH);
  digitalWrite(pin_4,HIGH);
  delay(speedMotor + 1);
 
}



void setup()
{
  for (int p=8; p<=11; p++) pinMode(p,OUTPUT);
  for (int p=3; p<=7; p++) pinMode(p,OUTPUT);
  Serial.begin(9600); 						// start the serial port
}

void loop()
{
  
  
  float dist_cm = ultrasonic.Ranging(CM); 	// get distance
  tone(3, 3900, 50);
  //Serial.println(dist_cm); 					// print the distance 
  if(dist_cm < 25.0 && dist_cm > 1.0){
    tone(3, 3900, 200);
    delay(500);
    tone(3, 3900, 200);
    for(int j=0; j<=999; j++) { 
      unStepMotor( 7, 6, 5, 4, 1); 
    }
  }
  else
  {
    for(int j=0; j<=99; j++) { 
      unStepMotor( 11, 10, 9, 8, 1); 
      unStepMotor( 7, 6, 5, 4, 1); 
    }
  }
  
}
