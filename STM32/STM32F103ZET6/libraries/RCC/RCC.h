#ifndef __OJ_RCC_H
#define __OJ_RCC_H
#include "stm32f10x.h"
typedef struct
{
    __IO uint32_t CRL;
} FLITF_TypeDef;
typedef struct
{
    __IO uint32_t CRL;
} SRAM_TypeDef;
typedef struct
{
    __IO uint32_t CRL;
} USB_TypeDef;

typedef enum
{
    HSI,
    HSE,
    PLL
} Clock_Source;

#define FLITF ((FLITF_TypeDef *)0x00)
#define SRAM ((SRAM_TypeDef *)0x00)
#define USB ((USB_TypeDef *)0x00)

class RCC_Operate
{
private:
public:
    RCC_Operate();
    ~RCC_Operate();
    static RCC_ClocksTypeDef Get_ClocksFreq();
    static uint32_t Get_SYSCLK_Frequency();
    static uint32_t Get_HCLK_Frequency();
    static uint32_t Get_PCLK1_Frequency();
    static uint32_t Get_PCLK2_Frequency();
    static uint32_t Get_ADCCLK_Frequency();
    static Clock_Source Get_SYSCLKSource();
    static void Backup_Reset();
    static void HSE_SetSysClock(uint32_t pllmul);
    static void HSI_SetSysClock(uint32_t pllmul);
    static void RCC_Config(ADC_TypeDef *ADCX, FunctionalState NewState);
    static void RCC_Config(AFIO_TypeDef *AFIOX, FunctionalState NewState);
    static void RCC_Config(BKP_TypeDef *BKPX, FunctionalState NewState);
    static void RCC_Config(CAN_TypeDef *CANX, FunctionalState NewState);
    static void RCC_Config(CRC_TypeDef *CRCX, FunctionalState NewState);
    static void RCC_Config(DAC_TypeDef *DACX, FunctionalState NewState);
    static void RCC_Config(DMA_TypeDef *DMAX, FunctionalState NewState);
    static void RCC_Config(FLITF_TypeDef *FLITFX, FunctionalState NewState);
    static void RCC_Config(FSMC_Bank1_TypeDef *FSMC_Bank1X, FunctionalState NewState);
    static void RCC_Config(FSMC_Bank2_TypeDef *FSMC_Bank2X, FunctionalState NewState);
    static void RCC_Config(FSMC_Bank3_TypeDef *FSMC_Bank3X, FunctionalState NewState);
    static void RCC_Config(FSMC_Bank4_TypeDef *FSMC_Bank4X, FunctionalState NewState);
    static void RCC_Config(FSMC_Bank1E_TypeDef *FSMC_Bank1EX, FunctionalState NewState);
    static void RCC_Config(GPIO_TypeDef *GPIOX, FunctionalState NewState);
    static void RCC_Config(I2C_TypeDef *I2CX, FunctionalState NewState);
    static void RCC_Config(PWR_TypeDef *PWRX, FunctionalState NewState);
    static void RCC_Config(SDIO_TypeDef *SDIOX, FunctionalState NewState);
    static void RCC_Config(SPI_TypeDef *SPIX, FunctionalState NewState);
    static void RCC_Config(SRAM_TypeDef *SRAMX, FunctionalState NewState);
    static void RCC_Config(TIM_TypeDef *TIMX, FunctionalState NewState);
    static void RCC_Config(USART_TypeDef *USARTX, FunctionalState NewState);
    static void RCC_Config(USB_TypeDef *USBX, FunctionalState NewState);
    static void RCC_Config(WWDG_TypeDef *WWDGX, FunctionalState NewState);
    static void RCC_Config(RTC_TypeDef *RTCx, FunctionalState NewState);
    static uint32_t ADCX_Convert_RCC(ADC_TypeDef *ADCX);
    static uint32_t AFIO_Convert_RCC(AFIO_TypeDef *AFIOX);
    static uint32_t BKP_Convert_RCC(BKP_TypeDef *BKPX);
    static uint32_t CAN_Convert_RCC(CAN_TypeDef *CANX);
    static uint32_t CRC_Convert_RCC(CRC_TypeDef *CRCX);
    static uint32_t DAC_Convert_RCC(DAC_TypeDef *DACX);
    static uint32_t DMA_Convert_RCC(DMA_TypeDef *DMAX);
    static uint32_t FLITF_Convert_RCC(FLITF_TypeDef *FLITFX);
    static uint32_t FSMC_Bank1_Convert_RCC(FSMC_Bank1_TypeDef *FSMC_Bank1X);
    static uint32_t FSMC_Bank2_Convert_RCC(FSMC_Bank2_TypeDef *FSMC_Bank2X);
    static uint32_t FSMC_Bank3_Convert_RCC(FSMC_Bank3_TypeDef *FSMC_Bank3X);
    static uint32_t FSMC_Bank4_Convert_RCC(FSMC_Bank4_TypeDef *FSMC_Bank4X);
    static uint32_t FSMC_Bank1E_Convert_RCC(FSMC_Bank1E_TypeDef *FSMC_Bank1EX);
    static uint32_t GPIOX_Convert_RCC(GPIO_TypeDef *GPIOX);
    static uint32_t I2CX_Convert_RCC(I2C_TypeDef *I2CX);
    static uint32_t PWRX_Convert_RCC(PWR_TypeDef *PWRX);
    static uint32_t SDIOX_Convert_RCC(SDIO_TypeDef *SDIOX);
    static uint32_t SPIX_Convert_RCC(SPI_TypeDef *SPIX);
    static uint32_t SRAMX_Convert_RCC(SRAM_TypeDef *SRAMX);
    static uint32_t TIMX_Convert_RCC(TIM_TypeDef *TIMX);
    static uint32_t USARTX_Convert_RCC(USART_TypeDef *USARTX);
    static uint32_t USBX_Convert_RCC(USB_TypeDef *USBX);
    static uint32_t WWDGX_Convert_RCC(WWDG_TypeDef *WWDGX);
};

#endif /*__BSP_RCC_CONFIG_H*/