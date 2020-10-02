/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>  // including the library of servo motor

Servo azimuth;      // defining servo positions
Servo elevation;    // defining servo positions
#define azpin 3     // defining the I/O pin on arduino 
#define elpin 5     // defining the I/O pin on arduino 
void setup() {
  azimuth.attach(azpin);   // Pin on which the function is there
  elevation.attach(elpin); // Pin on which the function is there
}

void loop() {
  azimuth.write(90);   //make the azimuth servo turn 90 degree
  elevation.write(1);  //make the elevation servo turn 90 degree
}
  

