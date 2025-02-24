#include "stm32f10x.h"                  // Device header


void LightSensor_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//GPIO_ResetBits(GPIOB, GPIO_Pin_15);	
				
}


uint8_t LightSensor_Get(void)
{
	//有光指示灯亮，输出高电平;无光指示灯灭，输出低电平
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);
}
