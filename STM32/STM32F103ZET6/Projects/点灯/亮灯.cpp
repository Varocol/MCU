#include"stm32f10x.h"
#define  LED_GPIO_PORT  GPIOB
#define  LED_GPIO_CLK   RCC->APB2ENR |= 1<<3
#define  LED_GPIO_PIN   GPIO_Pin_All
int main()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    //��GPIOBʱ��
    LED_GPIO_CLK;
    //����GPIOB��ģʽ
    //GPIOB->CRH |= 1<<(4*4);
    //����ODR�Ĵ���
    //GPIOB->ODR &= ~(1<<12);
    //GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    //��λ |= ���� &=~()
    GPIO_InitStructure.GPIO_Pin=LED_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_ResetBits(LED_GPIO_PORT,LED_GPIO_PIN);
}