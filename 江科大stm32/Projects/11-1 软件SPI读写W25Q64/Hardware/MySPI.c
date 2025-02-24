#include "stm32f10x.h"                  // Device header

//1.引脚封装
//1.1.片选CS从机封装
void MySPI_W_SS(uint8_t bitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_4,(BitAction)bitValue);
}

//1.2.时钟SCL封装
void MySPI_W_SCK(uint8_t bitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_5,(BitAction)bitValue);
}

//1.3.MOSI(对应W25Q64的DI)封装
void MySPI_W_MOSI(uint8_t bitValue)
{
	GPIO_WriteBit(GPIOA,GPIO_Pin_7,(BitAction)bitValue);
}

//1.4.MOSI(对应W25Q64的DI)封装
uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6);
}

//2.初始化
void MySPI_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//初始化主机输出，片选，时钟为PP
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//初始化主机的输入为上拉模式
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	MySPI_W_SS(1);   //初始化之后是低电平，默认是需要低电平
	MySPI_W_SCK(0);  //使用模式0  ？？？
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


//3.3交换字节1:功能是给一个需要的数据ByteSend，返回ByteReceive值
//以模式0的主机写入数据模型来理解,对照讲义课程移位实现
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{	
	for(uint8_t i = 0; i < 8; i++)
	{
		MySPI_W_MOSI(ByteSend & 0x80 );   //取出最高位
		ByteSend = (ByteSend << 1);       //左移一位，最低位自动补0 
		MySPI_W_SCK(1);
		if(MySPI_R_MISO() == 1) {ByteSend = (ByteSend | 0x01);}  //低位依次移入数据 
		MySPI_W_SCK(0);
	}
	return ByteSend;   //这个是和MySPI_R_MISO()交换后的ByteSend
}

//3.3交换字节2:功能是给一个需要的数据ByteSend，返回ByteReceive值
//以模式0的主机写入数据模型来理解,这个实现方式不是对照讲义课程的
uint8_t MySPI_SwapByte1(uint8_t ByteSend)
{
	uint8_t ByteReceive = 0X00 ;
	
	for(uint8_t i = 0; i < 8; i++)
	{
		MySPI_W_MOSI(ByteSend & (0x80 >> i) );
		MySPI_W_SCK(1);
		if(MySPI_R_MISO() == 1) {ByteReceive |= (0x80 >> i);} 
		MySPI_W_SCK(0);
	}
	return ByteReceive;
}
