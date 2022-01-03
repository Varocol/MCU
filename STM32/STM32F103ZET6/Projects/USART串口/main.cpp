#include "bsp_conf.h"
#include "bsp_led.h"
//实验1；单片机发送数据到电脑
//实验2：电脑发送数据到单片机，单片机返送
//实验3：电脑给单片机发指令，控制灯的亮灭
const char *str =
    "-------------------金辰星我爱你------------------\n$$$_____$$$$$$$$$$$$$$$_$$$_______$$$_$$$$$$$$$$\n$$$____$$$____$$$____$$$_$$$_____$$$__$$$_______\n$$$____$$$___________$$$_$$$_____$$$__$$$_______\n$$$_____$$$_________$$$___$$$___$$$___$$$$$$$$__\n$$$______$$$_______$$$_____$$$_$$$____$$$_______\n$$$_______$$$_____$$$______$$$_$$$____$$$_______\n$$$$$$$$$___$$$_$$$_________$$$$$_____$$$$$$$$$$\n";
char s[100];
int main()
{
     LED_GPIOInit();
     GPIO_InitTypeDef GPIOInitStructure = LED.Get_GPIOInitStructure();
     GPIOInitStructure.GPIO_Pin = GPIO_Pin_13;
     LED.Update(GPIOB, GPIOInitStructure);
     UART_5.Init();
     while(1)
     {
          // USART_1.Send_String((uint8_t*)str);
          printf(str);
          // USART_1.SendByte('2');//实验一
          //实验二、三见stm32f10x_it.C
          //实验四 发送中文
     }
    //  while(1)
    //  {
    //      if(scanf("%s",s))
    //      {
    //           printf("%s\n",s);
    //      }
    //  }
}