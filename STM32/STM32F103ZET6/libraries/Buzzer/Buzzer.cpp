#include "Buzzer.h"
/**
 * @brief  蜂鸣器构造函数
 * @param  None 
 * @retval None
 */
Buzzer::Buzzer()
{
}

/**
 * @brief  蜂鸣器构造函数
 * @param  None 
 * @retval None
 */
Buzzer::Buzzer(GPIO buzzer)
{
    this->buzzer = buzzer;
}

/**
 * @brief  蜂鸣器析构函数
 * @param  None 
 * @retval None
 */
Buzzer::~Buzzer()
{
}

/**
 * @brief  蜂鸣器初始化函数
 * @param  None 
 * @retval None
 */
void Buzzer::Init()
{
    buzzer.Init();
}

/**
  * @brief  音乐函数
  * @param  HZ:音调的频率数
  * @param  time:响应的时间(一拍为1,半拍为0.5,以此类推)
  * @param  Basespeed:乐曲基本拍数    
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
  * @brief  蜂鸣器驱动函数(需要其他循环驱动)
  * @param  None
  * @retval None
  */
void Buzzer::run(void)
{
    buzzer.Set_Pin((BitAction)!buzzer.Get_Output_Pin());
}

/**
  * @brief  蜂鸣器赫兹转换函数
  * @param  HZ:一定范围的赫兹数
  * @retval SysTick_config()函数所需的参数
  */
uint32_t Buzzer::BEEP_HZ_CONVERT(uint32_t HZ)
{
    return RCC_Operate::Get_SYSCLK_Frequency() / HZ;
}

/**
  * @brief  蜂鸣器特殊延时函数
  * @param  t:SysTick_config()函数所需的参数t
  * @param  count:蜂鸣器音调响应时间       
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
  * @brief  蜂鸣器普通延时函数
  *         用于间隔音符
  * @param  ms:毫秒数
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