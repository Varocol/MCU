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

�жϱ�־λ�б�
SPI_I2S_IT_TXE  //���ͻ������ձ�־
SPI_I2S_IT_ERR  //����(CRCERR��OVR��MODF)��־
SPI_I2S_IT_RXNE //���ջ������ǿձ�־

��������
SPI NSS  Ӳ����ģʽ PA4  ���츴��
SPI NSS  Ӳ����ģʽ PA4  ��������
SPI SCK  ��ģʽ PA5      ���츴��
SPI SCK  ��ģʽ PA5      ��������
SPI MISO ��ģʽ PA6      ��������
SPI MISO ��ģʽ PA6      ���츴��
SPI MOSI ��ģʽ PA7      ���츴��
SPI MOSI ��ģʽ PA7      ��������

ע��:
1. ������Ҫʹ��SPI_I2S_IT_TXE��־λ,��Ϊ��������ʼ����ֱ�ӽ����ж�Ȼ����ѭ��
ͬ�������Ĵ��������־λ������Ҳ���Ƽ��ڳ�ʼ��ʱʹ�øñ�־λ��
2. ʹ��SPI_I2S_IT_RXNEλʱ,�ǵ�������DR�Ĵ���,�Է�ֹ�����ж���ѭ��

*/
typedef enum
{
    SPI_DMA_RX,
    SPI_DMA_TX,
    SPI_DMA_BOTH
} SPI_DMA_enum;
//��ö����������NSS����,��Ҫ��SPI_InitStructure���Ӧ,�������Ϊ����ϸ��Ƭѡ����ģʽ
/*
  ˵����������ΪSPI_NSS_Master_Hardʱ,��ʱSSOE=0,������������GPIO���ƴ��豸
  ��Ҫʹ��Set_NSS_Pin()����NSS GPIO����,������SPI_NSS_Master_SSOE_Hard,��ʱSSOE=1,
  ��ʱ��NSS GPIO��������ΪӲ��nss��������Ӧ��GPIO����,��ʱ����Ҫʹ��Set_NSS_Pin()
  �����á�SPI_NSS_Master_SoftҲ��ͬ��,����Ҫͨ��Set_NSS_Pin()����NSS GPIO����,
  SPI_NSS_Slave_Softģʽ����ssiλ���ƣ����Կ��Բ���ҪSet_NSS_Pin(),��Ȼ��������ⲿGPIO
  �������빦��(ͨ����ȡ����ֵ������ssiλ),Ҳ���Կ���ʹ�á�
*/
typedef enum
{
    SPI_NSS_Master_Soft,
    SPI_NSS_Slave_Soft,
    SPI_NSS_Master_Hard,      //������SSOE,ʹ������GPIO���ƴ��豸
    SPI_NSS_Master_SSOE_Hard, //����SSOE
    SPI_NSS_Slave_Hard
} SPI_NSS_enum;

typedef struct
{
    SPI_TypeDef *SPIx;                       // SPIx
    SPI_InitTypeDef SPI_InitStructure;       // SPI��ʼ���ṹ��
    SPI_NSS_enum SPI_NSS;                    // SPIƬѡ����ģʽ
    NVIC_InitTypeDef SPI_NVIC_InitStructure; // SPI�жϳ�ʼ���ṹ��
    uint16_t SPI_IT_Selection;               // SPI�ж�λѡ��
    SPI_DMA_enum SPI_DMA_enum;               // SPIDMAѡ��
    FunctionalState SPI_IT_State;            // SPI�ж�ʹ(ʧ)��
    FunctionalState SPI_DMA_State;           // SPIDMAʹ(ʧ)��
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
