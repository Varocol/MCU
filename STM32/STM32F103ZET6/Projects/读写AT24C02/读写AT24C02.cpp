#include "System.h"
AT24C02 ee;
uint8_t aaa[26] =
    {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
uint8_t list[256];
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
    AT24C02_Param param =
        {
            .AT24C02_ADDR = 0xA0,
            .I2Cx = I2C_1};
    USART_1.Init();
    ee = AT24C02(param);
    ee.Init();
}
void Test()
{
    while (1)
    {
        ee.Write_Byte(0, 'z');
        SysTick_Operate::Delay_ms(1000);
        printf("1");
    }
    // ee.Write_Buffer(255, aaa, 26);
    // if (ee.PROCESS_CONDITION)
    // {
    //     printf("发送成功!\n发送的字节为:\n");
    //     for (int i = 0; i < 26; i++)
    //     {
    //         printf("%c\n", aaa[i]);
    //     }
    // }
    // ee.Read_Buffer(255, list, 26);
    // if (ee.PROCESS_CONDITION)
    // {
    //     printf("接收成功!\n接收的字节为:\n");
    // }
    // if (!ee.PROCESS_CONDITION)
    // {
    //     printf("I2C通讯失败!\n");
    // }
    // else
    // {
    //     for (int i = 0; i < 26; i++)
    //     {
    //         printf("%c\n", list[i]);
    //     }
    // }
}
void End()
{
}