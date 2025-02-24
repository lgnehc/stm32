#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "key.h"

uint8_t keynum;

int main(void)
{
	OLED_Init();
	Key_Init();
	Serial_Init();
	//OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,1,"TxData:");
	OLED_ShowString(3,1,"RxData:");
	//OLED_Clear();
	
	
	//发送固定长度的数据包，包头包尾已经封装好
	Serial_TxPacket[0] = 0x01;       //数组声明在serial文件
	Serial_TxPacket[1] = 0x02;
	Serial_TxPacket[2] = 0x03;
	Serial_TxPacket[3] = 0x04;
	//Serial_SendPacket();
	
	
	while(1){
		keynum = Key_GetNum();
		if(keynum == 1)     //按键按下
		{
			//按键按下发送数据
			Serial_TxPacket[0] ++; 
			Serial_TxPacket[1] ++;
			Serial_TxPacket[2] ++;
			Serial_TxPacket[3] ++;
			Serial_SendPacket();
			//显示数据
			OLED_ShowHexNum(2,1,Serial_TxPacket[0],2);
			OLED_ShowHexNum(2,4,Serial_TxPacket[1],2);
			OLED_ShowHexNum(2,7,Serial_TxPacket[2],2);
			OLED_ShowHexNum(2,10,Serial_TxPacket[3],2);
		}
		
		
		 if(Serial_GetRxFlag() == 1)
		 {
			 //显示接收数据
			 OLED_ShowHexNum(4,1,Serial_RxPacket[0],2);
			 OLED_ShowHexNum(4,4,Serial_RxPacket[1],2);
			 OLED_ShowHexNum(4,7,Serial_RxPacket[2],2);
			 OLED_ShowHexNum(4,10,Serial_RxPacket[3],2);
		 }
	}
		
}
