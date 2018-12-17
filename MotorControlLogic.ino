#include <CPE123_Fall16.h>
#include <EncoderLib123_Fall2016.h>


// Define your pins for Arduino Configuration


// Positions for IR Sensors are as follows LMP, LP, C, RP, RMP
const int irRightPin = A15;
const int irCenterPin = A14;
const int irLeftPin = A13;
const int irRightMostPin = A12;
const int irLeftMostPin = A11;
const int centerledpin = 41;
const int rightledpin = 43;
const int leftledpin = 39;
const int rightmostledpin = 45;
const int leftmostledpin = 47;

int RightAdjustedSpeed;
int LeftAdjustedSpeed;

const int IRThreshold = 600;  // Threshold used for determining if significant IR change
int mSpeed = 200;             // Speed Used for Motors

// Pins attached to motor servos
const int motor1L = 6;
const int motor2L = 7;
const int motor1R = 8;
const int motor2R = 9;

// Pins to Start Stop Process
const int StartButtonPin = 4;
const int KillSwitchTogglepin = 5;

// Declaration of Hardware
Button StartButton(StartButtonPin);
Button KillSwitchToggle(KillSwitchTogglepin);

// FeedBack LEDS for determining when a sensor meets the threshold define above
// Useful for troubleshooting with test line beneath sensors
Led CenterLed(centerledpin);
Led RightLed(rightledpin);
Led LeftLed(leftledpin);
Led RightMostLed(rightmostledpin);
Led LeftMostLed(leftmostledpin);

// Enter Setup Configuration
void setup() {
  Serial.begin(9600);  // Load Specific Baud Rate of Serial Output
  MotorSetup(6,7,8,9); // Launch Motor Setup for specified pins
  Serial.println("Gimme a line and hit that button");
  while (StartButton.wasPushed() != true){}
  delay(1000);
  Serial.println("Buton Pushed");
}

// Launch Motor Configuration
void MotorSetup(int motor1L, int motor2L, int motor1R, int motor2R)
{
  pinMode(motor1L, OUTPUT);
  pinMode(motor2L, OUTPUT);
  pinMode(motor1R, OUTPUT);
  pinMode(motor2R, OUTPUT); 
}

// Enter Main Process Loop
void loop(){
  Control();
}

