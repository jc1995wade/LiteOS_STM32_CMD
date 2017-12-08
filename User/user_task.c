/* Include ---------------------------------------- */
// Huawei LiteOS相关头文件
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

//STM硬件及驱动相关头文件
#include "stm32f10x.h"
#include "led.h"
#include "cmd.h"
#include "usart.h"

void Delay(__IO u32 nCount);

#define SOFT_DELAY Delay(0x0FFFFF);

UINT32 g_TestTskHandle;


void Delay(__IO uint32_t nCount)// 简单延时函数
{
	for(; nCount != 0; nCount--);
}


void USART1_IRQHnadler(void)
{
	GPIO_SetBits(GPIOC,LED3);
}


/* 硬件初始化 */
void hardware_init(void)
{
	
	LED_Init();
	GPIO_SetBits(GPIOC,LED);
	USART1_Config();
	
  //LOS_HwiCreate(37,0,0,USART1_IRQHnadler,NULL);
}



/* LED0 闪烁 */
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
	
	
		uwRet = LOS_TaskDelay(5000);  // 操作系统延时函数
#else
		//清空cmd内容
		for(i=0; i<MAX_CMD_NAME_LENGTH; i++)
		{
			cmd[i] = '\0'; 
		}
		
		uart_get_string((unsigned char *)cmd);  // 串口接受数据
		
		/* 输入控制命令式 */
		/* 解析并执行对应命令函数 */
		match_cmd(cmd);
		uart_send_string((unsigned char *)cmd);   // 串口发送数据
		
#endif

		
		if(uwRet != LOS_OK)
			return;
	}
}

UINT32 creat_task1(void)
{
	UINT32 uwRet = LOS_OK;
	TSK_INIT_PARAM_S task_init_param;
	task_init_param.usTaskPrio = 0;    // 任务优先级
	task_init_param.pcName = "task1";  // 任务名称
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)task1; // 指定入口函数
	task_init_param.uwStackSize = LOSCFG_BASE_CORE_TSK_DEFAULT_STACK_SIZE; // 设置任务堆栈大小
	task_init_param.uwResved = LOS_TASK_STATUS_DETACHED;
	uwRet = LOS_TaskCreate(&g_TestTskHandle, &task_init_param); //调用任务创建函数
	
	if(uwRet != LOS_OK)
	{
		return uwRet;
	}
	
	return uwRet;
}

/* LED1 闪烁 */
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
	hardware_init();         // 初始化硬件设备
	
	
	SOFT_DELAY;
	uwRet = creat_task1();   // 创建任务1
	
	if(uwRet !=LOS_OK)
	{
		return uwRet;
	}
	uwRet = creat_task2();   // 创建任务2
	
	if(uwRet !=LOS_OK)
	{
		return uwRet;
	}
	
	return LOS_OK;
}
/*********************************************END OF FILE**********************/






