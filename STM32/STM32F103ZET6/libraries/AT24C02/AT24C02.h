#ifndef __OJ_AT24C02_H
#define __OJ_AT24C02_H
#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_EVENT_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))
#define Check_PROCESS_CONDITION   \
  if (PROCESS_CONDITION == false) \
    return;
#define BUSY_ERROR "总线正在忙碌!\n在函数%s处无法运行"
#define EVENT_ERROR "事件%s无法响应!\n在函数%s处无法运行"
#define FLAG_ERROR "标志位%s无法改变!\n在函数%s处无法运行"
#include "I2C.h"
#include "USART.h"
#include "USART_DEBUG.h"
#include "stdio.h"
//AT24C02参数列表结构体
typedef struct
{
  uint8_t AT24C02_ADDR;
  I2C_TypeDef *I2Cx;
} AT24C02_Param;

class AT24C02
{
private:
  AT24C02_Param AT24C02x_Param;
  I2C *I2Cx;
  uint32_t FLAG_TIMEOUT;
  uint32_t EVENT_TIMEOUT;

public:
  bool PROCESS_CONDITION;
  AT24C02();
  AT24C02(AT24C02_Param AT24C02x_Param);
  ~AT24C02();
  void Init();
  void Update(AT24C02_Param AT24C02x_Param);
  void Set_AT24C02x_Param(AT24C02_Param AT24C02x_Param);
  void Write_Byte(uint8_t Byte_Addr, uint8_t Data);
  void Write_Buffer(uint8_t Byte_Addr, uint8_t p[], uint8_t num);
  void Write_Page(uint8_t Byte_Addr, uint8_t p[], uint8_t num);
  void Read_Buffer(uint8_t Byte_Addr, uint8_t p[], uint8_t num);
  void Check_AT24C02_Busy();
};

#endif /*__OJ_AT24C02_H*/