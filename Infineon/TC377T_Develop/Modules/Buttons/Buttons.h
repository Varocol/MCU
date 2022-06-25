#ifndef __BUTTONS_H
#define __BUTTONS_H
#include "Libraries.h"
#include "Button_Function.h"
//TC377T按钮模块
//参数(按钮命名顺序为从上往下)：
//      按钮1
//      引脚：P22_0
//      模式：activeLow (按下触发)
//      上拉：是
//
//      按钮2
//      引脚：P22_2
//      模式：activeLow (按下触发)
//      上拉：是
//
//      按钮3
//      引脚：P22_1
//      模式：activeLow (按下触发)
//      上拉：是
//
//      按钮4
//      引脚：P22_3
//      模式：activeLow (按下触发)
//      上拉：是

//按钮初始化
void Buttons_Init ();
void Button1_Init ();
void Button2_Init ();
void Button3_Init ();
void Button4_Init ();
//按钮运行
void Buttons_Tick ();
void Button1_Tick ();
void Button2_Tick ();
void Button3_Tick ();
void Button4_Tick ();

#endif /*__BUTTONS_H*/
