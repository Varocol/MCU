#include "GPIO.h"

/**
 * @brief  GPIO空构造方法
 * @retval None
 */
GPIO::GPIO()
{
}

/**
 * @brief  GPIO析构函数
 * @retval None
 */
GPIO::~GPIO()
{
}

/**
 * @brief  GPIO构造函数
 * @param  GPIOx:GPIO端口
 * @param  GPIO_Pin_x:GPIO引脚
 * @retval None
 */
GPIO::GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin_x)
{
  Set_GPIO(GPIOx);
  Set_GPIO_Pin(GPIO_Pin_x);
}

/**
 * @brief  GPIO构造方法
 * @param  GPIOx:GPIO端口
 * @param  GPIOInitStructure:GPIO初始化结构体
 * @retval None
 */
GPIO::GPIO(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef GPIOInitStructure)
{
  Set_GPIO(GPIOx);
  Set_GPIOInitStructure(GPIOInitStructure);
}

/**
 * @brief  返回GPIO端口
 * @retval GPIOx
 */
GPIO_TypeDef *GPIO::Get_GPIOx()
{
  return GPIOx;
}

/**
 * @brief  返回GPIO初始化结构体
 * @retval GPIOInitStructure
 */
GPIO_InitTypeDef GPIO::Get_GPIOInitStructure()
{
  return GPIOInitStructure;
}

/**
 * @brief  GPIO设置初始化结构体
 * @param  GPIOInitStructure:GPIO初始化结构体
 * @retval None
 */
void GPIO::Set_GPIOInitStructure(GPIO_InitTypeDef GPIOInitStructure)
{
  this->GPIOInitStructure = GPIOInitStructure;
}

/**
 * @brief  GPIO设置GPIO端口
 * @param  GPIOx:GPIO端口
 * @retval None
 */
void GPIO::Set_GPIO(GPIO_TypeDef *GPIOx)
{
  this->GPIOx = GPIOx;
}

/**
 * @brief  设置GPIO引脚
 * @param  GPIO_Pin_x:GPIO引脚
 * @retval None
 */
void GPIO::Set_GPIO_Pin(uint16_t GPIO_Pin_x)
{
  GPIOInitStructure.GPIO_Pin = GPIO_Pin_x;
}

/**
 * @brief  设置端口引脚值
 * @param  GPIO_Pin_x:GPIO引脚
 * @retval None
 */
void GPIO::Set_Port(uint16_t PortVal)
{
  GPIO_Write(GPIOx, PortVal);
}
/**
 * @brief  初始化GPIO为输出模式
 * @param  GPIOx:GPIO端口
 * @param  GPIO_Pin_x:GPIO引脚
 * @retval None
 */
void GPIO::OUT_MODE()
{
  GPIOInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  Init();
}

/**
 * @brief  初始化GPIO为输入模式
 * @param  GPIOx:GPIO端口
 * @param  GPIO_Pin_x:GPIO引脚
 * @retval None
 */
void GPIO::IN_MODE()
{
  GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIOInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  Init();
}

/**
 * @brief  GPIO pin口拉高
 * @param  pin:pin口
 * @retval None
 */
void GPIO::Pin_On()
{
  GPIO_SetBits(GPIOx, GPIOInitStructure.GPIO_Pin);
}

/**
 * @brief  GPIO pin口拉低
 * @param  pin:pin口
 * @retval None
 */
void GPIO::Pin_Off()
{
  GPIO_ResetBits(GPIOx, GPIOInitStructure.GPIO_Pin);
}

/**
 * @brief  设置Pin高低
 * @param  BitVal:状态值
 * @retval None
 */
void GPIO::Set_Pin(uint8_t BitVal)
{
  GPIO_WriteBit(GPIOx, GPIOInitStructure.GPIO_Pin, (BitAction)BitVal);
}

/**
 * @brief  读取输入的Pin高低
 * @param  None
 * @retval pin口的高低
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
 * @brief  读取输出的Pin高低
 * @param  None
 * @retval pin口的高低
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
 * @brief  读取输入的端口数据
 * @param  None
 * @retval 端口数据
 */
uint16_t GPIO::Get_Input_Port()
{
  return GPIO_ReadInputData(GPIOx);
}

/**
 * @brief  读取输出的端口数据
 * @param  None
 * @retval 端口数据
 */
uint16_t GPIO::Get_Output_Port()
{
  return GPIO_ReadOutputData(GPIOx);
}

/**
 * @brief  GPIO配置更新
 * @param  GPIOx:GPIO端口
 * @param  GPIOInitStructure:GPIO初始化结构体
 * @retval None
 */
void GPIO::Update(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef GPIOInitStructure)
{
  Set_GPIO(GPIOx);
  Set_GPIOInitStructure(GPIOInitStructure);
  Init();
}

/**
 * @brief  GPIO初始化函数
 * @param  None
 * @retval None
 */
void GPIO::Init()
{
  Start();
  GPIO_Init(GPIOx, &GPIOInitStructure);
}
/**
 * @brief  开启GPIO函数(打开时钟)
 * @param  None
 * @retval None
 */
void GPIO::Start()
{
  RCC_Operate::RCC_Config(GPIOx, ENABLE);
}
/**
 * @brief  关闭GPIO函数(关闭时钟)
 * @param  None
 * @retval None
 */
void GPIO::ShutUp()
{
  RCC_Operate::RCC_Config(GPIOx, DISABLE);
}