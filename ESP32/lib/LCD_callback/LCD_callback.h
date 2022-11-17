#ifndef __LCD_CALLBACK_h
#define __LCD_CALLBACK_h

#include <Arduino.h>
#include "Serial_LCD.h"

void add_user(String school_id);
void delete_user(String school_id);
void set_admin(String school_id);
void change_user_password(String password);
void change_admin_password(String password);
void unlock(String password);
void Return_to_factory();
void Show_finger_list();
#endif // __LCD_CALLBACK_h