#include "System.h"
// ʵ��1����Ƭ���������ݵ�����
// ʵ��2�����Է������ݵ���Ƭ������Ƭ������
// ʵ��3�����Ը���Ƭ����ָ����ƵƵ�����
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
    //     // USART_1.SendData('2');//ʵ��һ
    //     //ʵ���������stm32f10x_it.C
    //     //ʵ���� ��������
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