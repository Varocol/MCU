#ifndef __DEBUG_H
#define __DEBUG_H

#include <Arduino.h>
void debug_LCD_Task(void *parameter);
void debug_finger_Task(void *parameter);
void debug_LCD();
void debug_finger();
#endif /*__DEBUG_H*/