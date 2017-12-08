#include "hard_led.h"
#include "cmd.h"

void led_cmd_init(void);
void led0_cmd_init(void);
/*******************************************************************************
* �� �� ��         : delay
* ��������		   : ��ʱ������delay(6000000)��ʱԼ1s
* ��    ��         : i
* ��    ��         : ��
*******************************************************************************/
void delay(u32 i)	  
{
	while(i--);
}

/*******************************************************************************
* �� �� ��         : LED_Init
* ��������		   : LED��ʼ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void LED_Init()	  //�˿ڳ�ʼ��
{
	GPIO_InitTypeDef GPIO_InitStructure; //����һ���ṹ�������������ʼ��GPIO

	SystemInit();	//ʱ�ӳ�ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=LED;  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(GPIOC,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
	led_cmd_init();
}

/* LED �� */
static void led_on(void)
{
	GPIO_ResetBits(GPIOC,LED3);
	
}
/* LED �� */
static void led_off(void)
{
	GPIO_SetBits(GPIOC,LED3);
}

/* ע��LED�������� */
void led_cmd_init(void)
{
	CMD led_cmds[] = {
		{"led3 on", led_on},
		{"led3 off", led_off}
	};
	
	/* ע������ */
	register_cmds(led_cmds, 2);
}
