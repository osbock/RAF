//  Joystick moves the altitude / azimuth servos, but does not define
//  an absolute position.  This makes it easy to pick/refine
//  an aiming point.
//
//  The pump and solenoid timings are the same as in RAF2, but
//  you might want to adjust them as appropriate for the size
//  of your pump/reservoir/launchtube.

//  Change the next few #define's to suit your needs
#define AZIMUTH_HOME  90
#define AZIMUTH_DIRECTION 1 // Make -1 if you need to reverse azimuth movements
#define ALTITUDE_HOME  0
#define ALTITUDE_DIRECTION -1 // Make 1 if you need to reverse altitude movements
#define SOLENOID_FIRE_DURATION_MILLIS 300
#define PUMP_RECHARGE_MILLIS 3000
#define PUMP_INITIAL_CHARGE_MILLIS 10000
#define NULL_ZONE 50
#define JOY_MID 512

#include <Servo.h>

#define SOLENOID 2
#define PUMP 9
#define BUTTON 12
#define JOYX A0
#define JOYY A1
#define SERV1 3
#define SERV2 5

Servo azimuth;
Servo altitude;

void setup() {
  Serial.begin(115200);
  Serial.println("Ready Aim Fire!");

  //  Setup our fire button so it is off by default
  pinMode(BUTTON, INPUT_PULLUP);

  //  Setup the altitude/azimuth servos
  azimuth.attach(SERV1);
  azimuth.write(AZIMUTH_HOME);
  altitude.attach(SERV2);
  altitude.write(ALTITUDE_HOME);

  //  Setup the solenoid
  pinMode(SOLENOID, OUTPUT);
  digitalWrite(SOLENOID, LOW);

  //  Setup the pump, and run it for 10 seconds to prime reservoir
  pinMode(PUMP, OUTPUT);
  digitalWrite(PUMP, HIGH);
  delay(PUMP_INITIAL_CHARGE_MILLIS);
  digitalWrite(PUMP, LOW);
}

/*
   Utility function for updating a servo to a new value.
   This will be called twice (once for altitude, once for azimuth).

   Avoids jitter by allowing a "dead zone" near the joystick center.
   You can change the width of the dead zone with the NULL_ZONE #define
*/
int update_servo(int value, int pin, Servo servo, int high, int inversion) {
  int delta = analogRead(pin) - JOY_MID;
  if (abs(delta) > NULL_ZONE) {
    Serial.print("Incoming value is:  ");
    Serial.println(value);
    Serial.print("Current raw delta is:  ");
    Serial.println(delta);
    //  Upper bound of (map) is never hit, so we need to do -N, N+1 below...
    delta = map(delta, -JOY_MID, JOY_MID, -3, 4);
    delta *= inversion;
    Serial.print("Current mapped delta is:  ");
    Serial.println(delta);
    value = constrain(value + delta, 0, high);
    Serial.print("New value is:  ");
    Serial.println(value);
    servo.write(value);
  }
  return value;
}

/*
   Detects a request for launch, then
   fires the solenoid and recharges the air
   reservoir as required.
*/
void check_for_launch() {
  if (digitalRead(BUTTON) != LOW) {
    return;
  }

  Serial.println("fire!");

  //  Trigger solenoid, wait, then clear solenoid
  digitalWrite(SOLENOID, HIGH);
  delay(SOLENOID_FIRE_DURATION_MILLIS);
  digitalWrite(SOLENOID, LOW);

  //  Recharge the pump as required
  digitalWrite(PUMP, HIGH);
  delay(PUMP_RECHARGE_MILLIS);
  digitalWrite(PUMP, LOW);
}

/*
   Our main loop.  Not much to this one.
   Simply check for a launch, set the servo positions,
   delay for 1/50th of a second, and repeat.
*/
int current_azimuth = AZIMUTH_HOME;
int current_altitude = ALTITUDE_HOME;
void loop() {
  check_for_launch();
  current_azimuth = update_servo(current_azimuth, JOYX, azimuth, 180, AZIMUTH_DIRECTION);
  current_altitude = update_servo(current_altitude, JOYY, altitude, 90, ALTITUDE_DIRECTION);
  delay(20);
}
