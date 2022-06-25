#ifndef __SCREEN_H
#define __SCREEN_H
#include "IPS_114.h"
void Screen_Init ();
void Screen_Show_Img (uint8*, uint16, uint16);
extern IPS_114 Screen;
#endif /*__SCREEN_H*/
