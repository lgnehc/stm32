#include "stm32f10x.h"                  // Device header


uint16_t My_Size;

void MyDMA_Init(uint32_t ADDrA,uint32_t ADDrB,uint8_t Size)
{
	My_Size = Size;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_InitTypeDef DMA_InitStruct;
		
	DMA_InitStruct.DMA_PeripheralBaseAddr = ADDrA;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable; //地址自增
	DMA_InitStruct.DMA_MemoryBaseAddr = ADDrB;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;  //DMA_DIR是指DMA_PeripheralBaseAddr作为源or目的
	DMA_InitStruct.DMA_M2M = DMA_M2M_Enable;         //是否软件触发，寄存器到寄存器一般软件触发
	DMA_InitStruct.DMA_BufferSize = Size;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;
	
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	DMA_Cmd(DMA1_Channel1,DISABLE);
}

void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1,My_Size);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);
	
	
}


