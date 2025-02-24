#include "stm32f10x.h"
#include "Delay.h"

void Key_init(void){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	//GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD ;    //下拉模式默认是低电平
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU ;    //上拉模式默认是低电平
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

}

uint8_t Key_GetNum(void){
	uint8_t KeyNum = 0;
	
	//if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 1)  //默认是0，==1表示按键按下
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)  //默认是1，==0表示按键按下	
	{
		Delay_ms(20);    //消除抖动
		//while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 1)
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)   
		{
			Delay_ms(20);   //消除抖动
		}
		KeyNum = 1;
	}
	
	
	//if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 1)  //默认是0，==1表示按键按下
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)  //默认是1，==0表示按键按下	
	{
		Delay_ms(20);    //消除抖动
		//while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 1)
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)   
		{
			Delay_ms(20);   //消除抖动
		}
		KeyNum = 2;
	}
	
	return KeyNum;
}