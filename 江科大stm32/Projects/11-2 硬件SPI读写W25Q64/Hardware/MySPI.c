#include "stm32f10x.h"                  // Device header

//1.引脚封装
//1.1.片选CS从机封装
void MySPI_W_SS(uint8_t bitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)bitValue);
}


//2.初始化
void MySPI_init(void)
{
	//时钟初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

	//初始化GPIO	
	//初始化主机输出，片选，时钟为PP
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//初始化SCK/MOSI为复用推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//初始化MISO为上拉输入模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//初始化SPI
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1,ENABLE);
	
	MySPI_W_SS(1);
}

//3.1.起始位
void MySPI_Start(void)
{
	MySPI_W_SS(0);
}

//3.2终止位
void MySPI_Stop(void)
{
	MySPI_W_SS(1);
}


uint8_t MySPI_SwapByte(uint8_t ByteSend)
{	
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) != SET);
	SPI_I2S_SendData(SPI1,ByteSend);
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) != SET);
	return SPI_I2S_ReceiveData(SPI1);
}

