#include <FastLED.h>

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
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];
#define DATA_PIN NEOPIXELPIN
#define BRIGHTNESS 20
Servo azimuth;
Servo elevation;
void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  Serial.begin(115200);
  Serial.println("Ready Aim Fire!");
  

  azimuth.attach(SERV1);
  elevation.attach(SERV2);
  azimuth.write(80);
  elevation.write(3);
  pinMode(SOLENOID,OUTPUT);
  digitalWrite(SOLENOID,LOW);
  pinMode(PUMP,OUTPUT);
  digitalWrite(PUMP,HIGH);
  delay(10000);
  digitalWrite(PUMP, LOW);
  pinMode(BUTTON,INPUT_PULLUP);
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(200);
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(200);
  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(200);
  leds[0] = CRGB::Black;
  FastLED.show();
 
}
void chase()
{
     // Move a single white led 
   for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
      // Turn our current led on to white, then show the leds
      leds[whiteLed] = CRGB::White;

      // Show the leds (only one of which is set to white, from above)
      FastLED.show();

      // Wait a little bit
      delay(250);

      // Turn our current led back to black for the next loop around
      leds[whiteLed] = CRGB::Black;
      FastLED.show();
   }
}
int lastx;
int lasty;

void loop() {

  
 
  int light = analogRead(LIGHT);
  int temp = analogRead(TEMP);
  //Serial.print("LIGHT: ");Serial.print(light);Serial.print(" TEMP: ");Serial.println(temp);
   if (digitalRead(BUTTON) == LOW)
  {
    Serial.println("fire!");
    digitalWrite(SOLENOID,HIGH);
    delay(250);
    digitalWrite(SOLENOID,LOW);
    chase();
    digitalWrite(PUMP,HIGH);
    delay(3000);
    digitalWrite(PUMP, LOW);
    delay(100);
  }
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
