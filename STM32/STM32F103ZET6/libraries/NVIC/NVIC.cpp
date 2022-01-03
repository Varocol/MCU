#include "NVIC.h"
/**
  * @brief  NVIC空构造方法
  * @retval None
  */
NVIC_Operate::NVIC_Operate()
{
}
/**
  * @brief  NVIC析构方法
  * @retval None
  */
NVIC_Operate::~NVIC_Operate()
{
}
/**
  * @brief  NVIC构造方法
  * @param  NVIC_InitStructure:NVIC初始化结构体
  * @retval None
  */
NVIC_Operate::NVIC_Operate(NVIC_InitTypeDef *NVIC_InitStructure)
{
  Set_NVIC_InitStructure(NVIC_InitStructure);
}
/**
  * @brief  写入NVIC_PriorityGroup
  * @retval None
  */
void NVIC_Operate::PriorityGroupConfig()
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
}
/**
  * @brief  设置NVIC初始化结构体
  * @param  NVIC_InitStructure:NVIC初始化结构体
  * @retval None
  */
void NVIC_Operate::Set_NVIC_InitStructure(NVIC_InitTypeDef *NVIC_InitStructure)
{
  this->NVIC_InitStructure = NVIC_InitStructure;
}
/**
  * @brief  NVIC配置更新函数
  * @param  NVIC_InitStructure:NVIC初始化结构体
  * @retval None
  */
void NVIC_Operate::Update(NVIC_InitTypeDef *NVIC_InitStructure)
{
  Set_NVIC_InitStructure(NVIC_InitStructure);
  Init();
}
/**
  * @brief  NVIC初始化函数
  * @retval None
  */
void NVIC_Operate::Init()
{
  PriorityGroupConfig();
  NVIC_Init(NVIC_InitStructure);
}
/**
  * @brief  开启NVIC管理
  * @retval None
  */
void NVIC_Operate::Start()
{
  NVIC_InitStructure->NVIC_IRQChannelCmd = ENABLE;
  Init();
}
/**
  * @brief  关闭NVIC管理
  * @retval None
  */
void NVIC_Operate::ShutUp()
{
  NVIC_InitStructure->NVIC_IRQChannelCmd = DISABLE;
  Init();
}
