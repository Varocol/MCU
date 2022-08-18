#ifndef __SCREEN_H
#define __SCREEN_H
#include "Variables.h"
#include "IPS_114.h"
#define Screen_IMG (uint8*)Buffer_image
#define Screen_IMG_W MT9V03X_W
#define Screen_IMG_H MT9V03X_H
void Screen_Init ();
void Screen_Show_Img ();
void Screen_Show_Running_Info();
void Screen_Draw_Line();
void Screen_Show_FPS ();
extern IPS_114 Screen;
#endif /*__SCREEN_H*/
