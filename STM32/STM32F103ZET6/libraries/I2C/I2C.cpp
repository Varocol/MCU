#include "I2C.h"
/**
 * @brief  I2C-空构造方法
 * @param  None
 * @retval None
 */
I2C::I2C()
{
}

/**
 * @brief  I2C-构造方法
 * @param  I2Cx_Param     I2C的参数列表
 * @retval None
 */
I2C::I2C(I2C_Param I2Cx_Param)
{
  Set_I2C_Param(I2Cx_Param);
}

/**
 * @brief  I2C-析构方法
 * @param  None
 * @retval None
 */
I2C::~I2C()
{
}

/**
 * @brief  I2C-GPIO引脚初始化
 * @param  None
 * @retval None
 */
void I2C::Pin_Init()
{
  //若硬件方面没有给予高电平可以考虑内部上拉(IN_MODE)
  GPIO I2C_SCL = GPIO();
  GPIO I2C_SDA = GPIO();
  //对SCL和SDA线先上拉,后开漏
  if (I2Cx_Param.I2C_Pin_Remap == I2C1_Remap && I2Cx_Param.I2Cx == I2C1)
  {
    RCC_Operate::RCC_Config(AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
    I2C_SCL.Set_GPIO_Param(PB8);
    I2C_SCL.IN_MODE();
    I2C_SCL.Update(PB8, GPIO_Mode_AF_OD);
    I2C_SDA.Set_GPIO_Param(PB9);
    I2C_SDA.IN_MODE();
    I2C_SDA.Update(PB8, GPIO_Mode_AF_OD);
  }
  else if (I2Cx_Param.I2C_Pin_Remap == I2C_Default)
  {
    if (I2Cx_Param.I2Cx == I2C1)
    {
      I2C_SCL.Set_GPIO_Param(PB6);
      I2C_SCL.IN_MODE();
      I2C_SCL.Update(PB6, GPIO_Mode_AF_OD);
      I2C_SDA.Set_GPIO_Param(PB7);
      I2C_SDA.IN_MODE();
      I2C_SDA.Update(PB7, GPIO_Mode_AF_OD);
    }
    else if (I2Cx_Param.I2Cx == I2C2)
    {
      I2C_SCL.Set_GPIO_Param(PB10);
      I2C_SCL.IN_MODE();
      I2C_SCL.Update(PB10, GPIO_Mode_AF_OD);
      I2C_SDA.Set_GPIO_Param(PB11);
      I2C_SDA.IN_MODE();
      I2C_SDA.Update(PB11, GPIO_Mode_AF_OD);
    }
  }
}

/**
 * @brief  I2C-初始化方法
 * @param  None
 * @retval None
 */
void I2C::Init()
{
  //开启I2C时钟
  RCC_Enable();
  // I2C寄存器复位
  I2C_DeInit(I2Cx_Param.I2Cx);
  //软件复位,用于通讯失败后复位Busy
  Software_Reset(ENABLE);
  Software_Reset(DISABLE);
  //引脚初始化
  Pin_Init();
  //配置I2C
  I2C_Init(I2Cx_Param.I2Cx, &I2Cx_Param.I2C_InitStructure);
  //配置I2C中断优先级
  NVIC_Operate(I2Cx_Param.I2C_ER_NVIC_InitStructure).Init();
  NVIC_Operate(I2Cx_Param.I2C_EV_NVIC_InitStructure).Init();
  //配置I2C中断
  ITConfig(I2Cx_Param.I2C_IT_Selection, I2Cx_Param.I2C_IT_State);
  //配置DMA
  DMACmd(I2Cx_Param.I2C_DMA_State);
  //使能I2C
  Enable();
}

/**
 * @brief  I2C-开启I2C方法(I2C使能)
 * @param  None
 * @retval None
 */
void I2C::Enable()
{
  I2C_Cmd(I2Cx_Param.I2Cx, ENABLE);
}

/**
 * @brief  I2C-关闭I2C方法(I2C失能)
 * @param  None
 * @retval None
 */
void I2C::Disable()
{
  I2C_Cmd(I2Cx_Param.I2Cx, DISABLE);
}

/**
 * @brief  I2C-使能/失能DMA传输
 * @param  I2Cx_Param     I2C的参数列表
 * @retval None
 */
void I2C::DMACmd(FunctionalState NewState)
{
  I2C_DMACmd(I2Cx_Param.I2Cx, NewState);
}

/**
 * @brief  I2C-参数列表更新
 * @param  I2Cx_Param     I2C的参数列表
 * @retval None
 */
void I2C::Update(I2C_Param I2Cx_Param)
{
  I2C_DeInit(I2Cx_Param.I2Cx);
  Set_I2C_Param(I2Cx_Param);
  Init();
}

/**
 * @brief  I2C-中断方法
 * @param  I2C_IT         中断标志的选择
 * @param  NewState       使能或失能
 * @retval None
 */
void I2C::ITConfig(uint16_t I2C_IT, FunctionalState NewState)
{
  I2C_ITConfig(I2Cx_Param.I2Cx, I2C_IT, NewState);
}

/**
 * @brief  I2C-设置I2C的参数列表
 * @param  I2Cx_Param     I2C的参数列表
 * @retval None
 */
void I2C::Set_I2C_Param(I2C_Param I2Cx_Param)
{
  this->I2Cx_Param = I2Cx_Param;
}

/**
 * @brief  I2C-产生起始条件
 * @param  NewState       起始条件新状态
 * @retval None
 */
void I2C::Generate_START(FunctionalState NewState)
{
  I2C_GenerateSTART(I2Cx_Param.I2Cx, NewState);
}

/**
 * @brief  I2C-产生结束条件
 * @param  NewState       结束条件新状态
 * @retval None
 */
void I2C::Generate_STOP(FunctionalState NewState)
{
  I2C_GenerateSTOP(I2Cx_Param.I2Cx, NewState);
}

/**
 * @brief  I2C-检测事件
 * @param  Event          事件枚举子项
 * @retval 事件状态
 */
ErrorStatus I2C::Check_Event(I2C_Event Event)
{
  return I2C_CheckEvent(I2Cx_Param.I2Cx, Event);
}

/**
 * @brief  I2C-发送7位地址方法
 * @param  Addr           地址
 * @param  I2C_Direction  传输方向
 * @retval None
 */
void I2C::Send7bitAddress(uint8_t Addr, uint8_t I2C_Direction)
{
  I2C_Send7bitAddress(I2Cx_Param.I2Cx, Addr, I2C_Direction);
}

/**
 * @brief  I2C-发送8位数据
 * @param  Data           数据
 * @retval None
 */
void I2C::SendData(uint8_t Data)
{
  I2C_SendData(I2Cx_Param.I2Cx, Data);
}

/**
 * @brief  I2C-接收8位数据
 * @param  None
 * @retval 8位数据
 */
uint8_t I2C::ReceiveData()
{
  return I2C_ReceiveData(I2Cx_Param.I2Cx);
}

/**
 * @brief  I2C-产生应答信号
 * @param  NewState       应答新状态
 * @retval None
 */
void I2C::AcknowledgeConfig(FunctionalState NewState)
{
  I2C_AcknowledgeConfig(I2Cx_Param.I2Cx, NewState);
}

/**
 * @brief  I2C-获取标志位方法
 * @param  I2C_FLAG       I2C标志位
 * @retval 标志位状态
 */
FlagStatus I2C::GetFlagStatus(uint32_t I2C_FLAG)
{
  return I2C_GetFlagStatus(I2Cx_Param.I2Cx, I2C_FLAG);
}

/**
 * @brief  I2C-清除标志位
 * @param  I2C_FLAG       I2C标志位
 * @retval None
 */
void I2C::ClearFlag(uint32_t I2C_FLAG)
{
  I2C_ClearFlag(I2Cx_Param.I2Cx, I2C_FLAG);
}

/**
 * @brief  I2C-软件复位(可以避免因为前一次通讯失败后Busy位一直置1)
 * @param  None
 * @retval None
 */
void I2C::Software_Reset(FunctionalState NewState)
{
  I2C_SoftwareResetCmd(I2Cx_Param.I2Cx, NewState);
}

/**
 * @brief  I2C-开启I2C时钟方法
 * @param  None
 * @retval None
 */
void I2C::RCC_Enable()
{
  RCC_Operate::RCC_Config(I2Cx_Param.I2Cx, ENABLE);
}
/**
 * @brief  I2C-关闭I2C时钟方法
 * @param  None
 * @retval None
 */

void I2C::RCC_Disable()
{
  RCC_Operate::RCC_Config(I2Cx_Param.I2Cx, DISABLE);
}

/**
 * @brief  I2C-开启I2C时钟方法
 * @param  None
 * @retval None
 */
void I2C::RCC_Enable(I2C_TypeDef *I2Cx)
{
  RCC_Operate::RCC_Config(I2Cx, ENABLE);
}

/**
 * @brief  I2C-关闭I2C时钟方法
 * @param  None
 * @retval None
 */
void I2C::RCC_Disable(I2C_TypeDef *I2Cx)
{
  RCC_Operate::RCC_Config(I2Cx, DISABLE);
}