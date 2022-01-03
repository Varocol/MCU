#include "GPIO.h"
/*
 * @brief       GPIO�չ��췽��
 * @param       void
 * @return      null
 */
GPIO::GPIO ()
{

}

/*
 * @brief       GPIO��������
 * @param       void
 * @return      null
 */
GPIO::~GPIO ()
{

}

/*
 * @brief       GPIO���ι��췽��
 * @param       pin         �Ñ���Ҫ����������
 * @param       dir         ���������������
 * @param       dat         ���Ÿߵ� (���dirΪGPI��dat�������)
 * @param       pinmode     ���ŵ�ģʽ
 * @return      null
 */
GPIO::GPIO (PIN_enum pin, GPIODIR_enum dir, uint8 dat, GPIOMODE_enum pinmode)
{
    Set_Param(pin, dir, dat, pinmode);
}

/*
 * @brief       GPIO���ò�������
 * @param       pin         �Ñ���Ҫ����������
 * @param       dir         ���������������
 * @param       dat         ���Ÿߵ͵�ƽ (dirΪGPO)��Ч
 * @param       pinmode     ���ŵ�ģʽ
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
 * @brief       GPIO������Ҫ������������
 * @param       pin         �Ñ���Ҫ����������
 * @return      void
 */
void GPIO::Set_Pin (PIN_enum pin)
{
    this->pin = pin;
}

/*
 * @brief       GPIO�������������������
 * @param       dir         ���������������
 * @return      void
 */
void GPIO::Set_Dir (GPIODIR_enum dir)
{
    this->dir = dir;
}

/*
 * @brief       GPIO�������Ÿߵ͵�ƽ
 * @param       dat         ���Ÿߵ͵�ƽ (dirΪGPO)��Ч
 * @return      void
 */
void GPIO::Set_Dat (uint8 dat)
{
    this->dat = dat;
}

/*
 * @brief       GPIO�������ŵ�ģʽ
 * @param       pinmode     ���ŵ�ģʽ
 * @return      void
 */
void GPIO::Set_Pinmode (GPIOMODE_enum pinmode)
{
    this->pinmode = pinmode;
}

/*
 * @brief       GPIO��ʼ��
 * @param       null
 * @return      void
 */
void GPIO::Init ()
{
    gpio_init(pin, dir, dat, pinmode);
}

/*
 * @brief       GPIO���õ�ƽ�ߵ�
 * @param       dat         ���Ÿߵ͵�ƽ (dirΪGPO)��Ч
 * @return      void
 */
void GPIO::Set_PinVal (uint8 dat)
{
    gpio_set(pin, dat);
}

/*
 * @brief       GPIO����
 * @param       null
 * @return      void
 */
void GPIO::Pin_High ()
{
    gpio_set(pin, 1);
}

/*
 * @brief       GPIO����
 * @param       null
 * @return      void
 */
void GPIO::Pin_Low ()
{
    gpio_set(pin, 0);
}

/*
 * @brief       GPIO��ƽ��ת
 * @param       null
 * @return      void
 */
void GPIO::Pin_Toggle ()
{
    gpio_toggle(pin);
}

/*
 * @brief       GPIO��ȡ���ŵ�ƽ
 * @param       null
 * @return      uint8       0���͵�ƽ 1���ߵ�ƽ
 */
uint8 GPIO::Pin_Get ()
{
    return gpio_get(pin);
}
