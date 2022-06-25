#include "Buttons.h"
Button Button1;
Button Button2;
Button Button3;
Button Button4;
//按钮初始化
void Buttons_Init ()
{
    Button1_Init();
    Button2_Init();
    Button3_Init();
    Button4_Init();
}

void Button1_Init ()
{
    //按钮1设置参数
    Button1.Set_Param(P22_0);
    //按钮1初始化
    Button1.Init();
    //按钮1链接函数
    Button1.attachClick(Button1_Click1);
    Button1.attachDoubleClick(Button1_DoubleClick1);
    Button1.attachDuringLongPress(Button1_DuringLongPress1);
    Button1.attachLongPressStart(Button1_LongPressStart1);
    Button1.attachLongPressStop(Button1_LongPressStop1);
    Button1.attachMultiClick(Button1_MultiClick1);
}
void Button2_Init ()
{
    //按钮2设置参数
    Button2.Set_Param(P22_2);
    //按钮2初始化
    Button2.Init();
    //按钮2链接函数
    Button2.attachClick(Button2_Click1);
    Button2.attachDoubleClick(Button2_DoubleClick1);
    Button2.attachDuringLongPress(Button2_DuringLongPress1);
    Button2.attachLongPressStart(Button2_LongPressStart1);
    Button2.attachLongPressStop(Button2_LongPressStop1);
    Button2.attachMultiClick(Button2_MultiClick1);
}
void Button3_Init ()
{
    //按钮3设置参数
    Button3.Set_Param(P22_1);
    //按钮3初始化
    Button3.Init();
    //按钮3链接函数
    Button3.attachClick(Button3_Click1);
    Button3.attachDoubleClick(Button3_DoubleClick1);
    Button3.attachDuringLongPress(Button3_DuringLongPress1);
    Button3.attachLongPressStart(Button3_LongPressStart1);
    Button3.attachLongPressStop(Button3_LongPressStop1);
    Button3.attachMultiClick(Button3_MultiClick1);
}
void Button4_Init ()
{
    //按钮4设置参数
    Button4.Set_Param(P22_3);
    //按钮4初始化
    Button4.Init();
    //按钮4链接函数
    Button4.attachClick(Button4_Click1);
    Button4.attachDoubleClick(Button4_DoubleClick1);
    Button4.attachDuringLongPress(Button4_DuringLongPress1);
    Button4.attachLongPressStart(Button4_LongPressStart1);
    Button4.attachLongPressStop(Button4_LongPressStop1);
    Button4.attachMultiClick(Button4_MultiClick1);
}
//所有按钮运行函数
void Buttons_Tick ()
{
    Button1_Tick();
    Button2_Tick();
    Button3_Tick();
    Button4_Tick();
}
//按钮1运行函数
void Button1_Tick ()
{
    Button1.tick();
}
//按钮2运行函数
void Button2_Tick ()
{
    Button2.tick();
}
//按钮3运行函数
void Button3_Tick ()
{
    Button3.tick();
}
//按钮4运行函数
void Button4_Tick ()
{
    Button4.tick();
}
