
#ifndef ENCODERLIB_CPE123_FALL2016_H
#define ENCODERLIB_CPE123_FALL2016_H

#include "Arduino.h"

void encoderSetup(int rightEncoderPin1, int rightEncoderPin2, int leftEncoderPin1, int leftEncoderPin2);

unsigned long rightEncoderCount();
unsigned long leftEncoderCount();

void resetEncoders();
void resetRightEncoder();
void resetLeftEncoder();

void leftEncoderISR();
void rightEncoderISR();

#endif