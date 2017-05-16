 #include <Servo.h>
 #include <string.h>
 
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
  yServo.write(110);
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

  // process serial commands
  // A XXX - Azimuth degrees 
  // E XXX - Elevation degrees
  // F - Fire
  // RL -- read light sensor
  // RT -- read temp sensor
  if (Serial.available()){
    String command = Serial.readStringUntil('\r');
    const char *command_c_str = command.c_str();
    Serial.println(command_c_str);
    char buffer[100];
    int degrees;
    if (command.length() <100){
      int numscanned = sscanf(command_c_str,"%s %3d", buffer, &degrees);
      if (numscanned == 1){
        if(!strcmp(buffer,"RL")){
          int light = analogRead(LIGHT);
          Serial.println (light);
        }else
        if (!strcmp(buffer,"RT")){
           int temp = analogRead(TEMP);
          Serial.println (temp);       
        }
      }else if (numscanned == 2){
        if (!strcmp(buffer,"A")){
          xServo.write(degrees);
        }
        if (!strcmp(buffer,"E")){
          yServo.write(degrees);
        }
      }
    }
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
  
  int temp = analogRead(TEMP);
  //Serial.print("LIGHT: ");Serial.print(light);Serial.print(" TEMP: ");Serial.println(temp);
  int x = analogRead(JOYX);
  int y = analogRead(JOYY);

 /* if(abs(lastx-x)>2)
  {
    //Serial.print("X: ");Serial.println(x);
    xServo.write(x/4);
    lastx =x;
  }
  if(abs(lasty-y)>2)
  {

    // Y is also around 450-500 but y axis is at 90 essentially at rest,  so map forward and back;
    //Serial.print("Y: ");Serial.println(y);
    if (y < 480)
    {
      yServo.write(map(y,0,480,10,110));
    }else
      yServo.write(map(y,480,1023,110,150));
    lasty = y;
  }
  */
}
