#include "LED.h"
/*
 * @brief       LED�չ��췽��
 * @param       void
 * @return      null
 */
LED::LED ()
{
}

/*
 * @brief       LED���ι��췽��
 * @param       pin         �Ñ���Ҫ����������
 * @param       mode        LED��ƽ����
 * @return      null
 */
LED::LED (PIN_enum pin, LED_Lighting_Mode mode)
{
    Set_Param(pin, mode);
}

/*
 * @brief       LED��������
 * @param       void
 * @return      null
 */
LED::~LED ()
{
}

/*
 * @brief       LED���ò�������
 * @param       pin         �Ñ���Ҫ����������
 * @param       mode        LED��ƽ����
 * @return      void
 */
void LED::Set_Param (PIN_enum pin, LED_Lighting_Mode mode)
{
    GPIO::Set_Param(pin, GPO, 1, PUSHPULL);
    Set_Mode(mode);
}

/*
 * @brief       LED���ü���ģʽ
 * @param       mode        LED��ƽ����
 * @return      void
 */
void LED::Set_Mode (LED_Lighting_Mode mode)
{
    this->mode = mode;
}

/*
 * @brief       LED��ʼ��
 * @param       null
 * @return      void
 */
void LED::Init ()
{
    GPIO::Init();
    On();
}

/*
 * @brief       LED����
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
 * @brief       LED����
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
 * @brief       LED�Ʒ�ת
 * @param       null
 * @return      void
 */
void LED::Toggle()
{
    Pin_Toggle();
}
