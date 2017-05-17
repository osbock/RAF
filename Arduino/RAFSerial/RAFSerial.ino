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
void fire(){
    Serial.println("fire!");
    digitalWrite(RED,HIGH);
    digitalWrite(MOSFET,HIGH);
    delay(100);
    digitalWrite(MOSFET,LOW);
    digitalWrite(RED,LOW);

}
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
        }else if (!strcmp(buffer,"F")){
	fire();
      }else if (numscanned == 2){
        if (!strcmp(buffer,"A")){
          Serial.print("azimuth "); Serial.println(degrees);
          xServo.write(degrees);
        }
        if (!strcmp(buffer,"E")){
          Serial.print("elevation "); Serial.println(degrees);
          yServo.write(degrees);
        }
      }
    }
  }
  }
}
