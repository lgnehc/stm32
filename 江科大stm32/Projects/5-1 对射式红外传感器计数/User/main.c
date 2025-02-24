#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "CountSensor.h"


int main(void){
	OLED_Init();
	OLED_ShowString(1,1,"Hello world!!");
	//OLED_Clear();
	
	CountSensor_Init();
	
	OLED_ShowString(2,1,"Count:");
	while(1)
	{
		OLED_ShowNum(2,7,Get_Cnt(),5);
	}
	
}
