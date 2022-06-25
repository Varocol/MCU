#include "Sinal_Light.h"
LED Sinal_Light;

/*
 * @brief       工作信号灯模块初始化函数
 * @return      void
 */
void Sinal_Light_Init ()
{
    Sinal_Light.Set_Param(P20_8, Low_level_lighting);
    Sinal_Light.Init();
}

/*
 * @brief       工作信号灯模块初始化函数
 * @return      void
 */
void Sinal_Light_On ()
{
    Sinal_Light.On();
}

/*
 * @brief       工作信号灯模块初始化函数
 * @return      void
 */
void Sinal_Light_Off ()
{
    Sinal_Light.Off();
}

/*
 * @brief       工作信号灯模块初始化函数
 * @return      void
 */
void Sinal_Light_Toggle ()
{
    Sinal_Light.Toggle();
}
