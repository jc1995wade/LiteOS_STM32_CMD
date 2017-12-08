#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>
//#include "stm32f10x_usart.h"
void USART1_Config(void);

void uart_send_string(unsigned char *str);
void uart_get_string(unsigned char *str);
//int fputc(int ch, FILE *f);
//void USART1_printf(USART_TypeDef* USARTx, uint8_t *Data,...);

#endif /* __USART1_H */
