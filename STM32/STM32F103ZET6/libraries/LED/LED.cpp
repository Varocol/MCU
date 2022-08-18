#include "LED.h"
/**
 * @brief   LED-空构造方法
 * @param   None
 * @return  None
 */
LED::LED()
{
}

/**
 * @brief   LED-带参构造方法
 * @param   pin         用户需要操作的引脚
 * @param   mode        LED电平极性
 * @return  None
 */
LED::LED(PIN_enum pin, LED_Lighting_Mode mode)
{
    Set_Param(pin, mode);
}

/**
 * @brief   LED-析构方法
 * @param   None
 * @return  None
 */
LED::~LED()
{
}

/**
 * @brief   LED-设置参数方法
 * @param   pin         用户需要操作的引脚
 * @param   mode        LED电平极性
 * @return  None
 */
void LED::Set_Param(PIN_enum pin, LED_Lighting_Mode mode)
{
    Set_GPIO_Param(pin);
    Set_Mode(mode);
}

/**
 * @brief   LED-设置激活模式
 * @param   mode        LED电平极性
 * @return  None
 */
void LED::Set_Mode(LED_Lighting_Mode mode)
{
    this->mode = mode;
}

/**
 * @brief   LED-初始化
 * @param   None
 * @return  None
 */
void LED::Init()
{
    OUT_MODE();
    On();
}

/**
 * @brief   LED-灯亮
 * @param   None
 * @return  None
 */
void LED::On()
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

/**
 * @brief  LED-灯灭
 * @param  None
 * @return None
 */
void LED::Off()
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

/**
 * @brief  LED-灯反转
 * @param  None
 * @return None
 */
void LED::Toggle()
{
    Pin_Toggle();
}
