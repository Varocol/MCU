#include "OJ_Library.h"
//这里包含OJ_Library.h是因为需要用到里面的库，同时也包含了MSH_FUN.h
long LED_Test (void)
{
    LED led1 = LED(P20_8, Low_level_lighting);
    led1.Init();
    led1.Pin_Toggle();
    return 0;
}

