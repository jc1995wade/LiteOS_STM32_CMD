#include "hard_led.h"
#include "cmd.h"

void led_cmd_init(void);
void led0_cmd_init(void);
/*******************************************************************************
* 函 数 名         : delay
* 函数功能		   : 延时函数，delay(6000000)延时约1s
* 输    入         : i
* 输    出         : 无
*******************************************************************************/
void delay(u32 i)	  
{
	while(i--);
}

/*******************************************************************************
* 函 数 名         : LED_Init
* 函数功能		   : LED初始化函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void LED_Init()	  //端口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure; //声明一个结构体变量，用来初始化GPIO

	SystemInit();	//时钟初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=LED;  //选择你要设置的IO口
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	   /* 初始化GPIO */
	led_cmd_init();
}

/* LED 开 */
static void led_on(void)
{
	GPIO_ResetBits(GPIOC,LED3);
	
}
/* LED 关 */
static void led_off(void)
{
	GPIO_SetBits(GPIOC,LED3);
}

/* 注册LED控制命令 */
void led_cmd_init(void)
{
	CMD led_cmds[] = {
		{"led3 on", led_on},
		{"led3 off", led_off}
	};
	
	/* 注册命令 */
	register_cmds(led_cmds, 2);
}
