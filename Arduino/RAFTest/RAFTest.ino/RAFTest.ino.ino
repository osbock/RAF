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
#define NUM_LEDS 9
CRGB leds[NUM_LEDS];
#define DATA_PIN NEOPIXELPIN
#define BRIGHTNESS 20
Servo xServo,yServo;
void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  Serial.begin(115200);
  Serial.println("Ready Aim Fire!");
  
                                                                                                                                                                                                                                                                                                                                                                                                                      
  xServo.attach(SERV1);
  xServo.write(90);

  
  pinMode(BUTTON,INPUT_PULLUP);
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Green;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Blue;
  FastLED.show();
  delay(500);
  leds[0] = CRGB::Black;
  FastLED.show();
 
}

int lastx;
int lasty;

int testnumber =1;
#define NUMTESTS 7
void blinkTestNumber(int testnum){
  for (int i = 0; i < testnum; i++){
    leds[0] = CRGB::Blue;
    FastLED.show();
    delay(150);
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(150);
  }
}
void blinkTestResult(int testnum, boolean result){
  CRGB resultColor = result?CRGB::Green:CRGB::Red;
  // blink the testnumber 3 times on fail
  if(!result)
    for (int i = 0; i <3; i++){
     for (int j= 0 ;j < testnumber;j++)
      {
        leds[0] =resultColor;
        FastLED.show();
        delay(250);
        leds[0] = CRGB::Black;
        FastLED.show();
        delay(250);
     }
     delay(500);
    }
    else
    {
      leds[0]=resultColor;
      FastLED.show();
      delay(1000);
      leds[0] = CRGB::Black;
      FastLED.show();
    }
    Serial.print("Test number ");
    Serial.print(testnum);
    Serial.print(" ");
    Serial.println(result?"passed":"FAILED");
}
void servoTest(){
  xServo.write(180);
  delay(1000);
  xServo.write(0);
  blinkTestResult(7,true);
}
void tempTest(){
  boolean testResult = false;
  unsigned long cumulative = 0L;
  unsigned int averagetemp;
  int delta = 5;
  for (int i = 0; i < 100; i++)
  { 
    cumulative = cumulative + (unsigned long)analogRead(TEMP);
    delay(10);
  }
  averagetemp = cumulative/100;
  Serial.println(averagetemp);
  boolean reading = true;
  while(reading)
  {
    if (digitalRead(BUTTON) == LOW) //break
    {
      break;
    }
    if (analogRead(TEMP) > averagetemp+delta)
    {
      testResult = true;
      break;
    }
  }
  blinkTestResult(5,testResult);
}
void lightTest(){
  boolean testResult = false;
  unsigned long cumulative = 0L;
  unsigned int averagelight;
  int delta = 100;
  for (int i = 0; i < 100; i++)
  { 
    cumulative = cumulative + (unsigned long)analogRead(LIGHT);
    delay(10);
  }
  averagelight = cumulative/100;
  Serial.println(averagelight);
  boolean reading = true;
  while(reading)
  {
    if (digitalRead(BUTTON) == LOW) //break
    {
      break;
    }
    if (averagelight < 15){
      break;
    }
    int lightread = analogRead(LIGHT);
    if (lightread < averagelight-delta)
    {
      testResult = true;
      break;
    }
  }
  blinkTestResult(5,testResult);
}

void pumpTest(){
  digitalWrite(PUMP,HIGH);
  delay(500);
  digitalWrite(PUMP,LOW);
}
void solenoidTest(){
  for(int i = 0; i < 3; i++){
    digitalWrite(SOLENOID,HIGH);
    delay(250);
    digitalWrite(SOLENOID,LOW);
    delay(250);
  }
}
void joystickTest(){
  boolean xcrit1=false,
          xcrit2=false,
          ycrit1=false,
          ycrit2 = false;
  boolean testResult = true;
  while (!(xcrit1 && xcrit2 && ycrit1 && ycrit2)){
    int x = analogRead(JOYX);
    int y = analogRead(JOYY);
    if (x > 1000)
      xcrit1=true;
    if (x < 30)
      xcrit2 = true;
    if (y >1000)
      ycrit1 = true;
    if (y <30)
      ycrit2 = true;
    //Serial.print("X,Y");Serial.print(x);Serial.print(",");Serial.println(y);
    //Serial.println((xcrit1 && xcrit2 && ycrit1 && ycrit2));
    delay(100);
    if (digitalRead(BUTTON) == LOW) //abort
    {
      testResult=false;
      break;
    }
  }
  blinkTestResult(4,testResult);
}
void ledTest(){
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
void executeTest(int number){
  blinkTestNumber(number);
  switch(number){
    case 1:
      ledTest();
      break;
    case 2:
      pumpTest();
      break;
    case 3:
      solenoidTest();
      break;
    case 4:
      joystickTest();
      break;
    case 5:
      tempTest();
      break;
    case 6:
      lightTest();
      break;
    case 7:
      servoTest();
  }
}
void loop() {

  
  if (digitalRead(BUTTON) == LOW)
  {
    Serial.print("Executing Test: ");
    Serial.println(testnumber);
    delay(250);
    executeTest(testnumber);
    testnumber++;
    if (testnumber > NUMTESTS)
      testnumber = 1;

  }
  int light = analogRead(LIGHT);
  int temp = analogRead(TEMP);
  //Serial.print("LIGHT: ");Serial.print(light);Serial.print(" TEMP: ");Serial.println(temp);


}
