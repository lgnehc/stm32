#include "stm32f10x.h"                  // Device header
#include "Delay.h"

//函数封装，方便移植时修改端口和延时
//SCL写
void MyI2C_W_SCL(uint8_t Bitvalue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)Bitvalue);
	Delay_us(10);
}

//SDA写
void MyI2C_W_SDA(uint8_t Bitvalue)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)Bitvalue);
	Delay_us(10);
}

//SDA读
uint8_t MyI2C_R_SDA(void)
{
	uint8_t Bitvalue;
	Bitvalue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
	Delay_us(10);
	return Bitvalue;
}



//初始化函数
void MyI2C_init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
}

void MyI2C_Start(void)
{
	//这里为了兼容重复起始条件，应该SDA先置1
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);    
	MyI2C_W_SCL(0);
}

void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte)
{
	/*
	MyI2C_W_SDA(Byte && 0x80 );  //0x80 = 1000 0000  只设置第8位的意思
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	
	MyI2C_W_SDA(Byte && 0x40 );  //0x40 = 0100 0000  只设置第7位的意思
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	
	往下依次设置其他位
	*/
	//
	for(uint8_t i = 0;i < 8; i++)
	{
		MyI2C_W_SDA( Byte & (0x80 >> i));
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}

uint8_t MyI2C_ReceiveByte(void)
{

	uint8_t Byte = 0x00;
	
	//把控制权交给从机，这里抓叫控制权就是把主机把SDA置1，此时从机发送0/1就把SDA置0/1
	MyI2C_W_SDA(1);
	for(uint8_t i = 0; i < 8; i++)
	{
		MyI2C_W_SCL(1);   			   		//高位读取数据
		if(MyI2C_R_SDA() == 1)        
		{
			Byte = (Byte | (0x80 >> i));    //从高位依次读出每位数据
		}
		MyI2C_W_SCL(0);      				//SCL置0，低位放置数据
	}
	//如果接收的是0，那么返回 Byte = 0x00
	return Byte;
}


//发送应答，这时对应的情形是从机发送数据，主机接收到数据给出应答回应给从机
void MyI2C_SendAck(uint8_t AckBit)
{
	//发送应答，此时控制权是在从机
	//这里函数进来时是SCL低电平
	MyI2C_W_SDA(AckBit);  
	MyI2C_W_SCL(1);     //读取应答
	MyI2C_W_SCL(0);     //进入下一个时序
}

//接受应答，这时对应的情形是主机发送数据，从机接收到数据给出应答回应给主机
uint8_t  MyI2C_ReceiveAck(void)
{
	//接受应答，此时控制权是在主机
	//这里函数进来时是SCL低电平
	uint8_t AckBit;
	MyI2C_W_SDA(1);   //主机释放SDA控制权，同时从机发送应答位
	MyI2C_W_SCL(1);   //高电平读应答位	   		
	AckBit = MyI2C_R_SDA();        
	MyI2C_W_SCL(0);    //进入下个时序  				
	return AckBit;
}
