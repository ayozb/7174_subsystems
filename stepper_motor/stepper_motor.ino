//Drive a stepper motor continously

#include <AccelStepper.h>

#define HALFSTEP 8

#define motorPin1  3     // IN1 on the stepper driver
#define motorPin2  4     // IN2 on the stepper driver
#define motorPin3  5     // IN3 on the stepper driver
#define motorPin4  6     // IN4 on the stepper driver

AccelStepper stepper(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  //Don't increase the max speed any more
  //could damage arduino if too much power
  //is drawn
  stepper.setMaxSpeed(400.0);
  stepper.setSpeed(400); 
  //if plugging the stepper motor in effects the lights/makes them dimmer
  //run power from 5V2A on the VRM to the stepper controller
  //instead of powering it from the arduino
}

void loop() {
    stepper.runSpeed();
}
