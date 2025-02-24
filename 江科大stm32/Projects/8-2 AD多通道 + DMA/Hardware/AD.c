#include "stm32f10x.h"                  // Device header

uint16_t AD_Value[4];

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 4;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	//ADC_InitStructure.ADC_ContinuousConvMode =  DISABLE;   
	ADC_InitStructure.ADC_ContinuousConvMode =  ENABLE;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC1,&ADC_InitStructure);
	
	DMA_InitTypeDef DMA_InitStruct;	
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //地址自增
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)AD_Value;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;  //DMA_DIR是指DMA_PeripheralBaseAddr作为源or目的
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;        
	DMA_InitStruct.DMA_BufferSize = 4;
	//DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;        //用于单次扫描单次转运
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	ADC_Cmd(ADC1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);              //单次扫描单次触发不需要此行

}

/* //单次扫描单次转运
void AD_GetValue(void)
{
	DMA_Cmd(DMA1_Channel1,DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1,4);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	
		while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
	DMA_ClearFlag(DMA1_FLAG_TC1);

}
*/

