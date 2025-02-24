#include "stm32f10x.h"

void Encoder_Init(void)
{
	//1配置GPIO/AFIO时钟，另外两个默认打开
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//2.1初始化GPIO口
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//2.2初始化AFIO口
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	//2.3初始化exit 见exit.h文件
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line0 | EXTI_Line1;   //端口
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;   			  //是否允许中断
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;      //中断还是事件
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;  //边沿触发模式
	EXTI_Init(&EXTI_InitStruct);
    
	//2.4配置NVIC
	//设置优先级分组，2位抢占和4-2位响应
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
}	

int16_t Encoder_cnt = 0;

void EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0) == SET){
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0){
			Encoder_cnt--;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
} 


void EXTI1_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line1) == SET){
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0){
			Encoder_cnt++;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
} 


int16_t Encoder_Get_Cnt(void){
	return Encoder_cnt;
}
