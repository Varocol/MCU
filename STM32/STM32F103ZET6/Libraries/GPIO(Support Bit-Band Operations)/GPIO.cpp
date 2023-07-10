#include "GPIO.h"

/**
 * @brief  GPIO-空构造方法
 * @retval None
 */
GPIO::GPIO()
{
}

/**
 * @brief  GPIO-析构方法
 * @retval None
 */
GPIO::~GPIO()
{
}

/**
 * @brief  GPIO-构造方法
 * @param  Pin          引脚
 * @param  Val          GPIO初始化输出值
 * @param  Mode         GPIO模式
 * @param  Speed        GPIO速度
 * @retval None
 */
GPIO::GPIO(PIN_enum Pin, GPIOMode_TypeDef Mode, BitAction Val, GPIOSpeed_TypeDef Speed)
{
  Set_GPIO_Param(Pin, Mode, Val, Speed);
}

/**
 * @brief  GPIO-设置GPIO引脚
 * @param  Pin            引脚
 * @retval None
 */
void GPIO::Set_Pin(PIN_enum Pin)
{
  this->Pin = Pin;
  GPIOx = Get_GPIOx(Pin);
  GPIOInitStructure.GPIO_Pin = Get_GPIO_Pin(Pin);
}

/**
 * @brief  GPIO-设置GPIO初始化输出值
 *         (不能用于设置引脚值,若需要请使用Set_Pin_Val)
 * @param  Val          GPIO初始化输出值
 * @retval None
 */
void GPIO::Set_Val(BitAction Val)
{
  this->Val = Val;
}

/**
 * @brief  GPIO-设置GPIO速度
 * @param  Speed         GPIO速度
 * @retval None
 */
void GPIO::Set_Speed(GPIOSpeed_TypeDef Speed)
{
  GPIOInitStructure.GPIO_Speed = Speed;
}

/**
 * @brief  GPIO-设置GPIO模式
 * @param  Speed         GPIO模式
 * @retval None
 */
void GPIO::Set_Mode(GPIOMode_TypeDef Mode)
{
  GPIOInitStructure.GPIO_Mode = Mode;
}

/**
 * @brief  GPIO-获取引脚
 * @param  None
 * @retval Pin
 */
PIN_enum GPIO::Get_Pin()
{
  return Pin;
}

/**
 * @brief  GPIO-获取引脚初始化值
 * @param  None
 * @retval Val
 */
BitAction GPIO::Get_Val()
{
  return Val;
}

/**
 * @brief  GPIO-返回GPIO端口
 * @param  None
 * @retval GPIOx
 */
GPIO_TypeDef *GPIO::Get_GPIOx()
{
  return GPIOx;
}

/**
 * @brief  GPIO-返回GPIO初始化结构体
 * @param  None
 * @retval GPIOInitStructure
 */
GPIO_InitTypeDef GPIO::Get_GPIOInitStructure()
{
  return GPIOInitStructure;
}

/**
 * @brief  GPIO-获取Pin所对应的端口
 * @param  Pin          引脚
 * @retval Pin所对应的端口
 */
GPIO_TypeDef *GPIO::Get_GPIOx(PIN_enum Pin)
{
  GPIO_TypeDef *GPIOx;
  switch (Pin / 17)
  {
  case 0:
    GPIOx = GPIOA;
    break;
  case 1:
    GPIOx = GPIOB;
    break;
  case 2:
    GPIOx = GPIOC;
    break;
  case 3:
    GPIOx = GPIOD;
    break;
  case 4:
    GPIOx = GPIOE;
    break;
  case 5:
    GPIOx = GPIOF;
    break;
  case 6:
    GPIOx = GPIOG;
    break;
  }
  return GPIOx;
}

/**
 * @brief  GPIO-获取Pin所对应的GPIO_Pin
 * @param  Pin          引脚
 * @retval Pin所对应的GPIO_Pin
 */
uint16_t GPIO::Get_GPIO_Pin(PIN_enum Pin)
{
  uint16_t GPIO_Pin_x;
  switch (Pin % 17)
  {
  case 0:
    GPIO_Pin_x = GPIO_Pin_0;
    break;
  case 1:
    GPIO_Pin_x = GPIO_Pin_1;
    break;
  case 2:
    GPIO_Pin_x = GPIO_Pin_2;
    break;
  case 3:
    GPIO_Pin_x = GPIO_Pin_3;
    break;
  case 4:
    GPIO_Pin_x = GPIO_Pin_4;
    break;
  case 5:
    GPIO_Pin_x = GPIO_Pin_5;
    break;
  case 6:
    GPIO_Pin_x = GPIO_Pin_6;
    break;
  case 7:
    GPIO_Pin_x = GPIO_Pin_7;
    break;
  case 8:
    GPIO_Pin_x = GPIO_Pin_8;
    break;
  case 9:
    GPIO_Pin_x = GPIO_Pin_9;
    break;
  case 10:
    GPIO_Pin_x = GPIO_Pin_10;
    break;
  case 11:
    GPIO_Pin_x = GPIO_Pin_11;
    break;
  case 12:
    GPIO_Pin_x = GPIO_Pin_12;
    break;
  case 13:
    GPIO_Pin_x = GPIO_Pin_13;
    break;
  case 14:
    GPIO_Pin_x = GPIO_Pin_14;
    break;
  case 15:
    GPIO_Pin_x = GPIO_Pin_15;
    break;
  case 16:
    GPIO_Pin_x = GPIO_Pin_All;
    break;
  }
  return GPIO_Pin_x;
}

