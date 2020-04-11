#include <Servo.h>

#define SERV1 3
#define MIN_SERVO  0
#define MAX_SERVO  180
#define STEP_SERVO 18

#define DEC_BUTTON 4
#define INC_BUTTON 12
#define DEBOUNCE_MS 100

Servo control;
void setup() {
  control.attach(SERV1);

  pinMode(INC_BUTTON,INPUT_PULLUP);
  pinMode(DEC_BUTTON,INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("PAPR Controller (WyoLum.com)");
}

int setting = MIN_SERVO;
void inc(){
  setting += STEP_SERVO;
  if(setting > MAX_SERVO) setting = MAX_SERVO;
}
void dec(){
  setting -= STEP_SERVO;
  if(setting < MIN_SERVO) setting=MIN_SERVO;
}

unsigned long last_press = 0;
void interact(){
  if(millis() - last_press > DEBOUNCE_MS){
    if(digitalRead(INC_BUTTON) == LOW){
      inc();
      Serial.println("inc");
      Serial.print(setting);
      while(digitalRead(INC_BUTTON) == LOW){
	// wait for release
      }
      last_press = millis();
    }
    if(digitalRead(DEC_BUTTON) == LOW){
      dec();
      Serial.println("dec");
      Serial.print(setting);
      while(digitalRead(DEC_BUTTON) == LOW){
	// wait for release
      }
      last_press = millis();
    }
  }
}
void loop(){
  interact();
  control.write(setting);
}
