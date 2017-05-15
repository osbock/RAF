 #include <Servo.h>
#define MOSFET 2
#define BUTTON 12
#define JOYX A0
#define JOYY A1
#define SERV1 3
#define SERV2 5
#define SERV3 6
#define LIGHT A2
#define TEMP A3
#define RED 11
#define GREEN 10
#define BLUE 9

Servo xServo,yServo;
void setup() {
  Serial.begin(115200);
  xServo.attach(SERV1);
  yServo.attach(SERV2);
  yServo.write(30);
  pinMode(MOSFET,OUTPUT);
  digitalWrite(MOSFET,LOW);

 pinMode(RED,OUTPUT);
 pinMode(GREEN, OUTPUT);
 pinMode(BLUE,OUTPUT);
 pinMode(BUTTON,INPUT_PULLUP);

 for (int i = 9; i < 12; i++)
 {
  digitalWrite(i,HIGH);
  delay(1000);
  digitalWrite(i,LOW);
 }
 
}

int lastx;
int lasty;

void loop() {

  if (Serial.available())
  {
    char c = Serial.read();
    if (c == '0')
      yServo.write(0);
    if (c == '9')
      yServo.write(90);
     if(c == '8')
      yServo.write(180);
  }

  if (digitalRead(BUTTON) == LOW)
  {
    Serial.println("fire!");
    digitalWrite(RED,HIGH);
    digitalWrite(MOSFET,HIGH);
    delay(1000);
    digitalWrite(MOSFET,LOW);
    digitalWrite(RED,LOW);
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

    // Y is also around 450-500 but y axis is at 0 essentially at rest,  so ignore anything < 400; 
    // it can only really tilt down
    Serial.print("Y: ");Serial.println(y);
    if (y < 480)
    {
      yServo.write(map(y,0,480,0,30));
    }else
      yServo.write(map(y,480,1023,30,180));
    lasty = y;
  }
}
