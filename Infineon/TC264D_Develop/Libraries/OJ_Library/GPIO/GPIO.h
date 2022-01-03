#ifndef __OJ_GPIO_H
#define __OJ_GPIO_H
#include "headfile.h"
class GPIO
{
    private:
        PIN_enum pin;           //GPIO 引脚
        GPIODIR_enum dir;       //GPIO 引脚输入输出方向选择
        uint8 dat;              //GPIO 引脚电平高低
        GPIOMODE_enum pinmode;  //GPIO 引脚模式
    public:
        GPIO ();
        GPIO (PIN_enum pin, GPIODIR_enum dir, uint8 dat, GPIOMODE_enum pinmode);
        ~GPIO ();
        void Set_Param (PIN_enum pin, GPIODIR_enum dir, uint8 dat, GPIOMODE_enum pinmode);
        void Set_Pin (PIN_enum pin);
        void Set_Dir (GPIODIR_enum dir);
        void Set_Dat (uint8 dat);
        void Set_Pinmode (GPIOMODE_enum pinmode);
        void Init ();
        void Set_PinVal (uint8 dat);
        void Pin_High ();
        void Pin_Low ();
        void Pin_Toggle ();
        uint8 Pin_Get ();
};
#endif  /*__OJ_GPIO_H*/