/**
 * @brief  GPIO-初始化GPIO为输出模式
 * @param  None
 * @retval None
 */
void GPIO::OUT_MODE()
{
  GPIOInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  Init();
}

/**
 * @brief  GPIO-初始化GPIO为输入模式
 * @param  None
 * @retval None
 */
void GPIO::IN_MODE()
{
  GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  Init();
}

/**
 * @brief  GPIO-引脚拉高
 * @param  None
 * @retval None
 */
void GPIO::Pin_High()
{
  GPIO_SetBits(GPIOx, GPIOInitStructure.GPIO_Pin);
}

/**
 * @brief  GPIO-引脚拉低
 * @param  None
 * @retval None
 */
void GPIO::Pin_Low()
{
  GPIO_ResetBits(GPIOx, GPIOInitStructure.GPIO_Pin);
}

/**
 * @brief  GPIO-引脚反转
 * @param  None
 * @retval None
 */
void GPIO::Pin_Toggle()
{
  Set_Pin_Val(Get_Input_Pin() == Bit_RESET ? Bit_SET : Bit_RESET);
}

/**
 * @brief  GPIO-设置引脚值
 * @param  BitVal       引脚值
 * @retval None
 */
void GPIO::Set_Pin_Val(uint8_t BitVal)
{
  GPIO_WriteBit(GPIOx, GPIOInitStructure.GPIO_Pin, (BitAction)BitVal);
}

/**
 * @brief  GPIO-设置端口值
 * @param  PortVal      端口值
 * @retval None
 */
void GPIO::Set_Port_Val(uint16_t PortVal)
{
  GPIO_Write(GPIOx, PortVal);
}

/**
 * @brief  GPIO-读取输入的引脚数值
 * @param  None
 * @retval 输入引脚的数值
 */
BitAction GPIO::Get_Input_Pin()
{
  if (GPIO_ReadInputDataBit(GPIOx, GPIOInitStructure.GPIO_Pin) == 0x00)
  {
    return Bit_RESET;
  }
  else
  {
    return Bit_SET;
  }
}

/**
 * @brief  GPIO-读取输出的引脚数值
 * @param  None
 * @retval 输出引脚的数值
 */
BitAction GPIO::Get_Output_Pin()
{
  if (GPIO_ReadOutputDataBit(GPIOx, GPIOInitStructure.GPIO_Pin) == 0x00)
  {
    return Bit_RESET;
  }
  else
  {
    return Bit_SET;
  }
}

/**
 * @brief  GPIO-读取输入的端口数值
 * @param  None
 * @retval 输入端口的数值
 */
uint16_t GPIO::Get_Input_Port()
{
  return GPIO_ReadInputData(GPIOx);
}

/**
 * @brief  GPIO-读取输出的端口数值
 * @param  None
 * @retval 输出端口的数值
 */
uint16_t GPIO::Get_Output_Port()
{
  return GPIO_ReadOutputData(GPIOx);
}

/**
 * @brief  GPIO-设置参数列表
 * @param  Pin          引脚
 * @param  Val          GPIO初始化输出值
 * @param  Mode         GPIO模式
 * @param  Speed        GPIO速度
 * @retval None
 */
void GPIO::Set_GPIO_Param(PIN_enum Pin, GPIOMode_TypeDef Mode, BitAction Val, GPIOSpeed_TypeDef Speed)
{
  Set_Pin(Pin);
  Set_Val(Val);
  Set_Speed(Speed);
  Set_Mode(Mode);
}

/**
 * @brief  GPIO-参数更新
 * @param  Pin          引脚
 * @param  Val          GPIO初始化输出值
 * @param  Mode         GPIO模式
 * @param  Speed        GPIO速度
 * @retval None
 */
void GPIO::Update(PIN_enum Pin, GPIOMode_TypeDef Mode, BitAction Val, GPIOSpeed_TypeDef Speed)
{
  Set_GPIO_Param(Pin, Mode, Val, Speed);
  Init();
}

/**
 * @brief  GPIO-初始化方法
 * @param  None
 * @retval None
 */
void GPIO::Init()
{
  RCC_Enable();
  GPIO_Init(GPIOx, &GPIOInitStructure);
  switch (GPIOInitStructure.GPIO_Mode)
  {
  case GPIO_Mode_Out_OD:
  case GPIO_Mode_Out_PP:
    Set_Pin_Val(Val);
    break;
  default:
    break;
  }
}

/**
 * @brief  GPIO-开启GPIO时钟方法
 * @param  None
 * @retval None
 */
void GPIO::RCC_Enable()
{
  RCC_Operate::RCC_Config(GPIOx, ENABLE);
}

/**
 * @brief  GPIO-关闭GPIO时钟方法
 * @param  None
 * @retval None
 */
void GPIO::RCC_Disable()
{
  RCC_Operate::RCC_Config(GPIOx, DISABLE);
}

/**
 * @brief  GPIO-开启GPIO时钟方法
 * @param  None
 * @retval None
 */
void GPIO::RCC_Enable(GPIO_TypeDef *GPIOx)
{
  RCC_Operate::RCC_Config(GPIOx, ENABLE);
}

/**
 * @brief  GPIO-关闭GPIO时钟方法
 * @param  None
 * @retval None
 */
void GPIO::RCC_Disable(GPIO_TypeDef *GPIOx)
{
  RCC_Operate::RCC_Config(GPIOx, DISABLE);
}