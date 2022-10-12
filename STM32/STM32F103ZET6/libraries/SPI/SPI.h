#ifndef __OJ_SPI_H
#define __OJ_SPI_H
#include "GPIO.h"
#include "RCC.h"
#include "NVIC.h"
/*
        NSS     SCK     MISO    MOSI
SPI1:   PA4     PA5     PA6     PA7
SPI2:   PB12    PB13    PB14    PB15
SPI3:   PA15    PB3     PB4     PB5

中断标志位列表
SPI_I2S_IT_TXE  //发送缓冲器空标志
SPI_I2S_IT_ERR  //错误(CRCERR、OVR、MODF)标志
SPI_I2S_IT_RXNE //接收缓冲器非空标志

引脚配置
SPI NSS  硬件主模式 PA4  推挽复用
SPI NSS  硬件从模式 PA4  上拉输入
SPI SCK  主模式 PA5      推挽复用
SPI SCK  从模式 PA5      浮空输入
SPI MISO 主模式 PA6      上拉输入
SPI MISO 从模式 PA6      推挽复用
SPI MOSI 主模式 PA7      推挽复用
SPI MOSI 从模式 PA7      上拉输入

注意:
1. 尽量不要使用SPI_I2S_IT_TXE标志位,因为这会在你初始化后直接进入中断然后死循环
同理其他的带有这类标志位的外设也不推荐在初始化时使用该标志位。
2. 使用SPI_I2S_IT_RXNE位时,记得先清理DR寄存器,以防止进入中断死循环

*/
typedef enum
{
    SPI_DMA_RX,
    SPI_DMA_TX,
    SPI_DMA_BOTH
} SPI_DMA_enum;
//该枚举用于配置NSS引脚,需要和SPI_InitStructure相对应,可以理解为更详细的片选引脚模式
/*
  说明：当配置为SPI_NSS_Master_Hard时,此时SSOE=0,采用其他空闲GPIO控制从设备
  需要使用Set_NSS_Pin()设置NSS GPIO对象,若设置SPI_NSS_Master_SSOE_Hard,此时SSOE=1,
  此时的NSS GPIO对象被配置为硬件nss引脚所对应的GPIO对象,此时不需要使用Set_NSS_Pin()
  来设置。SPI_NSS_Master_Soft也是同理,都需要通过Set_NSS_Pin()配置NSS GPIO对象,
  SPI_NSS_Slave_Soft模式下由ssi位控制，所以可以不需要Set_NSS_Pin(),当然如果是用外部GPIO
  当作输入功能(通过读取输入值来决定ssi位),也可以考虑使用。
*/
typedef enum
{
    SPI_NSS_Master_Soft,
    SPI_NSS_Slave_Soft,
    SPI_NSS_Master_Hard,      //不开启SSOE,使用其他GPIO控制从设备
    SPI_NSS_Master_SSOE_Hard, //开启SSOE
    SPI_NSS_Slave_Hard
} SPI_NSS_enum;

typedef struct
{
    SPI_TypeDef *SPIx;                       // SPIx
    SPI_InitTypeDef SPI_InitStructure;       // SPI初始化结构体
    SPI_NSS_enum SPI_NSS;                    // SPI片选引脚模式
    NVIC_InitTypeDef SPI_NVIC_InitStructure; // SPI中断初始化结构体
    uint16_t SPI_IT_Selection;               // SPI中断位选择
    SPI_DMA_enum SPI_DMA_enum;               // SPIDMA选择
    FunctionalState SPI_IT_State;            // SPI中断使(失)能
    FunctionalState SPI_DMA_State;           // SPIDMA使(失)能
} SPI_Param;
class SPI
{
private:
    SPI_Param SPIx_Param;
    GPIO NSS;
    void Set_NSS_Val(uint8_t BitVal);

public:
    SPI();
    ~SPI();
    SPI(SPI_Param SPIx_Param);
    void Send_Data(uint16_t data);
    void Send_Buffer(uint8_t *buffer, uint32_t cnt);
    void Send_Buffer(uint16_t *buffer, uint32_t cnt);
    uint16_t Receive_Data();
    void Pin_Init();
    void NSS_High();
    void NSS_Low();
    void Set_NSS_Pin(GPIO &NSS_Soft);
    void Update(SPI_Param SPIx_Param);
    void Set_SPI_Param(SPI_Param SPIx_Param);
    void DMACmd(SPI_DMA_enum SPI_DMA_enum, FunctionalState NewState);
    void ITConfig(uint8_t SPI_I2S_IT, FunctionalState NewState);
    void CalculateCRC(FunctionalState NewState);
    void ClearCRC();
    void TransmitCRC();
    uint16_t GetCRC(uint8_t SPI_CRC);
    void Init();
    void Enable();
    void Disable();

    void RCC_Enable();
    void RCC_Disable();
    static void RCC_Enable(SPI_TypeDef *SPIx);
    static void RCC_Disable(SPI_TypeDef *SPIx);
};

#endif /*__OJ_SPI_H*/
