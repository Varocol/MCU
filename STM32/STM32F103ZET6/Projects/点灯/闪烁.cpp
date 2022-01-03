#include"stm32f10x.h"
void delay(int x)
{
    for(int i=0;i<x;i++)
    for(int j=0;j<1000;j++)
    {
        __NOP();
    }
}
int main()
{
    RCC->APB2ENR |= 1<<3;
    GPIOB->CRH |= 1<<(4*4);
    GPIOB->CRH |= 1<<(4*7);
    while(1)
    {
        GPIOB->ODR &= ~(1<<12);
        delay(800);
        GPIOB->ODR &= ~(1<<15);
        delay(500);
        GPIOB->ODR |= 1<<15;
        delay(500);
        GPIOB->ODR |=  1<<12;
        delay(800);
    }
}