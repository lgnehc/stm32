#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "KEY.h"


int main(void){
	OLED_Init();
	Key_Init();
	
	OLED_ShowString(1,1,"IWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)
	{
		OLED_ShowString(2,1,"IWDGRST");
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
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(2499);          //1000ms需要喂狗
	IWDG_ReloadCounter();
	IWDG_Enable();
	
	while(1)
	{
		Key_GetNum();    //函数里面有循环检测，这里如果按住不放会一直循环导致超时
		
		IWDG_ReloadCounter();
		OLED_ShowString(4,1,"FEEDING");
		Delay_ms(200);
		OLED_ShowString(4,1,"       ");
		Delay_ms(600);
		
	}
	
}
