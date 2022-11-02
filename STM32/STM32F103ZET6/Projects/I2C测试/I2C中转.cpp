#include <System.h>

/*
    STM32ģ����תI2C����:
        ʹ��I2C1���ӻ�����ָ��,I2C2����������ָ��
        I2C1���Ͻ���,��ͨ��DMA���뻺�����С�
        I2C2���Ϸ���,���ѵõ������ݷ���USART�Ļ������С�
        USARTʹ��DMA�������ݡ�
*/

I2C I2C_T_1;
I2C I2C_T_2;

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
    // ��ʼ��ϵͳ
    system_init();
    // ��ʼ������I2C
    I2C_InitTypeDef I2C1_InitStructure = {
        .I2C_ClockSpeed = 400000,
        .I2C_Mode = I2C_Mode_I2C,
        .I2C_DutyCycle = I2C_DutyCycle_16_9,
        .I2C_OwnAddress1 = 0x03,
        .I2C_Ack = I2C_Ack_Enable,
        .I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit};
    I2C_InitTypeDef I2C2_InitStructure = {
        .I2C_ClockSpeed = 100000,
        .I2C_Mode = I2C_Mode_I2C,
        .I2C_DutyCycle = I2C_DutyCycle_16_9,
        .I2C_OwnAddress1 = 0xB0,
        .I2C_Ack = I2C_Ack_Enable,
        .I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit};
    // I2C1 �����ж�
    NVIC_InitTypeDef I2C1_ER_NVIC_InitStructure = {
        .NVIC_IRQChannel = I2C1_ER_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 6,
        .NVIC_IRQChannelCmd = ENABLE};
    // I2C1 �¼��ж�
    NVIC_InitTypeDef I2C1_EV_NVIC_InitStructure = {
        .NVIC_IRQChannel = I2C1_EV_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 7,
        .NVIC_IRQChannelCmd = ENABLE};
    // I2C2 �����ж�
    NVIC_InitTypeDef I2C2_ER_NVIC_InitStructure = {
        .NVIC_IRQChannel = I2C2_ER_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 8,
        .NVIC_IRQChannelCmd = ENABLE};
    // I2C2 �¼��ж�
    NVIC_InitTypeDef I2C2_EV_NVIC_InitStructure = {
        .NVIC_IRQChannel = I2C2_EV_IRQn,
        .NVIC_IRQChannelPreemptionPriority = 0,
        .NVIC_IRQChannelSubPriority = 9,
        .NVIC_IRQChannelCmd = ENABLE};
    I2C_Param I2C1_Param = {
        .I2Cx = I2C1,
        .I2C_InitStructure = I2C1_InitStructure,
        .I2C_ER_NVIC_InitStructure = I2C1_ER_NVIC_InitStructure,
        .I2C_EV_NVIC_InitStructure = I2C1_EV_NVIC_InitStructure,
        .I2C_Pin_Remap = I2C_Default,
        .I2C_IT_Selection = I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR,
        .I2C_IT_State = ENABLE,
        .I2C_DMA_State = DISABLE};
    I2C_Param I2C2_Param = {
        .I2Cx = I2C2,
        .I2C_InitStructure = I2C2_InitStructure,
        .I2C_ER_NVIC_InitStructure = I2C2_ER_NVIC_InitStructure,
        .I2C_EV_NVIC_InitStructure = I2C2_EV_NVIC_InitStructure,
        .I2C_Pin_Remap = I2C_Default,
        .I2C_IT_Selection = I2C_IT_BUF | I2C_IT_EVT | I2C_IT_ERR,
        .I2C_IT_State = DISABLE,
        .I2C_DMA_State = DISABLE};
    I2C_T_1 = I2C(I2C1_Param);
    I2C_T_2 = I2C(I2C2_Param);
    I2C_T_1.Init();
    I2C_T_2.Init();
}
void Test()
{
    
}
void End()
{
}