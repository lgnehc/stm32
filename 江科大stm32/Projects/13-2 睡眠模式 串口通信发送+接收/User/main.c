#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

int main(void){
	OLED_Init();
	//OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,1,"RxData:");
	//OLED_Clear();
	
	Serial_Init();
	
	while(1)
	{
		/*
		if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET){
			RXdata = USART_ReceiveData(USART1);
			OLED_ShowHexNum(2,1,RXdata,4);
		}
		*/
		
		if(Serial_GetRxFlag() == 1)
		{
			RxData = Serial_GetRxData();    //接受的是16进制数据
			Serial_SendByte(RxData);
			OLED_ShowHexNum(1,8,RxData,2);
		}
		
		OLED_ShowString(2,1,"Running:");
		Delay_ms(100);
		OLED_ShowString(2,1,"        ");
		Delay_ms(100);
		
		
		__WFI();
	}
	
}
