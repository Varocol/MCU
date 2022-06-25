#include "I2C.h"
//I2C1_Default I2C_SCL = PB6
GPIO_InitTypeDef I2C1_SCL_Pin_1 =
    {
        GPIO_Pin_6,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_OD};

//I2C1_Default I2C_SDA = PB7
GPIO_InitTypeDef I2C1_SDA_Pin_1 =
    {
        GPIO_Pin_7,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_OD};

//I2C1_Remap   I2C_SCL = PB8
GPIO_InitTypeDef I2C1_SCL_Pin_2 =
    {
        GPIO_Pin_8,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_OD};

//I2C1_Remap   I2C_SDA = PB9
GPIO_InitTypeDef I2C1_SDA_Pin_2 =
    {
        GPIO_Pin_9,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_OD};

//I2C2_Default I2C_SCL = PB10
GPIO_InitTypeDef I2C2_SCL_Pin =
    {
        GPIO_Pin_10,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_OD};

//I2C2_Default I2C_SDA = PB11
GPIO_InitTypeDef I2C2_SDA_Pin =
    {
        GPIO_Pin_11,
        GPIO_Speed_50MHz,
        GPIO_Mode_AF_OD};
/**
  * @brief  I2C空构造方法
  * @param  None
  * @retval None
  */
I2C::I2C()
{
}

/**
  * @brief  I2C构造方法
  * @param  I2Cx_Param:I2C的参数列表
  * @retval None
  */
I2C::I2C(I2C_Param I2Cx_Param)
{
  Set_I2C_Param(I2Cx_Param);
}

/**
  * @brief  I2C析构函数
  * @param  None
  * @retval None
  */
I2C::~I2C()
{
}

/**
  * @brief  I2C GPIO引脚初始化
  * @param  None
  * @retval None
  */
