#include "Libraries.h"
void Setup();
void Test();
void End();
int main()
{
    Setup();
    Test();
    End();
}
void Setup()
{
    //初始化串口
    USART_1.Init();
    //初始化信号灯
    LED_1.Init();
    //开启电源和后备寄存器时钟
    RCC_Operate::RCC_Config(PWR, ENABLE);
    RCC_Operate::RCC_Config(BKP, ENABLE);

    //开放后备寄存器
    PWR_BackupAccessCmd(ENABLE);
    //关闭侵入检测引脚
    BKP_TamperPinCmd(DISABLE);
    //设置引脚电平
    BKP_TamperPinLevelConfig(BKP_TamperPinLevel_Low);
    //清除标志位(侵入检测引脚可以在不需要VDD的时候工作,所以有可能在这期间产生入侵事件,需要手动清除)
    BKP_ClearFlag();
    //配置中断
    NVIC_InitTypeDef Tamper_InitStructure =
        {
            TAMPER_IRQn,
            0,
            1,
            ENABLE};
    NVIC_Operate Tamper_NVIC = NVIC_Operate(Tamper_InitStructure);
    Tamper_NVIC.Init();
    BKP_ITConfig(ENABLE);
    //开启入侵检测引脚
    BKP_TamperPinCmd(ENABLE);
}
void Test()
{
    //读取上电次数
    printf("上电次数:%d\n", BKP_ReadBackupRegister(BKP_DR1));
    //写入上电次数
    BKP_WriteBackupRegister(BKP_DR1, BKP_ReadBackupRegister(BKP_DR1) + 1);
    while (1)
        ;
}
void End()
{
}