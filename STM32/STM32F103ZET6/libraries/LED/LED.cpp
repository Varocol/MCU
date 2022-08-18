#include "LED.h"
/**
 * @brief   LED-�չ��췽��
 * @param   None
 * @return  None
 */
LED::LED()
{
}

/**
 * @brief   LED-���ι��췽��
 * @param   pin         �û���Ҫ����������
 * @param   mode        LED��ƽ����
 * @return  None
 */
LED::LED(PIN_enum pin, LED_Lighting_Mode mode)
{
    Set_Param(pin, mode);
}

/**
 * @brief   LED-��������
 * @param   None
 * @return  None
 */
LED::~LED()
{
}

/**
 * @brief   LED-���ò�������
 * @param   pin         �û���Ҫ����������
 * @param   mode        LED��ƽ����
 * @return  None
 */
void LED::Set_Param(PIN_enum pin, LED_Lighting_Mode mode)
{
    Set_GPIO_Param(pin);
    Set_Mode(mode);
}

/**
 * @brief   LED-���ü���ģʽ
 * @param   mode        LED��ƽ����
 * @return  None
 */
void LED::Set_Mode(LED_Lighting_Mode mode)
{
    this->mode = mode;
}

/**
 * @brief   LED-��ʼ��
 * @param   None
 * @return  None
 */
void LED::Init()
{
    OUT_MODE();
    On();
}

/**
 * @brief   LED-����
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
 * @brief  LED-����
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
 * @brief  LED-�Ʒ�ת
 * @param  None
 * @return None
 */
void LED::Toggle()
{
    Pin_Toggle();
}
