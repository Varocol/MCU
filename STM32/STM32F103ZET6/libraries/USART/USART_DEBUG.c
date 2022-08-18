#include "USART_DEBUG.h"
//�ض���c�⺯��printf������,�ض�����ʹ��printf����,ǰ���ǵÿ���DEBUG_USARTx
int fputc(int ch, FILE *f)
{
	/* ����һ���ֽ����ݵ����� */
	USART_SendData(DEBUG_USARTx, (uint8_t)ch);

	/* �ȴ�������� */
	while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET)
		;
	while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TC) == RESET)
		;
	return (ch);
}
//�ض���c�⺯��scanf������,�ض�����ʹ��scanf��getchar�Ⱥ���,ǰ���ǵÿ���DEBUG_USARTx,Ҫ�ر�RXNE�жϲſ�������ʹ��
int fgetc(FILE *f)
{
	/* �ȴ������������� */
	while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET)
		;

	return (int)USART_ReceiveData(DEBUG_USARTx);
}
