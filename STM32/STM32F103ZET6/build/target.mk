###########################################################################
#  !!! This file is Auto-Generated By Embedded IDE, Don't modify it !!!
###########################################################################

# eide version
EIDE_VER = 2

# current target
CUR_TARGET := Debug

# current compiler
COMPILER_TYPE := AC5

# include folders
INCLUDE_FOLDERS += .eide/deps
INCLUDE_FOLDERS += lib/cmsis
INCLUDE_FOLDERS += hal/STM32F10x_StdPeriph_Driver
INCLUDE_FOLDERS += hal/STM32F10x_StdPeriph_Driver/src
INCLUDE_FOLDERS += hal/STM32F10x_StdPeriph_Driver/inc
INCLUDE_FOLDERS += lib/STM32F10x_Driver
INCLUDE_FOLDERS += lib/CMSIS
INCLUDE_FOLDERS += libraries/USART
INCLUDE_FOLDERS += libraries/TIM
INCLUDE_FOLDERS += libraries/SysTick
INCLUDE_FOLDERS += libraries/String
INCLUDE_FOLDERS += libraries/SPI
INCLUDE_FOLDERS += libraries/Servo
INCLUDE_FOLDERS += libraries/RCC
INCLUDE_FOLDERS += libraries/PWM
INCLUDE_FOLDERS += libraries/NVIC
INCLUDE_FOLDERS += libraries/INTERRUPT
INCLUDE_FOLDERS += libraries/I2C
INCLUDE_FOLDERS += libraries/GPIO(Support Bit-Band Operations)
INCLUDE_FOLDERS += libraries/Buzzer
INCLUDE_FOLDERS += libraries/AT24C02
INCLUDE_FOLDERS += libraries/All_Headers
INCLUDE_FOLDERS += libraries/12864
INCLUDE_FOLDERS += Startup

# library search folders

# c source files
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/misc.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_adc.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_bkp.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_can.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_cec.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_crc.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_dac.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_dbgmcu.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_dma.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_exti.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_flash.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_fsmc.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_gpio.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_i2c.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_iwdg.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_pwr.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_rcc.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_rtc.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_sdio.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_spi.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_tim.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_usart.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/src/stm32f10x_wwdg.c
C_SOURCES += hal/STM32F10x_StdPeriph_Driver/system_stm32f10x.c
C_SOURCES += libraries/USART/USART_DEBUG.c

# cpp source files
CPP_SOURCES += libraries/12864/LCD_12864_Parallel.cpp
CPP_SOURCES += libraries/12864/LCD_12864_Serial.cpp
CPP_SOURCES += libraries/AT24C02/AT24C02.cpp
CPP_SOURCES += libraries/Buzzer/Buzzer.cpp
CPP_SOURCES += libraries/GPIO(Support Bit-Band Operations)/GPIO.cpp
CPP_SOURCES += libraries/I2C/I2C.cpp
CPP_SOURCES += libraries/INTERRUPT/stm32f10x_it.cpp
CPP_SOURCES += libraries/NVIC/NVIC.cpp
CPP_SOURCES += libraries/PWM/PWM.cpp
CPP_SOURCES += libraries/RCC/RCC.cpp
CPP_SOURCES += libraries/SPI/SPI.cpp
CPP_SOURCES += libraries/Servo/Servo.cpp
CPP_SOURCES += libraries/SysTick/SysTick.cpp
CPP_SOURCES += libraries/TIM/TIM.cpp
CPP_SOURCES += libraries/USART/USART.cpp

# asm source files
ASM_SOURCES += Startup/startup_stm32f10x_hd.s

# object files

# macro defines
DEFINES += USE_STDPERIPH_DRIVER
DEFINES += STM32F10X_HD
DEFINES += ARM_MATH_CM3