void Control()
{
  // Condition for Center IR Sensor over Black Line, correctly oriented, continue forward both motor same power
  if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) > IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {
    // Display FeedBack LED's, very useful for troubleshooting IR Sensor path detection
    CenterLed.on();
    RightLed.off();
    RightMostLed.off();
    LeftLed.off();
    LeftMostLed.off();
    RightMotorForward(150);
    LeftMotorForward(150);
    // No need for delay here, keep pushing forward
  }
  
  // Condition for Left IR Sensor over Black Line, must adjust slightly left
  else if ((analogRead(irLeftPin) > IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {
    // Display FeedBack LED's, very useful for troubleshooting IR Sensor path detection
    LeftLed.on();
    LeftMostLed.off();
    RightLed.off();
    RightMostLed.off();
    CenterLed.off();
    // Condition for Right IR Sensor AND RightMost IR Sensor over Black Line, must adjust slightly left
    LeftMotorBackward(50); // This is a slight turn left
    RightMotorForward(150);
// Experimenting with Delays, may be necessary to avoid quick corrections and allow the robot to stray slightly before adjusting
//    delay(250);
  }
  
  // Condition for Right IR Sensor over Black Line, must adjust slightly right
  else if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) > IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {    
    // Display FeedBack LED's, very useful for troubleshooting IR Sensor path detection
    RightLed.on();
    RightMostLed.off();
    LeftLed.off();
    LeftMostLed.off();
    CenterLed.off();
    // Send power to the motors, Can turn right or spin in place counter clock/clock wise depending
    LeftMotorForward(150); // This is a slight turn right
    RightMotorBackward(50);
// Experimenting with Delays, may be necessary to avoid quick corrections and allow the robot to stray slightly before adjusting
//    delay(250);
  }
  // Condition for Left IR Sensor AND Center IR Sensor over Black Line, must adjust slightly left
  else if ((analogRead(irLeftPin) > IRThreshold) && (analogRead(irCenterPin) > IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {   
    // Display FeedBack LED's, very useful for troubleshooting IR Sensor path detection
    RightLed.off();
    RightMostLed.off();
    LeftLed.on();
    LeftMostLed.off();
    CenterLed.on();
    // Send power to the motors, Can turn right or spin in place counter clock/clock wise depending
    LeftMotorBackward(50); // This is a slight turn left
    RightMotorForward(150);
// Experimenting with Delays, may be necessary to avoid quick corrections and allow the robot to stray slightly before adjusting
//    delay(250);
  }
  // Condition for Right IR Sensor AND Center IR Sensor over Black Line, must adjust slightly right
  else if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) > IRThreshold) && (analogRead(irRightPin) > IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  { 
    // Display FeedBack LED's, very useful for troubleshooting IR Sensor path detection
    RightLed.on();
    RightMostLed.off();
    LeftLed.off();
    LeftMostLed.off();
    CenterLed.on();
    // Send power to the motors, Can turn right or spin in place counter clock/clock wise depending
    LeftMotorForward(150); // This is a slight turn right
    RightMotorBackward(50);
// Experimenting with Delays, may be necessary to avoid quick corrections and allow the robot to stray slightly before adjusting
//    delay(250);
  }
  // Condition for Right IR Sensor AND RightMost IR Sensor over Black Line, must adjust slightly right
  else if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) > IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) > IRThreshold))
  { 
    // Display FeedBack LED's, very useful for troubleshooting IR Sensor path detection
    RightLed.on();
    RightMostLed.on();
    LeftLed.off();
    LeftMostLed.off();
    CenterLed.off();
    // Send power to the motors, Can turn right or spin in place counter clock/clock wise depending
    LeftMotorForward(200); // This is a turn right
    RightMotorBackward(50);
// Experimenting with Delays, may be necessary to avoid quick corrections and allow the robot to stray slightly before adjusting
//    delay(250);
  }
  // Condition for Left IR Sensor AND LeftMost IR Sensor over Black Line, must adjust slightly left
  else if ((analogRead(irLeftPin) > IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) > IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {  
    // Display FeedBack LED's, very useful for troubleshooting IR Sensor path detection
    RightLed.off();
    RightMostLed.off();
    LeftLed.on();
    LeftMostLed.on();
    CenterLed.off();
    // Send power to the motors, Can turn right or spin in place counter clock/clock wise depending
    LeftMotorBackward(50); // This is a turn left
    RightMotorForward(200);
// Experimenting with Delays, may be necessary to avoid quick corrections and allow the robot to stray slightly before adjusting
//    delay(250);
  }
  
  // Condition for RightMost IR Sensor over Black Line, must adjust majorly right
  else if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) > IRThreshold))
  { 
    // Display FeedBack LED's, very useful for troubleshooting IR Sensor path detection
    RightLed.off();
    RightMostLed.on();
    LeftLed.off();
    LeftMostLed.off();
    CenterLed.off();
    // Send power to the motors, Can turn right or spin in place counter clock/clock wise depending
    LeftMotorForward(250); // This is a major turn right
    RightMotorBackward(50);
// Experimenting with Delays, may be necessary to avoid quick corrections and allow the robot to stray slightly before adjusting
//    delay(250);
  }
  // Condition for LeftMost IR Sensor over Black Line, must adjust majorly left
  else if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) > IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {
    // Display FeedBack LED's, very useful for troubleshooting IR Sensor path detection 
    RightLed.off();
    RightMostLed.off();
    LeftLed.off();
    LeftMostLed.on();
    CenterLed.off();
    // Send power to the motors, Can turn right or spin in place counter clock/clock wise depending
    LeftMotorBackward(50); // This is a major turn right
    RightMotorForward(250);
// Experimenting with Delays, may be necessary to avoid quick corrections and allow the robot to stray slightly before adjusting
//    delay(250);
  }
  // Condition for Center IR Sensor AND Left IR Sensor AND LeftMost IR Sensor over Black Line, must adjust left
  // This can result when approaching 90 degree bend left
  else if ((analogRead(irLeftPin) > IRThreshold) && (analogRead(irCenterPin) > IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) > IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {  
    // Display FeedBack LED's, very useful for troubleshooting IR Sensor path detection
    RightLed.off();
    RightMostLed.off();
    LeftLed.on();
    LeftMostLed.on();
    CenterLed.on();
    // Send power to the motors, Can turn right or spin in place counter clock/clock wise depending
    LeftMotorBackward(100); // This is a counter-clockwise spin in place maneuver
    RightMotorForward(150);
// Experimenting with Delays, may be necessary to avoid quick corrections and allow the robot to stray slightly before adjusting
//    delay(1500);
  }
  // Condition for Center IR Sensor AND Right IR Sensor AND RightMost IR Sensor over Black Line, must adjust right
  // This can result when approaching 90 degree bend right
  else if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) > IRThreshold) && (analogRead(irRightPin) > IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) > IRThreshold))
  { 
    // Display FeedBack LED's, very useful for troubleshooting IR Sensor path detection
    RightLed.on();
    RightMostLed.on();
    LeftLed.off();
    LeftMostLed.off();
    CenterLed.on();
    // Send power to the motors, Can turn right or spin in place counter clock/clock wise depending
    LeftMotorForward(150); // This is a clockwise spin in place maneuver
    RightMotorBackward(100);
// Experimenting with Delays, may be necessary to avoid quick corrections and allow the robot to stray slightly before adjusting    
//    delay(1500);
  }
  
// KillSwitch is pressed, call RobotStop
  if (KillSwitchToggle.wasPushed())
  {
    while (KillSwitchToggle.isPushed() != true)
  {
    // Stop the robot, manual override
    RobotStop();
  }
  }
  // Condition for Black Line under ZERO IR Sensors, path no longer visible, stop robot
  if((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {
    // Stop the robot, keep it from straying further from path
    RobotStop();
  }

  delay(0);
}

// Kill The Robot
// Used when path is no longer visible under any IR Sensors, also
//   when the KillSwitch Button is pressed
void RobotStop()
{
  LeftMotorStop();
  RightMotorStop();
}

// Motor Control Helper Functions
void LeftMotorForward(int LeftAdjustedSpeed)
{
  MotorControl(motor1L, motor2L, LeftAdjustedSpeed);
}
void RightMotorForward(int RightAdjustedSpeed)
{
  MotorControl(motor1R, motor2R, RightAdjustedSpeed);
}
void LeftMotorBackward(int LeftAdjustedSpeed)
{
  MotorControl(motor2L, motor1L, LeftAdjustedSpeed);
}
void RightMotorBackward(int RightAdjustedSpeed)
{
  MotorControl(motor2R, motor1R, RightAdjustedSpeed);
}
void LeftMotorStop()
{
  MotorControl(motor1L, motor2L, 0);
  MotorControl(motor1R, motor2R, 0);
}
void RightMotorStop()
{
  MotorControl(motor1L, motor2L, 0);
  MotorControl(motor1R, motor2R, 0);
}
void MotorControl(int pin1, int pin2, int mSpeed)
{
  analogWrite(pin1, mSpeed);
  analogWrite(pin2, 0);
}
