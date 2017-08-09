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
#define NUM_LEDS 8
CRGB leds[NUM_LEDS];
#define DATA_PIN NEOPIXELPIN
#define BRIGHTNESS 20
Servo xServo,yServo;
void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  Serial.begin(115200);
  Serial.println("Ready Aim Fire!");
  

  xServo.attach(SERV1);
  yServo.attach(SERV2);
  yServo.write(90);
  pinMode(SOLENOID,OUTPUT);
  digitalWrite(SOLENOID,LOW);
  pinMode(PUMP,OUTPUT);
  digitalWrite(PUMP,HIGH);
  delay(4000);
  digitalWrite(PUMP, LOW);
/* 

 pinMode(RED,OUTPUT);
 pinMode(GREEN, OUTPUT);
 pinMode(BLUE,OUTPUT);
 */
 pinMode(BUTTON,INPUT_PULLUP);


 
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
      delay(100);

      // Turn our current led back to black for the next loop around
      leds[whiteLed] = CRGB::Black;
      FastLED.show();
   }
}
int lastx;
int lasty;

void loop() {

  
  if (digitalRead(BUTTON) == LOW)
  {
    Serial.println("fire!");
    digitalWrite(SOLENOID,HIGH);
    delay(250);
    digitalWrite(SOLENOID,LOW);
    chase();
    digitalWrite(PUMP,HIGH);
    delay(4000);
    digitalWrite(PUMP, LOW);
    delay(100);
  }
  int light = analogRead(LIGHT);
  int temp = analogRead(TEMP);
  //Serial.print("LIGHT: ");Serial.print(light);Serial.print(" TEMP: ");Serial.println(temp);
  int x = analogRead(JOYX);
  int y = analogRead(JOYY);

  if(abs(lastx-x)>2)
  {
    Serial.print("X: ");Serial.println(x);
    xServo.write(x/4);
    lastx =x;
  }
  if(abs(lasty-y)>2)
  {

    // Y is also around 450-500 but y axis is at 90 essentially at rest,  so map forward and back;
    Serial.print("Y: ");Serial.println(y);
    if (y < 523)
    {
      yServo.write(map(y,0,518,1,100));
    }else
      yServo.write(map(y,519,1023,101,130));
    lasty = y;
  }

}
