/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo azimuth;  
Servo elevation;
#define azpin 3
#define elpin 5
void setup() {
  azimuth.attach(azpin);
  elevation.attach(elpin);
}

void loop() {
  azimuth.write(90);
  elevation.write(1);
}
  

