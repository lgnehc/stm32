#include "stm32f10x.h"                  // Device header

void CountSensor_Init(void)
{
	//1.需要配置gpio,afio,exit/nvic
	
	//1配置GPIO/AFIO时钟，另外两个默认打开
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//2.1初始化GPIO口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//2.2初始化AFIO口
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	
	//2.3初始化exit 见exit.h文件
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line14;              //端口
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;   			  //是否允许中断
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;      //中断还是事件
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  //边沿触发模式
	EXTI_Init(&EXTI_InitStruct);
    
	//2.4配置NVIC
	//设置优先级分组，2位抢占和4-2位响应
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}	


uint16_t cnt = 0;
void EXTI15_10_IRQHandler(void)
{
	//判断是否是14号线的中断信号，如果是，那么执行完中断函数要进行清除标志位
	if(EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		cnt++;
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}


uint16_t Get_Cnt(void)
{
	return cnt; 
}
