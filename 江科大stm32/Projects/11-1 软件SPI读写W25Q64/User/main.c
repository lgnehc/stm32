#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "W25Q64.h"

uint8_t MID;
uint16_t DID;

uint8_t ArrayWrite[] = {0x41,0x42,0x43,0x44};
uint8_t ArrayRead[4];

int main(void)
{
	OLED_Init();
	W25Q64_init();
	
	OLED_ShowString(1,1,"MID:   DID:");
	OLED_ShowString(2,1,"W:");
	OLED_ShowString(3,1,"R:");
	
	W25Q64_ReadID(&MID,&DID);
	OLED_ShowHexNum(1,5,MID,2);
	OLED_ShowHexNum(1,12,DID,4);
	
	//这个需要对扇区地址有了解，一般页地址起始0xxx00（页头）--0xxxff(页尾)
	W25Q64_SectorErase(0X000000);
	W64Q25_PageProgram(0X000000,ArrayWrite,4);
	W25Q64_ReadData(0X000000, ArrayRead, 4);
	/*显示写入和读出的函数*/
	for(uint8_t i = 0; i < 4; i++)
	{
		OLED_ShowHexNum(2,3*i+3,ArrayWrite[i],2);  	//（2，3/6/9）打印
		OLED_ShowHexNum(3,3*i+3,ArrayRead[i],2);  	//（3，3/6/9）打印
	}
	
	while(1)
	{
		
	}
	
}
