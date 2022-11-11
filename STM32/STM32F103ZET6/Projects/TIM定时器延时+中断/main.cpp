#include "Libraries.h"
#include "bsp_led.h"
void Delay_ms(uint32_t ms); //保留TIM2用来延时,需要搭配delay_Complete来判断延时是否完成
bool Delay_Complete();      //延时是否完成
int main()
{
     // HSE_SetSysClock(RCC_PLLMul_9);
     LED_GPIOInit();
     LED.Pin_Off();
     while (1)
     {
          if (Delay_Complete())
          {
               Delay_ms(2000);
               LED.Set_Pin(flag);
          }
     }
}

/**
  * @brief  TIM静态毫秒级延时方法
  * @param  TIMx_Parma:TIM初始化参数列表
  * @retval None
  */
void Delay_ms(uint32_t ms)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  //开启TIM2时钟
  RCC_Operate::RCC_Config(TIM2, ENABLE);
  //TIM2寄存器复位
  TIM_DeInit(TIM2);
  //TIM基础参数结构体
  // 配置定时器的分频因子(PSC)
  TIM_TimeBaseStructure.TIM_Prescaler = RCC_Operate::Get_SYSCLK_Frequency() / 1000000 - 1;
  // 配置定时器的重装载寄存器(ARR)
  TIM_TimeBaseStructure.TIM_Period = (1000 - 1); // 这个值可以临时设置
  // 时钟分频因子，基本定时器没有
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  // 计数器计数模式，基本定时器只能向上计数，没有计数模式的设置
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  // 重复计数器的值，基本定时器没有
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  // 初始化定时器
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  // 清除计时器中断标志位/
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  // 开启计时器中断
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  //NVIC配置
  NVIC_InitTypeDef NVIC_InitStructure =
      {
          TIM2_IRQn,
          0,
          3,
          ENABLE};
  NVIC_Operate TIM2_NVIC_Operate = NVIC_Operate(NVIC_InitStructure);
  TIM2_NVIC_Operate.Init();
  //设置时间
  time_ms = ms;
  // 使能计数器
  TIM_Cmd(TIM2, ENABLE);
}

/**
  * @brief  判断延时是否完成函数
  * @param  None
  * @retval 是否延时结束
  */
bool Delay_Complete()
{
  //检查TIM2状态
  if((!(TIM2->CR1 & TIM_CR1_CEN)) && current_time_ms == 0)
  {
    return true;
  }
  else 
  {
    return false;
  }
}