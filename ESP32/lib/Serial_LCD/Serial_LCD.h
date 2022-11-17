#ifndef __Serial_LCD_h
#define __Serial_LCD_h

#include <Arduino.h>
#include <vector>
#include <Variables.h>

using namespace std;

// 处理类函数
void LCD_setup();
void LCD_print(String out_data);
void LCD_while();
void deal_lcd_cmd(String raw_data);
void LCD_debug(String str);
void keypad_while();

// 控制类函数
void show_confirm(String title, String center, String last_page, String cmd);
void show_tips(String title, String center, String last_page);
void back_home_page();
void show_menu();
void show_first();

#endif // __Serial_LCD_h