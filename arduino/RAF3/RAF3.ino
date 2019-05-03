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
const int MAX_AZ = 180;
const int MIN_AZ = 0;
const int MAX_EL = 125;
const int MIN_EL = 0;
const float AZ_GAIN = 1./8000.;
const float EL_GAIN = 1./4000.;
Servo azimuth;
Servo elevation;

int xCenter, yCenter;

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
  digitalWrite(PUMP, LOW);
  pinMode(BUTTON,INPUT_PULLUP);
  leds[0] = CRGB::Black;
  FastLED.show();
 xCenter = analogRead(JOYX);
 yCenter = analogRead(JOYY);
  digitalWrite(PUMP,HIGH);
  delay(100);
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(200);
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(200);
  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(200);
 
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
float current_az = 90;
float current_el = 45;

void loop() {
 int xReading,yReading;
 int light = analogRead(LIGHT);
 int temp = analogRead(TEMP);
 if (digitalRead(BUTTON) == LOW){
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
 xReading = analogRead(JOYX);
 yReading = analogRead(JOYY);

 /*
 Serial.print("xReading: ");
 Serial.print(xReading);
 Serial.print(", yReading: ");
 Serial.print(yReading);

 Serial.print(", delta_az: ");
 Serial.print(delta_az);
 Serial.print(", current_az: ");
 Serial.print(current_az);

 Serial.print(", delta_el: ");
 Serial.print(delta_el);
 Serial.print(", current_el: ");
 Serial.println(current_el);
 */
 
 float delta_az = - AZ_GAIN * (xReading - xCenter);
 current_az += delta_az;
 if(current_az > MAX_AZ){
   current_az = MAX_AZ;
 }
 if(current_az < MIN_AZ){
   current_az = MIN_AZ;
 }
 float delta_el = EL_GAIN * (yReading - yCenter);
 current_el += delta_el;
 if(current_el > MAX_EL){
   current_el = MAX_EL;
 }
 if(current_el < MIN_EL){
   current_el = MIN_EL;
 }
 azimuth.write(current_az);
 elevation.write(current_el);
 return;
 
}
