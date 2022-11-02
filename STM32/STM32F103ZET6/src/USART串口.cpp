#include "System.h"
// 实验1；单片机发送数据到电脑
// 实验2：电脑发送数据到单片机，单片机返送
// 实验3：电脑给单片机发指令，控制灯的亮灭
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
    LED_1.Init();
    USART_1.Init();
}
void Test()
{
    USART_1.Send_String_DMA("123");
    // while (1)
    // {
    //     USART_1.Send_String(SendBuffer);
    //     // printf(str);
    //     // USART_1.SendData('2');//实验一
    //     //实验二、三见stm32f10x_it.C
    //     //实验四 发送中文
    //     SysTick_Operate::Delay_ms(500);
    // }
    //  while(1)
    //  {
    //      if(scanf("%s",s))
    //      {
    //           printf("%s\n",s);
    //      }
    //  }
}
void End()
{
}