void I2C::Pin_Init()
{
  //若硬件方面没有给予高电平可以考虑内部上拉(IN_MODE)
  //I2C1_SCL = PB8    I2C1_SDA = PB9
  if (I2Cx_Param.I2C_Pin_Remap_Selection == I2C1_Remap)
  {
    RCC_Operate::RCC_Config(AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
    //先上拉,后开漏
    GPIO *I2C1_SCL = new GPIO(GPIOB, I2C1_SCL_Pin_2);
    I2C1_SCL->IN_MODE();
    I2C1_SCL->Update(GPIOB, I2C1_SCL_Pin_2);
    delete I2C1_SCL;
    //先上拉,后开漏
    GPIO *I2C1_SDA = new GPIO(GPIOB, I2C1_SDA_Pin_2);
    I2C1_SDA->IN_MODE();
    I2C1_SDA->Update(GPIOB, I2C1_SDA_Pin_2);
    delete I2C1_SDA;
  }
  else if (I2Cx_Param.I2C_Pin_Remap_Selection == I2C_Default)
  {
    //I2C1_SCL = PB6    I2C1_SDA = PB7
    if (I2Cx_Param.I2Cx == I2C1)
    {
      //先上拉,后开漏
      GPIO *I2C1_SCL = new GPIO(GPIOB, I2C1_SCL_Pin_1);
      I2C1_SCL->IN_MODE();
      I2C1_SCL->Update(GPIOB, I2C1_SCL_Pin_1);
      delete I2C1_SCL;
      //先上拉,后开漏
      GPIO *I2C1_SDA = new GPIO(GPIOB, I2C1_SDA_Pin_1);
      I2C1_SDA->IN_MODE();
      I2C1_SDA->Update(GPIOB, I2C1_SDA_Pin_1);
      delete I2C1_SDA;
    }
    // I2C2_SCL = PB10    I2C2_SDA = PB11
    else if (I2Cx_Param.I2Cx == I2C2)
    {
      //先上拉,后开漏
      GPIO *I2C2_SCL = new GPIO(GPIOB, I2C2_SCL_Pin);
      I2C2_SCL->IN_MODE();
      I2C2_SCL->Update(GPIOB, I2C2_SCL_Pin);
      delete I2C2_SCL;
      //先上拉,后开漏
      GPIO *I2C2_SDA = new GPIO(GPIOB, I2C2_SDA_Pin);
      I2C2_SDA->IN_MODE();
      I2C2_SDA->Update(GPIOB, I2C2_SDA_Pin);
      delete I2C2_SDA;
    }
  }
}

/**
  * @brief  I2C 初始化函数
  * @param  None
  * @retval None
  */
void I2C::Init()
{
  //开启I2C时钟
  RCC_Operate::RCC_Config(I2Cx_Param.I2Cx, ENABLE);
  //I2C寄存器复位
  I2C_DeInit(I2Cx_Param.I2Cx);
  //软件复位,用于通讯失败后复位Busy
  Software_Reset(ENABLE);
  Software_Reset(DISABLE);
  //引脚初始化
  Pin_Init();
  //配置I2C
  I2C_Init(I2Cx_Param.I2Cx, &I2Cx_Param.I2C_InitStructure);
  //配置I2C中断优先级
  I2Cx_Param.I2C_ER_NVIC_Operate.Init();
  I2Cx_Param.I2C_EV_NVIC_Operate.Init();
  //配置I2C中断
  I2C_ITConfig(I2Cx_Param.I2Cx, I2Cx_Param.I2C_IT_Selection, I2Cx_Param.I2C_IT_State);
  //使能I2C
  Start();
}

/**
  * @brief  开启I2C函数(I2C使能)
  * @param  None
  * @retval None
  */
void I2C::Start()
{
  I2C_Cmd(I2Cx_Param.I2Cx, ENABLE);
}

/**
  * @brief  关闭I2C函数(I2C失能)
  * @param  None
  * @retval None
  */
void I2C::ShutUp()
{
  I2C_Cmd(I2Cx_Param.I2Cx, DISABLE);
}

/**
  * @brief  I2C参数列表更新
  * @param  I2Cx_Param:I2C的参数列表
  * @retval None
  */
void I2C::Update(I2C_Param I2Cx_Param)
{
  I2C_DeInit(I2Cx_Param.I2Cx);
  Set_I2C_Param(I2Cx_Param);
  Init();
}

/**
  * @brief  设置I2C的参数列表
  * @param  I2Cx_Param:I2C的参数列表
  * @retval None
  */
void I2C::Set_I2C_Param(I2C_Param I2Cx_Param)
{
  this->I2Cx_Param = I2Cx_Param;
}

/**
  * @brief  I2C产生起始条件
  * @param  NewState:起始条件新状态
  * @retval None
  */
void I2C::Generate_START(FunctionalState NewState)
{
  I2C_GenerateSTART(I2Cx_Param.I2Cx, NewState);
}

/**
  * @brief  I2C产生结束条件
  * @param  NewState:结束条件新状态
  * @retval None
  */
void I2C::Generate_STOP(FunctionalState NewState)
{
  I2C_GenerateSTOP(I2Cx_Param.I2Cx, NewState);
}

/**
  * @brief  I2C检测事件
  * @param  Event:事件枚举子项
  * @retval 事件状态
  */
ErrorStatus I2C::Check_Event(I2C_Event Event)
{
  return I2C_CheckEvent(I2Cx_Param.I2Cx, Event);
}

/**
  * @brief  I2C发送7位地址方法
  * @param  Addr:地址
  * @param  I2C_Direction:传输方向
  * @retval None
  */
void I2C::Send7bitAddress(uint8_t Addr, uint8_t I2C_Direction)
{
  I2C_Send7bitAddress(I2Cx_Param.I2Cx, Addr, I2C_Direction);
}

/**
  * @brief  I2C发送8位数据
  * @param  Data:数据
  * @retval None
  */
void I2C::SendData(uint8_t Data)
{
  I2C_SendData(I2Cx_Param.I2Cx, Data);
}

/**
  * @brief  I2C接收8位数据
  * @param  None
  * @retval Data:数据
  */
uint8_t I2C::ReceiveData()
{
  return I2C_ReceiveData(I2Cx_Param.I2Cx);
}

/**
  * @brief  I2C产生应答信号
  * @param  NewState:应答新状态
  * @retval None
  */
void I2C::AcknowledgeConfig(FunctionalState NewState)
{
  I2C_AcknowledgeConfig(I2Cx_Param.I2Cx, NewState);
}

/**
  * @brief  I2C获取标志位方法
  * @param  I2C_FLAG:I2C标志位
  * @retval 标志位状态
  */
FlagStatus I2C::GetFlagStatus(uint32_t I2C_FLAG)
{
  return I2C_GetFlagStatus(I2Cx_Param.I2Cx, I2C_FLAG);
}

/**
  * @brief  I2C清除标志位
  * @param  I2C_FLAG:I2C标志位
  * @retval None
  */
void I2C::ClearFlag(uint32_t I2C_FLAG)
{
  I2C_ClearFlag(I2Cx_Param.I2Cx, I2C_FLAG);
}

/**
  * @brief  I2C软件复位(可以避免因为前一次通讯失败后Busy位一直置1)
  * @param  None
  * @retval None
  */
void I2C::Software_Reset(FunctionalState NewState)
{
  I2C_SoftwareResetCmd(I2Cx_Param.I2Cx, NewState);
}