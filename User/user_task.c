/* Include ---------------------------------------- */
// Huawei LiteOS���ͷ�ļ�
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "los_base.h"
#include "los_config.h"
#include "los_typedef.h"
#include "los_hwi.h"
#include "los_task.h"
#include "los_sem.h"
#include "los_event.h"
#include "los_memory.h"
#include "los_queue.ph"

//STMӲ�����������ͷ�ļ�
#include "stm32f10x.h"
#include "led.h"
#include "cmd.h"
#include "usart.h"

void Delay(__IO u32 nCount);

#define SOFT_DELAY Delay(0x0FFFFF);

UINT32 g_TestTskHandle;


void Delay(__IO uint32_t nCount)// ����ʱ����
{
	for(; nCount != 0; nCount--);
}


void USART1_IRQHnadler(void)
{
	GPIO_SetBits(GPIOC,LED3);
}


/* Ӳ����ʼ�� */
void hardware_init(void)
{
	
	LED_Init();
	GPIO_SetBits(GPIOC,LED);
	USART1_Config();
	
  //LOS_HwiCreate(37,0,0,USART1_IRQHnadler,NULL);
}



/* LED0 ��˸ */
VOID task1(void)
{
	UINT32 uwRet = LOS_OK;
	UINT32 i = 0;
	char cmd[MAX_CMD_NAME_LENGTH] = {NULL};
	
	while(1)
	{
#if 0
		if(i == 0)
		{
			GPIO_SetBits(GPIOC,LED0);
		}
		else 
			GPIO_ResetBits(GPIOC,LED0);
		
		i++;
		i = i%2;
	
	
		uwRet = LOS_TaskDelay(5000);  // ����ϵͳ��ʱ����
#else
		//���cmd����
		for(i=0; i<MAX_CMD_NAME_LENGTH; i++)
		{
			cmd[i] = '\0'; 
		}
		
		uart_get_string((unsigned char *)cmd);  // ���ڽ�������
		
		/* �����������ʽ */
		/* ������ִ�ж�Ӧ����� */
		match_cmd(cmd);
		uart_send_string((unsigned char *)cmd);   // ���ڷ�������
		
#endif

		
		if(uwRet != LOS_OK)
			return;
	}
}

UINT32 creat_task1(void)
{
	UINT32 uwRet = LOS_OK;
	TSK_INIT_PARAM_S task_init_param;
	task_init_param.usTaskPrio = 0;    // �������ȼ�
	task_init_param.pcName = "task1";  // ��������
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)task1; // ָ����ں���
	task_init_param.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE; // ���������ջ��С
	task_init_param.uwResved = LOS_TASK_STATUS_DETACHED;
	uwRet = LOS_TaskCreate(&g_TestTskHandle, &task_init_param); //�������񴴽�����
	
	if(uwRet != LOS_OK)
	{
		return uwRet;
	}
	
	return uwRet;
}

/* LED1 ��˸ */
VOID task2(void)
{
	UINT32 uwRet = LOS_OK;
	UINT32 i = 0;
	while(1)
	{
		
		if(i == 0)
		{
			GPIO_SetBits(GPIOC,LED1);
		}
		else 
			GPIO_ResetBits(GPIOC,LED1);
		i++;
		i = i%2;
		
		uwRet = LOS_TaskDelay(2000);
		
		if(uwRet !=LOS_OK)
			return;
	} 
}


UINT32 creat_task2(void)
{
	UINT32 uwRet = LOS_OK;
	TSK_INIT_PARAM_S task_init_param;
	task_init_param.usTaskPrio = 0;
	task_init_param.pcName = "task2";
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)task2;
	task_init_param.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE;
	task_init_param.uwResved = LOS_TASK_STATUS_DETACHED;
	uwRet = LOS_TaskCreate(&g_TestTskHandle,&task_init_param);
	
	if(uwRet !=LOS_OK)
	{
	return uwRet;
	}
	
	return uwRet;
}


UINT32 osAppInit(void)
{
	UINT32 uwRet = 0;
	hardware_init();         // ��ʼ��Ӳ���豸
	
	
	SOFT_DELAY;
	uwRet = creat_task1();   // ��������1
	
	if(uwRet !=LOS_OK)
	{
		return uwRet;
	}
	uwRet = creat_task2();   // ��������2
	
	if(uwRet !=LOS_OK)
	{
		return uwRet;
	}
	
	return LOS_OK;
}
/*********************************************END OF FILE**********************/






