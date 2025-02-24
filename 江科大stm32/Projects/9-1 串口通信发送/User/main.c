#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"


int main(void){
	OLED_Init();
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,3,"Hello world!!");
	//OLED_Clear();
	
	Serial_Init();
	//Serial_SendByte(0X41);
	//Serial_SendByte('B');
	
	//发送数组打印
	uint8_t Arr[] = {0x41,0x42,0x43,0x44};        //ABCD
	uint8_t len = sizeof(Arr)/sizeof(Arr[0]);
	Serial_SendArray(Arr,len);
	
	Serial_SendString("\r\n Hello world ! ! ! \r\n" );
	Serial_SendNumber(12345,5);
	
	//移植打印函数1
	printf("\r\nnum1 = %d \r\n",665);
	printf("你好，世界1 \r\n");
	
	//移植打印函数2
	char String[100];
	sprintf(String,"num2 = %d \r\n",666);
	Serial_SendString(String);
	
	sprintf(String,"你好，世界2 \r\n");
	Serial_SendString(String);
	
	
	//移植打印函数3,对打印函数2进行封装
	Serial_Printf("num3 = %d \r\n",667);
	Serial_Printf("你好，世界3 \r\n");
	
	
	while(1){

	}
	
}
