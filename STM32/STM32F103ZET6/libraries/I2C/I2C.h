#ifndef __OJ_I2C_H
#define __OJ_I2C_H
#include "stm32f10x.h"
#include "NVIC.h"
#include "GPIO.h"
#include "RCC.h"
/*
                SCL     SDA
I2C1:
      Default:  PB6     PB7
      Remap:    PB8     PB9
I2C2:
      Default:  PB10    PB11

I2C 中断列表
I2C_IT_BUF    //缓冲器中断标志
I2C_IT_EVT    //事件中断标志
I2C_IT_ERR    //出错中断标志
*/
// I2C引脚枚举
typedef enum
{
  I2C_Default,
  I2C1_Remap
} I2C_Remap_enum;
// I2C事件列表,与stm32f10x_i2c.c中列表一致
typedef enum
{
  // I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED
  EV1_1 = I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED,
  // I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED
  EV1_2 = I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED,
  // I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED
  EV1_3 = I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED,
  // I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED
  EV1_4 = I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED,
  // I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED
  EV1_5 = I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED,
  // I2C_EVENT_SLAVE_BYTE_RECEIVED
  EV2_1 = I2C_EVENT_SLAVE_BYTE_RECEIVED,
  // (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF)
  EV2_2 = (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF),
  // (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL)
  EV2_3 = (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL),
  // I2C_EVENT_SLAVE_BYTE_TRANSMITTED
  EV3_1 = I2C_EVENT_SLAVE_BYTE_TRANSMITTED,
  // (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALF)
  EV3_3 = (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALF),
  // (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL)
  EV3_4 = (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL),
  // I2C_EVENT_SLAVE_ACK_FAILURE
  EV3_2 = I2C_EVENT_SLAVE_ACK_FAILURE,
  // I2C_EVENT_SLAVE_STOP_DETECTED
  EV4 = I2C_EVENT_SLAVE_STOP_DETECTED,
  // I2C_EVENT_MASTER_MODE_SELECT
  EV5 = I2C_EVENT_MASTER_MODE_SELECT,
  // I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED
  EV6_1 = I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED,
  // I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED
  EV6_2 = I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED,
  // I2C_EVENT_MASTER_BYTE_RECEIVED
  EV7 = I2C_EVENT_MASTER_BYTE_RECEIVED,
  // I2C_EVENT_MASTER_BYTE_TRANSMITTING
  EV8 = I2C_EVENT_MASTER_BYTE_TRANSMITTING,
  // I2C_EVENT_MASTER_BYTE_TRANSMITTED
  EV8_2 = I2C_EVENT_MASTER_BYTE_TRANSMITTED,
  // I2C_EVENT_MASTER_MODE_ADDRESS10
  EV9 = I2C_EVENT_MASTER_MODE_ADDRESS10,
} I2C_Event;

// I2C参数列表结构体
typedef struct
{
  I2C_TypeDef *I2Cx;                          // I2Cx
  I2C_InitTypeDef I2C_InitStructure;          // I2C初始化结构体
  NVIC_InitTypeDef I2C_ER_NVIC_InitStructure; // I2C错误中断初始化结构体
  NVIC_InitTypeDef I2C_EV_NVIC_InitStructure; // I2C事件中断初始化结构体
  I2C_Remap_enum I2C_Pin_Remap;               // I2C引脚选择
  uint16_t I2C_IT_Selection;                  // I2C中断位选择
  FunctionalState I2C_IT_State;               // I2C中断使(失)能
  FunctionalState I2C_DMA_State;              // I2CDMA使(失)能
} I2C_Param;

class I2C
{
private:
  I2C_Param I2Cx_Param;

public:
  I2C();
  I2C(I2C_Param I2Cx_Param);
  ~I2C();
  void Pin_Init();
  void Init();
  void Enable();
  void Disable();
  void DMACmd(FunctionalState NewState);
  void Update(I2C_Param I2Cx_Param);
  void ITConfig(uint16_t I2C_IT, FunctionalState NewState);
  void Set_I2C_Param(I2C_Param I2Cx_Param);
  void Generate_START(FunctionalState NewState);
  void Generate_STOP(FunctionalState NewState);
  ErrorStatus Check_Event(I2C_Event Event);
  void Send7bitAddress(uint8_t Addr, uint8_t I2C_Direction);
  void SendData(uint8_t Data);
  uint8_t ReceiveData();
  void AcknowledgeConfig(FunctionalState NewState);
  FlagStatus GetFlagStatus(uint32_t I2C_FLAG);
  void ClearFlag(uint32_t I2C_FLAG);
  void Software_Reset(FunctionalState NewState);
  void StretchClockCmd(FunctionalState NewState);

  void RCC_Enable();
  void RCC_Disable();
  static void RCC_Enable(I2C_TypeDef *I2Cx);
  static void RCC_Disable(I2C_TypeDef *I2Cx);
};
#endif /*__OJ_I2C_H*/