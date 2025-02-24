#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "KEY.h"


int main(void){
	OLED_Init();
	Key_Init();
	
	OLED_ShowString(1,1,"WWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET)
	{
		OLED_ShowString(2,1,"WWDGRST");
		Delay_ms(500);
		OLED_ShowString(2,1,"       ");
		Delay_ms(100);

		RCC_ClearFlag();
	}
	else
	{
		OLED_ShowString(3,1,"RST");
		Delay_ms(500);
		OLED_ShowString(3,1,"   ");
		Delay_ms(100);
	}
	
	//喂狗初始化
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_WWDGEN,ENABLE);
	
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	WWDG_SetWindowValue(0X40 | 21);     //30ms
	WWDG_Enable(0X40 | 54);				//50ms，这个使能会喂一次狗
	
	
	while(1)
	{
		Key_GetNum();    //函数里面有循环检测，这里如果按住不放会一直循环导致超时
		
		OLED_ShowString(4,1,"FEEDING");
		Delay_ms(20);
		OLED_ShowString(4,1,"       ");
		Delay_ms(15);
		
		WWDG_SetCounter(0X40 | 54);
	}
	
}
