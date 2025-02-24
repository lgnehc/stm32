#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Encoder.h"


int main(void){
	OLED_Init();
	OLED_ShowString(1,1,"Hello world!!");
	//OLED_Clear();
	Encoder_Init();
	
	OLED_ShowString(2,1,"Count:");
	
	//int16_t num = Encoder_Get_Cnt();
	while(1)
	{
		OLED_ShowNum(2,7,Encoder_Get_Cnt(),6);
	}
	
}
