#include "stm32f10x.h"                  // Device header

void LED_init(void){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP ;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_2);
}

/*
void LED1_ON(void){
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}
void LED1_OFF(void){
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
}

void LED2_ON(void){
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}
void LED2_OFF(void){
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}
*/

void LED1_turn(void){
	if(GPIO_ReadOutputDataBit(GPIOA ,GPIO_Pin_1) == 0){
		//这里读取的是输出寄存器的值，就是当前灯的状态
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
	}
	else{
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	} 
}

void LED2_turn(void){
	if(GPIO_ReadOutputDataBit(GPIOA ,GPIO_Pin_2) == 0){
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	} 
}
