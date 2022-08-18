#include "USART_DEBUG.h"
//重定向c库函数printf到串口,重定向后可使用printf函数,前提是得开启DEBUG_USARTx
int fputc(int ch, FILE *f)
{
	/* 发送一个字节数据到串口 */
	USART_SendData(DEBUG_USARTx, (uint8_t)ch);

	/* 等待发送完成 */
	while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET)
		;
	while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TC) == RESET)
		;
	return (ch);
}
//重定向c库函数scanf到串口,重定向后可使用scanf、getchar等函数,前提是得开启DEBUG_USARTx,要关闭RXNE中断才可以正常使用
int fgetc(FILE *f)
{
	/* 等待串口输入数据 */
	while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET)
		;

	return (int)USART_ReceiveData(DEBUG_USARTx);
}
