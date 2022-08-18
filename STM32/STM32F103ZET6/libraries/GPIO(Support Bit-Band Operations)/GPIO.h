#ifndef __OJ_GPIO_H
#define __OJ_GPIO_H
#include "stm32f10x.h"
#include "RCC.h"
typedef enum
{
    PA0,
    PA1,
    PA2,
    PA3,
    PA4,
    PA5,
    PA6,
    PA7,
    PA8,
    PA9,
    PA10,
    PA11,
    PA12,
    PA13,
    PA14,
    PA15,
    PA_All,
    PB0,
    PB1,
    PB2,
    PB3,
    PB4,
    PB5,
    PB6,
    PB7,
    PB8,
    PB9,
    PB10,
    PB11,
    PB12,
    PB13,
    PB14,
    PB15,
    PB_All,
    PC0,
    PC1,
    PC2,
    PC3,
    PC4,
    PC5,
    PC6,
    PC7,
    PC8,
    PC9,
    PC10,
    PC11,
    PC12,
    PC13,
    PC14,
    PC15,
    PC_All,
    PD0,
    PD1,
    PD2,
    PD3,
    PD4,
    PD5,
    PD6,
    PD7,
    PD8,
    PD9,
    PD10,
    PD11,
    PD12,
    PD13,
    PD14,
    PD15,
    PD_All,
    PE0,
    PE1,
    PE2,
    PE3,
    PE4,
    PE5,
    PE6,
    PE7,
    PE8,
    PE9,
    PE10,
    PE11,
    PE12,
    PE13,
    PE14,
    PE15,
    PE_All,
    PF0,
    PF1,
    PF2,
    PF3,
    PF4,
    PF5,
    PF6,
    PF7,
    PF8,
    PF9,
    PF10,
    PF11,
    PF12,
    PF13,
    PF14,
    PF15,
    PF_All,
    PG0,
    PG1,
    PG2,
    PG3,
    PG4,
    PG5,
    PG6,
    PG7,
    PG8,
    PG9,
    PG10,
    PG11,
    PG12,
    PG13,
    PG14,
    PG15,
    PG_All,
} PIN_enum;
class GPIO
{
private:
    PIN_enum Pin;
    BitAction Val = Bit_RESET;
    GPIO_TypeDef *GPIOx;
    GPIO_InitTypeDef GPIOInitStructure;

public:
    GPIO();
    ~GPIO();
    //这样排列是按照使用频率排的
    GPIO(PIN_enum Pin, GPIOMode_TypeDef Mode = GPIO_Mode_Out_PP, BitAction Val = Bit_RESET, GPIOSpeed_TypeDef Speed = GPIO_Speed_50MHz);
    void Set_Pin(PIN_enum Pin);
    void Set_Val(BitAction Val);
    void Set_Speed(GPIOSpeed_TypeDef Speed);
    void Set_Mode(GPIOMode_TypeDef Mode);

    PIN_enum Get_Pin();
    BitAction Get_Val();
    GPIO_TypeDef *Get_GPIOx();
    GPIO_InitTypeDef Get_GPIOInitStructure();

    GPIO_TypeDef *Get_GPIOx(PIN_enum Pin);
    uint16_t Get_GPIO_Pin(PIN_enum Pin);

    void OUT_MODE();
    void IN_MODE();
    void Pin_High();
    void Pin_Low();
    void Pin_Toggle();
    void Set_Pin_Val(uint8_t BitVal);
    void Set_Port_Val(uint16_t PortVal);

    BitAction Get_Input_Pin();
    BitAction Get_Output_Pin();
    uint16_t Get_Input_Port();
    uint16_t Get_Output_Port();

    void Set_GPIO_Param(PIN_enum Pin, GPIOMode_TypeDef Mode = GPIO_Mode_Out_PP, BitAction Val = Bit_RESET, GPIOSpeed_TypeDef Speed = GPIO_Speed_50MHz);
    void Update(PIN_enum Pin, GPIOMode_TypeDef Mode = GPIO_Mode_Out_PP, BitAction Val = Bit_RESET, GPIOSpeed_TypeDef Speed = GPIO_Speed_50MHz);

    void Init();
    static void Start(GPIO_TypeDef *GPIOx);
    static void ShutUp(GPIO_TypeDef *GPIOx);
};
#define GPIOA_ODR_Addr (GPIOA_BASE + 12) // 0X4001080C
#define GPIOB_ODR_Addr (GPIOB_BASE + 12) // 0X40010C0C
#define GPIOC_ODR_Addr (GPIOC_BASE + 12) // 0X4001100C
#define GPIOD_ODR_Addr (GPIOD_BASE + 12) // 0X4001140C
#define GPIOE_ODR_Addr (GPIOE_BASE + 12) // 0X4001180C
#define GPIOF_ODR_Addr (GPIOF_BASE + 12) // 0X40011C0C
#define GPIOG_ODR_Addr (GPIOG_BASE + 12) // 0X4001200C

#define GPIOA_IDR_Addr (GPIOA_BASE + 8) // 0X40010808
#define GPIOB_IDR_Addr (GPIOB_BASE + 8) // 0X40010C08
#define GPIOC_IDR_Addr (GPIOC_BASE + 8) // 0X40011008
#define GPIOD_IDR_Addr (GPIOD_BASE + 8) // 0X40011408
#define GPIOE_IDR_Addr (GPIOE_BASE + 8) // 0X40011808
#define GPIOF_IDR_Addr (GPIOF_BASE + 8) // 0X40011C08
#define GPIOG_IDR_Addr (GPIOG_BASE + 8) // 0X40012008

#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x02000000 + ((addr & 0x00FFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr) *((volatile unsigned long *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))

#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr, n) //输出
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr, n)  //输入

#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr, n) //输出
#define PBin(n) BIT_ADDR(GPIOB_IDR_Addr, n)  //输入

#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr, n) //输出
#define PCin(n) BIT_ADDR(GPIOC_IDR_Addr, n)  //输入

#define PDout(n) BIT_ADDR(GPIOD_ODR_Addr, n) //输出
#define PDin(n) BIT_ADDR(GPIOD_IDR_Addr, n)  //输入

#define PEout(n) BIT_ADDR(GPIOE_ODR_Addr, n) //输出
#define PEin(n) BIT_ADDR(GPIOE_IDR_Addr, n)  //输入

#define PFout(n) BIT_ADDR(GPIOF_ODR_Addr, n) //输出
#define PFin(n) BIT_ADDR(GPIOF_IDR_Addr, n)  //输入

#define PGout(n) BIT_ADDR(GPIOG_ODR_Addr, n) //输出
#define PGin(n) BIT_ADDR(GPIOG_IDR_Addr, n)  //输入
#endif                                       /* __OJ_GPIO_H*/