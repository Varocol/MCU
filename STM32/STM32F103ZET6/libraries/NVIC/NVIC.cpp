#include "NVIC.h"
/**
  * @brief  NVIC-空构造方法
  * @retval None
  */
NVIC_Operate::NVIC_Operate()
{
}
/**
  * @brief  NVIC-析构方法
  * @retval None
  */
NVIC_Operate::~NVIC_Operate()
{
}
/**
  * @brief  NVIC-构造方法
  * @param  NVIC_InitStructure    NVIC初始化结构体
  * @retval None
  */
NVIC_Operate::NVIC_Operate(NVIC_InitTypeDef &NVIC_InitStructure)
{
  Set_NVIC_InitStructure(NVIC_InitStructure);
}
/**
  * @brief  NVIC-设置NVIC初始化结构体
  * @param  NVIC_InitStructure    NVIC初始化结构体
  * @retval None
  */
void NVIC_Operate::Set_NVIC_InitStructure(NVIC_InitTypeDef &NVIC_InitStructure)
{
  this->NVIC_InitStructure = NVIC_InitStructure;
}
/**
  * @brief  NVIC-NVIC配置更新方法
  * @param  NVIC_InitStructure    NVIC初始化结构体
  * @retval None
  */
void NVIC_Operate::Update(NVIC_InitTypeDef &NVIC_InitStructure)
{
  Set_NVIC_InitStructure(NVIC_InitStructure);
  Init();
}
/**
  * @brief  NVIC-初始化方法
  * @param  None
  * @retval None
  */
void NVIC_Operate::Init()
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
  NVIC_Init(&NVIC_InitStructure);
}
/**
  * @brief  NVIC-开启NVIC管理
  * @param  None
  * @retval None
  */
void NVIC_Operate::Start()
{
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  Init();
}
/**
  * @brief  NVIC-关闭NVIC管理
  * @param  None
  * @retval None
  */
void NVIC_Operate::ShutUp()
{
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  Init();
}
