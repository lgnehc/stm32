#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h" 
#include "Key.h"

int main(void){
	uint8_t KeyNum;
	LED_Init();
	Key_Init();
	
	while(1){
		KeyNum = Key_GetNum();
		
		if(KeyNum == 1){   //表示按键B1按下
			LED1_Turn();	
		}
		if(KeyNum == 2){   //表示按键B11按下
			LED2_Turn();	
		}
			
		
	}
	
}
