#ifndef __UNCLOCK_SERVO_h
#define __UNCLOCK_SERVO_h

#include <Arduino.h>
#include <ESP32Servo.h>
#include <Variables.h>

void unclock_servo_setup();
void unclock_servo_open();

extern Servo unclock_servo;

#endif // __UNCLOCK_SERVO_h