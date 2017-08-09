#include <Adafruit_NeoPixel.h>

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
Adafruit_NeoPixel strip = Adafruit_NeoPixel(3, NEOPIXELPIN, NEO_GRB + NEO_KHZ800);


Servo xServo,yServo;
void setup() {
  Serial.begin(115200);
  Serial.println("Ready Aim Fire!");
  
  strip.begin();
  strip.setBrightness(20);
  strip.show(); // Initialize all pixels to 'off'
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

int lastx;
int lasty;
void blank() // black out the neopixel strip
{
  for (int i = 0; i < strip.numPixels();i++)
    strip.setPixelColor(i,0);

   strip.show();
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
void loop() {

  
  if (digitalRead(BUTTON) == LOW)
  {
    Serial.println("fire!");
    digitalWrite(SOLENOID,HIGH);
    delay(250);
    digitalWrite(SOLENOID,LOW);
    rainbowCycle(10);
    blank();
    digitalWrite(PUMP,HIGH);
    delay(4000);
    digitalWrite(PUMP, LOW);
    delay(100);
  }
  int light = analogRead(LIGHT);
  int temp = analogRead(TEMP);
  Serial.print("LIGHT: ");Serial.print(light);Serial.print(" TEMP: ");Serial.println(temp);
  int x = analogRead(JOYX);
  int y = analogRead(JOYY);

  if(abs(lastx-x)>2)
  {
    //Serial.print("X: ");Serial.println(x);
    xServo.write(x/4);
    lastx =x;
  }
  if(abs(lasty-y)>2)
  {

    // Y is also around 450-500 but y axis is at 90 essentially at rest,  so map forward and back;
    //Serial.print("Y: ");Serial.println(y);
    if (y < 523)
    {
      yServo.write(map(y,0,523,1,80));
    }else
      yServo.write(map(y,524,1023,81,110));
    lasty = y;
  }

}
