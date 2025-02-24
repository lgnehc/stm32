#include "stm32f10x.h"                  // Device header
#include "myflash.h"

#define STORE_START_ADDRESS 0X800FC00
#define STORE_COUNT 512

uint16_t Store_Data[STORE_COUNT];

//初始化这里是把全部置0，最后一页的页首半字节写0xA5A5作为标志位
void Store_Init(void)
{
	if(MyFlash_ReadHalfWord(STORE_START_ADDRESS) != 0xA5A5)
	{
		//擦除
		MyFlash_ErasePage(STORE_START_ADDRESS);
		MyFlash_ProgramHalfWord(STORE_START_ADDRESS , 0xA5A5);
		for(uint16_t i = 1; i < STORE_COUNT; i++)
		{
			MyFlash_ProgramWord(STORE_START_ADDRESS + i*2,0x0000);
		}
	}
	for(uint16_t i = 0; i < STORE_COUNT; i++)
	{
		Store_Data[i] = MyFlash_ReadHalfWord(STORE_START_ADDRESS + i*2);
	}
	
}


void Store_Save(void)
{
	MyFlash_ErasePage(STORE_START_ADDRESS);
	for(uint16_t i = 0; i < STORE_COUNT; i++)
	{
		MyFlash_ProgramHalfWord(STORE_START_ADDRESS + i*2 , Store_Data[i]);
	}
}

void Store_Clear(void)
{
	for(uint16_t i = 1; i < STORE_COUNT; i++)
	{
		MyFlash_ProgramWord(STORE_START_ADDRESS + i*2,0x0000);
	}
	Store_Save();	
		
}
