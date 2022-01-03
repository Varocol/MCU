#include "GPIO.h"
/*
 * @brief       GPIO空构造方法
 * @param       void
 * @return      null
 */
GPIO::GPIO ()
{

}

/*
 * @brief       GPIO析构方法
 * @param       void
 * @return      null
 */
GPIO::~GPIO ()
{

}

/*
 * @brief       GPIO带参构造方法
 * @param       pin         用戶需要操作的引脚
 * @param       dir         引脚输入输出方向
 * @param       dat         引脚高低 (如果dir为GPI则dat随便输入)
 * @param       pinmode     引脚的模式
 * @return      null
 */
GPIO::GPIO (PIN_enum pin, GPIODIR_enum dir, uint8 dat, GPIOMODE_enum pinmode)
{
    Set_Param(pin, dir, dat, pinmode);
}

/*
 * @brief       GPIO设置参数方法
 * @param       pin         用戶需要操作的引脚
 * @param       dir         引脚输入输出方向
 * @param       dat         引脚高低电平 (dir为GPO)有效
 * @param       pinmode     引脚的模式
 * @return      void
 */
void GPIO::Set_Param (PIN_enum pin, GPIODIR_enum dir, uint8 dat, GPIOMODE_enum pinmode)
{
    Set_Pin(pin);
    Set_Dir(dir);
    Set_Dat(dat);
    Set_Pinmode(pinmode);
}

/*
 * @brief       GPIO设置需要被操作的引脚
 * @param       pin         用戶需要操作的引脚
 * @return      void
 */
void GPIO::Set_Pin (PIN_enum pin)
{
    this->pin = pin;
}

/*
 * @brief       GPIO设置引脚输入输出方向
 * @param       dir         引脚输入输出方向
 * @return      void
 */
void GPIO::Set_Dir (GPIODIR_enum dir)
{
    this->dir = dir;
}

/*
 * @brief       GPIO设置引脚高低电平
 * @param       dat         引脚高低电平 (dir为GPO)有效
 * @return      void
 */
void GPIO::Set_Dat (uint8 dat)
{
    this->dat = dat;
}

/*
 * @brief       GPIO设置引脚的模式
 * @param       pinmode     引脚的模式
 * @return      void
 */
void GPIO::Set_Pinmode (GPIOMODE_enum pinmode)
{
    this->pinmode = pinmode;
}

/*
 * @brief       GPIO初始化
 * @param       null
 * @return      void
 */
void GPIO::Init ()
{
    gpio_init(pin, dir, dat, pinmode);
}

/*
 * @brief       GPIO设置电平高低
 * @param       dat         引脚高低电平 (dir为GPO)有效
 * @return      void
 */
void GPIO::Set_PinVal (uint8 dat)
{
    gpio_set(pin, dat);
}

/*
 * @brief       GPIO拉高
 * @param       null
 * @return      void
 */
void GPIO::Pin_High ()
{
    gpio_set(pin, 1);
}

/*
 * @brief       GPIO拉低
 * @param       null
 * @return      void
 */
void GPIO::Pin_Low ()
{
    gpio_set(pin, 0);
}

/*
 * @brief       GPIO电平反转
 * @param       null
 * @return      void
 */
void GPIO::Pin_Toggle ()
{
    gpio_toggle(pin);
}

/*
 * @brief       GPIO获取引脚电平
 * @param       null
 * @return      uint8       0：低电平 1：高电平
 */
uint8 GPIO::Pin_Get ()
{
    return gpio_get(pin);
}
