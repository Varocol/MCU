#include "SysTick.h"
#include "core_cm3.h"
/**
  * @brief  滴答定时器构造函数
  * @param  None   
  * @retval None
  */
SysTick_Operate::SysTick_Operate()
{
}

/**
  * @brief  滴答定时器析构函数
  * @param  None   
  * @retval None
  */
SysTick_Operate::~SysTick_Operate()
{
}

/**
  * @brief  滴答定时器毫秒级延时函数(滴答定时器准确定时时钟最低阈值为:24MHZ)
  * @param  ms:毫秒数  
  * @retval None
  */
void SysTick_Operate::Delay_ms(uint32_t ms)
{
  uint32_t System_Speed = RCC_Operate::Get_SYSCLK_Frequency() / 1000000; 
  SysTick_Config(System_Speed * 1000);
  for (uint32_t i = 0; i < ms; i++)
  {
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
      ;
  }
  SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
}

/**
  * @brief  滴答定时器微秒级延时函数(滴答定时器准确定时时钟最低阈值为:24MHZ)
  * @param  us:微秒数    
  * @retval None
  */
void SysTick_Operate::Delay_us(uint32_t us)
{

  SysTick_Config(RCC_Operate::Get_SYSCLK_Frequency() / 1000000);

  for (uint32_t i = 0; i < us; i++)
  {
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
      ;
  }
  SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
}

/**
  * @brief  滴答定时器自定义延时函数
  * @param  count:循环次数
  * @param  ticks:每次循环所计的数(每次计数1/SYSCLK时间)   
  * @retval None
  */
void SysTick_Operate::Delay(uint32_t count, uint32_t ticks)
{
  SysTick_Config(ticks);
  for (int i = 0; i < count; i++)
  {
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
      ;
  }
  SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
}
