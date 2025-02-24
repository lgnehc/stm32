#include "stm32f10x.h"                  // Device header

int main(void)
{
	/*
	//1.直接控制寄存器点灯
	RCC->APB2ENR = 0X00000010;
	GPIOC->CRH   = 0X00300000;
	GPIOC->ODR   = 0X00002000;    //PC13是给低电平点亮
	*/
	
	
	
    //2.库函数模式点灯
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);    //GPIOC的时钟配置
	GPIO_InitTypeDef GPIO_InitStructure;                    //定义一个结构体变量GPIO_InitStructure
	//结构体初始化
	GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC,&GPIO_InitStructure);                  //GPIOC初始化
	//GPIO_SetBits(GPIOC,GPIO_Pin_13);         //高电平灭灯
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);     //低电平点亮    
    
	while(1)
	{
	
	}
	
}
