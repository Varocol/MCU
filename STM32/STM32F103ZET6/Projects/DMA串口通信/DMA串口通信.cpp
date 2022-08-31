#include "Libraries.h"
/*
   ��ʵ�����USART1
   ʵ��һ��ʹ��DMA�Ĵ��ڷ�����֤�洢��������
   ʵ�����ʹ��DMA�Ĵ��ڽ�����֤���赽�洢��
   ʵ������ʹ��DMA��flash���ڴ���֤�洢�����洢��
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
    //����һ�ĳ�ʼ��
    USART_1.Init();
    //��ʼ��dma
    USART1_TX_DMA.Init();
    // USART1_RX_DMA.Init();
    // Flash_SRAM_DMA.Init();
}
void Test()
{
    //ʵ��һ
    USART_1.Use_DMA(USART_DMA_TX, ENABLE);
    //ʵ��� ע�������յ����ݴ��ڹ����������򣬲�ͨ���жϺ������·��͵�����
    // USART_1.Use_DMA(USART_DMA_RX, ENABLE);
    //Ϊɶһ��Ҫѭ����Ҳ��֪�����������ã�����ʵ��һ���Բ��ã�ʵ����������
    // 20220624����ʵ��������ļ��Ķ�ջ�����޸ģ���Ҫ���Ƿ���ִ�в��������ڴ治����
    //ʵ����
    // USART_1.Send_String(SRAMBuffer);
    while (1)
        ;
}
void End()
{
}
