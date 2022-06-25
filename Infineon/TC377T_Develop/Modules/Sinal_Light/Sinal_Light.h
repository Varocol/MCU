#ifndef __SINAL_LIGHT_H
#define __SINAL_LIGHT_H
#include "Libraries.h"

//TC377T工作信号灯模块
//参数：
//      引脚：P20_8
//      模式：Low_level_lighting

void Sinal_Light_Init ();
void Sinal_Light_On ();
void Sinal_Light_Off ();
void Sinal_Light_Toggle ();
#endif /*__SINAL_LIGHT_H*/
