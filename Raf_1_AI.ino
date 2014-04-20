//
// Ultrasonic HR-SC04 sensor test
//
// http://robocraft.ru
//

#include "Ultrasonic.h"

// sensor connected to:
// Trig - 2, Echo - 3
Ultrasonic ultrasonic(12, 13);

int states[4][4] = {{HIGH, LOW, LOW, HIGH},
                  {HIGH, HIGH, LOW, LOW},
                  {LOW, HIGH, HIGH, LOW},
                  {LOW, LOW, HIGH, HIGH}};

boolean MOVE_BACKWARD = false;
boolean MOVE_FORWARD = true;

boolean ROTATE_CLOCKWISE = true;
boolean ROTATE_ANTICLOCKWISE = false;


int motor2_pins[] =   { 11, 10, 9, 8 };
int motor1_pins[] =   { 7, 6, 5, 4 };


// Двигает робота вперед-назад
void move(int* pins1, int* pins2, int speedMotor = 2, boolean _direction = MOVE_FORWARD){

  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      digitalWrite(pins1[j], states[(_direction) ? i : 3-i ][j]);
      digitalWrite(pins2[j], states[(_direction) ? i : 3-i ][j]);
    }
    delay(speedMotor + 1);
  }

}

// Вращает робота
void rotate(int* pins1, int* pins2, int speedMotor = 2, boolean _direction = ROTATE_CLOCKWISE){

  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      digitalWrite(pins2[j], states[(_direction) ? i : 3-i ][j]);
      digitalWrite(pins1[j], states[(_direction) ? 3-i : i ][j]);
    }
    delay(speedMotor + 1);
  }

}


void rotate_on_angle(int angle = 360, boolean _direction = ROTATE_CLOCKWISE){
    for(int j=0; j<=int(3.4*angle); j++) {
      rotate(motor1_pins, motor2_pins, 2, _direction);
    }
}


void move_in_cm(int dist, boolean _direction = MOVE_FORWARD){
  for(int j=0; j<=23.6667*dist; j++) {
      move(motor1_pins, motor2_pins, 2, _direction);
    }
}

void setup()
{
  for (int p=8; p<=11; p++) pinMode(p,OUTPUT);
  for (int p=3; p<=7; p++) pinMode(p,OUTPUT);
//  Serial.begin(9600); 						// start the serial port
}

void loop()
{
  float dist_cm = ultrasonic.Ranging(CM); 	                // get distance
  tone(3, 3900, 50);
  //Serial.println(dist_cm); 					// print the distance
  if(dist_cm < 30.0 && dist_cm > 1.0){
   tone(3, 3900, 200);
   rotate_on_angle(10);
   tone(3, 3900, 200);

   rotate_on_angle(60);

  }
  else
  {
    move_in_cm(10);
  }

}
