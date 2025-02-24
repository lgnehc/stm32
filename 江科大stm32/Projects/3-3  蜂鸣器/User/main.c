#include "stm32f10x.h"                  // Device header
#include "Delay.h" 

int main(void){
	  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);       //默认初始化之后是低电平
	
	
	 
	while(1){
		//蜂鸣器，低电平响
		GPIO_ResetBits(GPIOB,GPIO_Pin_14 );    
		Delay_ms(100);
		GPIO_SetBits(GPIOB, GPIO_Pin_14);   
		Delay_ms(100);
		GPIO_ResetBits(GPIOB,GPIO_Pin_14 );    
		Delay_ms(100);
		GPIO_SetBits(GPIOB, GPIO_Pin_14);   
		Delay_ms(700);
	
	}
	
}
