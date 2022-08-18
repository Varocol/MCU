#include "SysTick.h"
#include "core_cm3.h"
/**
 * @brief  SysTick_Operate-���췽��
 * @param  None
 * @retval None
 */
SysTick_Operate::SysTick_Operate()
{
}

/**
 * @brief  SysTick_Operate-��������
 * @param  None
 * @retval None
 */
SysTick_Operate::~SysTick_Operate()
{
}

/**
 * @brief  SysTick_Operate-���뼶��ʱ����(�δ�ʱ��׼ȷ��ʱʱ�������ֵΪ:24MHZ)
 * @param  ms           ������
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
 * @brief  SysTick_Operate-΢�뼶��ʱ����(�δ�ʱ��׼ȷ��ʱʱ�������ֵΪ:24MHZ)
 * @param  us           ΢����
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
 * @brief  SysTick_Operate-�Զ�����ʱ����
 * @param  count        ѭ������
 * @param  ticks        ÿ��ѭ�����Ƶ���(ÿ�μ���1/SYSCLKʱ��)
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
