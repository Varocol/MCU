#include "Libraries.h"
/*
   本实验采用USART1
   实验一：使用DMA的串口发送验证存储器到外设
   实验二：使用DMA的串口接收验证外设到存储器
   实验三：使用DMA的flash到内存验证存储器到存储器
*/
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
    //串口一的初始化
    USART_1.Init();
    //初始化dma
    USART1_TX_DMA.Init();
    // USART1_RX_DMA.Init();
    // Flash_SRAM_DMA.Init();
}
void Test()
{
    //实验一
    USART_1.Use_DMA(USART_DMA_TX, ENABLE);
    //实验二 注：将接收的数据存在公共变量区域，并通过中断函数重新发送到串口
    // USART_1.Use_DMA(USART_DMA_RX, ENABLE);
    //为啥一定要循环我也不知道，反正好用，但是实验一可以不用，实验二必须得用
    // 20220624本次实验对启动文件的堆栈进行修改，主要还是方法执行不起来，内存不够用
    //实验三
    // USART_1.Send_String(SRAMBuffer);
    while (1)
        ;
}
void End()
{
}
