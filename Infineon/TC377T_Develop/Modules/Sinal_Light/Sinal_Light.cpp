#include "Sinal_Light.h"
LED Sinal_Light;

/*
 * @brief       �����źŵ�ģ���ʼ������
 * @return      void
 */
void Sinal_Light_Init ()
{
    Sinal_Light.Set_Param(P20_8, Low_level_lighting);
    Sinal_Light.Init();
}

/*
 * @brief       �����źŵ�ģ���ʼ������
 * @return      void
 */
void Sinal_Light_On ()
{
    Sinal_Light.On();
}

/*
 * @brief       �����źŵ�ģ���ʼ������
 * @return      void
 */
void Sinal_Light_Off ()
{
    Sinal_Light.Off();
}

/*
 * @brief       �����źŵ�ģ���ʼ������
 * @return      void
 */
void Sinal_Light_Toggle ()
{
    Sinal_Light.Toggle();
}
