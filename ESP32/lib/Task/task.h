#ifndef __TASK_H
#define __TASK_H
#include <Arduino.h>
#include <Variables.h>
void Task_Die();
void keypad_Task(void *parameter);
void LCD_Task(void *parameter);
void Network_Task(void *parameter);
void Task_int();
#endif // __TASK_H