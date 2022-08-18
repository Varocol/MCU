#ifndef __BSP_SERVO_H
#define __BSP_SERVO_H
#include "Servo.h"
#include "Variables.h"
#include "platform.h"
void Servo_Init();
void Servo_Control();
void Get_CDF_Table();
void Get_Mid_Bias ();
void MidBias_FitTurnR();
float GetTargetTurnAngleSpeed(float car_speed, float steer_R);
#endif /*__BSP_SERVO_H*/
