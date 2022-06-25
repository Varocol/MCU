#include "LED.h"
/*
 * @brief       LED空构造方法
 * @param       void
 * @return      null
 */
LED::LED ()
{
}

/*
 * @brief       LED带参构造方法
 * @param       pin         用戶需要操作的引脚
 * @param       mode        LED电平极性
 * @return      null
 */
LED::LED (PIN_enum pin, LED_Lighting_Mode mode)
{
    Set_Param(pin, mode);
}

/*
 * @brief       LED析构方法
 * @param       void
 * @return      null
 */
LED::~LED ()
{
}

/*
 * @brief       LED设置参数方法
 * @param       pin         用戶需要操作的引脚
 * @param       mode        LED电平极性
 * @return      void
 */
void LED::Set_Param (PIN_enum pin, LED_Lighting_Mode mode)
{
    GPIO::Set_Param(pin, GPO, 1, PUSHPULL);
    Set_Mode(mode);
}

/*
 * @brief       LED设置激活模式
 * @param       mode        LED电平极性
 * @return      void
 */
void LED::Set_Mode (LED_Lighting_Mode mode)
{
    this->mode = mode;
}

/*
 * @brief       LED初始化
 * @param       null
 * @return      void
 */
void LED::Init ()
{
    GPIO::Init();
    On();
}

/*
 * @brief       LED灯亮
 * @param       null
 * @return      void
 */
void LED::On ()
{
    if (mode == Low_level_lighting)
    {
        Pin_Low();
    }
    else if (mode == High_level_lighting)
    {
        Pin_High();
    }
}

/*
 * @brief       LED灯灭
 * @param       null
 * @return      void
 */
void LED::Off ()
{
    if (mode == Low_level_lighting)
    {
        Pin_High();
    }
    else if (mode == High_level_lighting)
    {
        Pin_Low();
    }
}

/*
 * @brief       LED灯反转
 * @param       null
 * @return      void
 */
void LED::Toggle()
{
    Pin_Toggle();
}
