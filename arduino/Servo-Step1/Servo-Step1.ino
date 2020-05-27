#include <Servo.h>

#define SOLENOID 2
#define PUMP 9
#define BUTTON 12
#define JOYX A0
#define JOYY A1
#define SERV1 3
#define SERV2 5
#define SERV3 6
#define LIGHT A2
#define TEMP A3
#define NEOPIXELPIN 8

Servo azimuth;
Servo elevation;
void setup() {
  azimuth.attach(SERV1);
  elevation.attach(SERV2);

  pinMode(SOLENOID,OUTPUT);
  pinMode(JOYX,INPUT);
  pinMode(JOYY,INPUT);
  pinMode(BUTTON,INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Joy!");
  azimuth.write(80);
  elevation.write(3);

}
//x center 515, ycenter 490
int lastx,lasty;
void loop() {
 int xReading,yReading;
  xReading = analogRead(JOYX);
  yReading = analogRead(JOYY);

if(abs(lastx-xReading) > 2)
{
  if (xReading <490)
  {
    azimuth.write(map(xReading,490,0,90,2));
  }else
  if (xReading > 489)
  {
    azimuth.write(map(xReading,489,1023,91,178));
  }
  lastx = xReading;

}
if (abs(lasty-yReading) > 2)
{
  if (yReading <515)
  {
    elevation.write(map(yReading,515,0,31,70));
  }else
  if (yReading > 514)
  {
    elevation.write(map(yReading,524,1023,30,3));
  }
  lasty = yReading;
  
}
  
}
