#include "OJ_Library.h"
//�������OJ_Library.h����Ϊ��Ҫ�õ�����Ŀ⣬ͬʱҲ������MSH_FUN.h
long LED_Test (void)
{
    LED led1 = LED(P20_8, Low_level_lighting);
    led1.Init();
    led1.Pin_Toggle();
    return 0;
}

