#include "Buzzer.h"
/**
 * @brief  ���������캯��
 * @param  None 
 * @retval None
 */
Buzzer::Buzzer()
{
}

/**
 * @brief  ���������캯��
 * @param  None 
 * @retval None
 */
Buzzer::Buzzer(GPIO buzzer)
{
    this->buzzer = buzzer;
}

/**
 * @brief  ��������������
 * @param  None 
 * @retval None
 */
Buzzer::~Buzzer()
{
}

/**
 * @brief  ��������ʼ������
 * @param  None 
 * @retval None
 */
void Buzzer::Init()
{
    buzzer.Init();
}

/**
  * @brief  ���ֺ���
  * @param  HZ:������Ƶ����
  * @param  time:��Ӧ��ʱ��(һ��Ϊ1,����Ϊ0.5,�Դ�����)
  * @param  Basespeed:������������    
  * @retval None
  */
void Buzzer::Music(uint32_t hz, double time, uint8_t Basespeed)
{
    if (hz != 0)
    {
        Systick_Special_Delay(BEEP_HZ_CONVERT(hz), hz * time * 60 / Basespeed);
    }
    else
    {
        Systick_Delay_ms(time * 60 / Basespeed * 1000);
    }
}

/**
  * @brief  ��������������(��Ҫ����ѭ������)
  * @param  None
  * @retval None
  */
void Buzzer::run(void)
{
    buzzer.Set_Pin((BitAction)!buzzer.Get_Output_Pin());
}

/**
  * @brief  ����������ת������
  * @param  HZ:һ����Χ�ĺ�����
  * @retval SysTick_config()��������Ĳ���
  */
uint32_t Buzzer::BEEP_HZ_CONVERT(uint32_t HZ)
{
    return RCC_Operate::Get_SYSCLK_Frequency() / HZ;
}

/**
  * @brief  ������������ʱ����
  * @param  t:SysTick_config()��������Ĳ���t
  * @param  count:������������Ӧʱ��       
  * @retval None
  */
void Buzzer::Systick_Special_Delay(uint32_t t, uint32_t count)
{
    SysTick_Config(t);
    for (int i = 0; i < count; i++)
    {
        while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
            ;
        if (i < count * 5 / 6)
            run();
    }
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
}

/**
  * @brief  ��������ͨ��ʱ����
  *         ���ڼ������
  * @param  ms:������
  * @retval None
  */
void Buzzer::Systick_Delay_ms(uint32_t ms)
{
    SysTick_Config(RCC_Operate::Get_SYSCLK_Frequency() / 1000);
    for (int i = 0; i < ms; i++)
    {
        while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
            ;
    }
    SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
}