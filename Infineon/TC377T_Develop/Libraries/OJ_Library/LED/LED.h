#ifndef __OJ_LED_H
#define __OJ_LED_H
#include "GPIO.h"
typedef enum
{
    //低电平触发
    Low_level_lighting = 0,
    //高电平触发
    High_level_lighting
}LED_Lighting_Mode;

class LED :  public GPIO
{
    private:
        LED_Lighting_Mode mode = High_level_lighting;   //灯触发模式
    public:
        LED ();
        ~LED ();
        LED(PIN_enum pin,LED_Lighting_Mode mode);
        void Set_Param(PIN_enum pin,LED_Lighting_Mode mode);
        void Set_Mode(LED_Lighting_Mode mode);
        void Init ();
        void On();
        void Off();
        void Toggle();
};

#endif  /*__OJ_LED_H*/
