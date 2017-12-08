#ifndef _HARD_LED_H
#define _HARD_LED_H
#include "stm32f10x.h"
#define LED GPIO_Pin_All	//π‹Ω≈∫Í∂®“Â
#define LED0 GPIO_Pin_0
#define LED1 GPIO_Pin_1
#define LED2 GPIO_Pin_2
#define LED3 GPIO_Pin_3

void LED_Init(void);
void led_display(void);

#endif 
