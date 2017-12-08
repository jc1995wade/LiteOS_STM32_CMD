/**
  ******************************************************************************
  * @file    bsp_usart1.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����c��printf������usart�˿�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� iSO STM32 ������ 
  * ��̳    :http://www.chuxue123.com
  * �Ա�    :http://firestm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "usart.h"
#include "stm32f10x_usart.h"
 /**
  * @brief  USART1 GPIO ����,����ģʽ���á�115200 8-N-1
  * @param  ��
  * @retval ��
  */
void USART1_Config(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		USART_InitTypeDef USART_InitStructure;
		
		/* config USART1 clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
		
		/* USART1 GPIO config */
		/* Configure USART1 Tx (PA.09) as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		/* Configure USART1 Rx (PA.10) as input floating */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
			
		/* USART1 mode config */
		USART_InitStructure.USART_BaudRate = 9600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No ;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure); 
		USART_Cmd(USART1, ENABLE);
}


void uart_send_string(unsigned char *str)
{
	while (*str != '\0')
	{
		//*str = *str<<1;
		//*str = *str>>1;
	 	USART_SendData(USART1, (uint8_t) *str); // 0111 1111
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		str++;
	}
}



/******************************************************************************
* �������ܣ� ���ڽ����ַ�������
* ��������� ��
* ��������� str �ѽ��յ��ַ���
* ����ֵ ��  �� 
* ��    ע�� ������ \r\n Ϊ�������ַ��������ڹ����蹴ѡ���������С�ѡ��   
******************************************************************************/
void uart_get_string(unsigned char *str)
{
	unsigned char ch;
	/* �ȴ�����1�������� */
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	ch = USART_ReceiveData(USART1);

	while ((ch != '\r') && (ch != '\n'))  // ����ʱ�Իس����н���
	{
	 	*str++ = ch;
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
		ch = USART_ReceiveData(USART1);
	}

	*str = '\0';
}



#if 0

///�ض���c�⺯��printf��USART1
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ�USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf��USART1
int fgetc(FILE *f)
{
		/* �ȴ�����1�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

#endif

/*********************************************END OF FILE**********************/
