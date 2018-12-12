#include <CPE123_Fall16.h>
#include <EncoderLib123_Fall2016.h>


// Define your pins

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

const int IRThreshold = 600;
int mSpeed = 200;

const int motor1L = 6;
const int motor2L = 7;
const int motor1R = 8;
const int motor2R = 9;
const int StartButtonPin = 4;
const int KillSwitchTogglepin = 5;

// Create your hardware

Button StartButton(StartButtonPin);
Button KillSwitchToggle(KillSwitchTogglepin);
Led CenterLed(centerledpin);
Led RightLed(rightledpin);
Led LeftLed(leftledpin);
Led RightMostLed(rightmostledpin);
Led LeftMostLed(leftmostledpin);



void setup() {
  Serial.begin(9600);
  MotorSetup(6,7,8,9);
  Serial.println("Gimme a line and hit that button");
  while (StartButton.wasPushed() != true){}
  delay(1000);
  Serial.println("Buton Pushed");
}


void MotorSetup(int motor1L, int motor2L, int motor1R, int motor2R)
{
  pinMode(motor1L, OUTPUT);
  pinMode(motor2L, OUTPUT);
  pinMode(motor1R, OUTPUT);
  pinMode(motor2R, OUTPUT); 
}

void loop(){
  Control();
}

void Control()
{
//  Serial.println("In Control");
  if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) > IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {
//    Serial.println(analogRead(irCenterPin));
//    Serial.println("Center Pin over Black Line");
    CenterLed.on();
    RightLed.off();
    RightMostLed.off();
    LeftLed.off();
    LeftMostLed.off();
    RightMotorForward(150);
    LeftMotorForward(150);     
  }
  else if ((analogRead(irLeftPin) > IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {
//    Serial.println(analogRead(irLeftPin));    
//    Serial.println("Left Pin over Black Line");
    LeftLed.on();
    LeftMostLed.off();
    RightLed.off();
    RightMostLed.off();
    CenterLed.off();
    LeftMotorBackward(50);
    RightMotorForward(150);
//    delay(250);
  }
  else if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) > IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {
//    Serial.println(analogRead(irRightPin));    
    RightLed.on();
    RightMostLed.off();
    LeftLed.off();
    LeftMostLed.off();
    CenterLed.off();
    LeftMotorForward(150);
    RightMotorBackward(50);
//    delay(250);
  }
  else if ((analogRead(irLeftPin) > IRThreshold) && (analogRead(irCenterPin) > IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {
//    Serial.println(analogRead(irRightPin));    
    RightLed.off();
    RightMostLed.off();
    LeftLed.on();
    LeftMostLed.off();
    CenterLed.on();
    LeftMotorBackward(50);
    RightMotorForward(150);
//    delay(250);
  }
  else if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) > IRThreshold) && (analogRead(irRightPin) > IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {
//    Serial.println(analogRead(irRightPin));    
    RightLed.on();
    RightMostLed.off();
    LeftLed.off();
    LeftMostLed.off();
    CenterLed.on();
    LeftMotorForward(150);
    RightMotorBackward(50);
//    delay(250);
  }
  else if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) > IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) > IRThreshold))
  {
//    Serial.println(analogRead(irRightPin));    
    RightLed.on();
    RightMostLed.on();
    LeftLed.off();
    LeftMostLed.off();
    CenterLed.off();
    LeftMotorForward(200);
    RightMotorBackward(50);
//    delay(250);
  }
  else if ((analogRead(irLeftPin) > IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) > IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {
//    Serial.println(analogRead(irRightPin));    
    RightLed.off();
    RightMostLed.off();
    LeftLed.on();
    LeftMostLed.on();
    CenterLed.off();
    LeftMotorBackward(50);
    RightMotorForward(200);
//    delay(250);
  }
  else if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) > IRThreshold))
  {
//    Serial.println(analogRead(irRightPin));    
    RightLed.off();
    RightMostLed.on();
    LeftLed.off();
    LeftMostLed.off();
    CenterLed.off();
    LeftMotorForward(250);
    RightMotorBackward(50);
//    delay(250);
  }
  else if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) > IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {
//    Serial.println(analogRead(irRightPin));    
    RightLed.off();
    RightMostLed.off();
    LeftLed.off();
    LeftMostLed.on();
    CenterLed.off();
    LeftMotorBackward(50);
    RightMotorForward(250);
//    delay(250);
  }
  else if ((analogRead(irLeftPin) > IRThreshold) && (analogRead(irCenterPin) > IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) > IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {
//    Serial.println(analogRead(irRightPin));    
    RightLed.off();
    RightMostLed.off();
    LeftLed.on();
    LeftMostLed.on();
    CenterLed.on();
    LeftMotorBackward(100);
    RightMotorForward(150);
//    delay(1500);
  }
  else if ((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) > IRThreshold) && (analogRead(irRightPin) > IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) > IRThreshold))
  {
//    Serial.println(analogRead(irRightPin));    
    RightLed.on();
    RightMostLed.on();
    LeftLed.off();
    LeftMostLed.off();
    CenterLed.on();
    LeftMotorForward(150);
    RightMotorBackward(100);
//    delay(1500);
  }
  if (KillSwitchToggle.wasPushed())
  {
    while (KillSwitchToggle.isPushed() != true)
  {
    RobotStop();
  }
  }
  if((analogRead(irLeftPin) < IRThreshold) && (analogRead(irCenterPin) < IRThreshold) && (analogRead(irRightPin) < IRThreshold) && (analogRead(irLeftMostPin) < IRThreshold) && (analogRead(irRightMostPin) < IRThreshold))
  {
    RobotStop();
  }
//  else
//  {
//    LeftMotorForward(LeftAdjustedSpeed);
//    RightMotorForward(RightAdjustedSpeed);
//  }
  delay(0);
}

void RobotStop()
{
  LeftMotorStop();
  RightMotorStop();
}
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
