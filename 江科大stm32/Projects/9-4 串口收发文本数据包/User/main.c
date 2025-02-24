#include "stm32f10x.h"                  // Device header
//#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "Serial.h"
#include <string.h>

uint8_t keynum;


//文本格式定义：可变包长，@开头，\r\n结尾
int main(void)
{
	LED_Init();
	OLED_Init();
	Serial_Init();
	//OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,1,"TxData:");
	OLED_ShowString(3,1,"RxData:");
	//OLED_Clear();

	
	while(1)
	{
		if(Serial_RxFlag == 1)
		{	 
			OLED_ShowString(4,1,"                ");
			OLED_ShowString(4,1,Serial_RxPacket);
		
		
			//判断是否输入LED_ON,相等则等于0
			if(strcmp(Serial_RxPacket,"LED_ON") == 0)
			{
				LED1_ON();
				Serial_SendString("LED_ON_OK\r\n");
				OLED_ShowString(2,1,"                ");
				OLED_ShowString(2,1,"LED_ON_OK");
			}
			//输入LED_OFF
			else if(strcmp(Serial_RxPacket,"LED_OFF") == 0)
			{
				LED1_OFF();
				Serial_SendString("LED_OFF_OK\r\n");
				OLED_ShowString(2,1,"                ");
				OLED_ShowString(2,1,"LED_OFF_OK");
			}
			//输入错误指令
			else
			{
				Serial_SendString("ERROR_COMMAND\r\n");
				OLED_ShowString(2,1,"                ");
				OLED_ShowString(2,1,"ERROR_COMMAND");
			}
			Serial_RxFlag = 0;     
		}
	}
}
