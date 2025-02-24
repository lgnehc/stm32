#include "stm32f10x.h"                  // Device header

/**
  * 函    数：LED初始化
  * 参    数：无
  * 返 回 值：无
  */
void Buzzer_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//初始化为推挽输出
	
	/*设置GPIO初始化后的默认电平*/
	//GPIO_SetBits(GPIOB, GPIO_Pin_14);				
}


void Buzzer_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_14);		//低电平响
}


void Buzzer_OFF(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_14);		
}

/*
void Buzzer_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_14) == 0)		
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_14);					
	}
	else													
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);					
	}
}
*/
