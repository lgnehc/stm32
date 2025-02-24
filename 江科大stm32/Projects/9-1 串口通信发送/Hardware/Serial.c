#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>


//初始化函数
void  Serial_Init(void){
	//1.1配置时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//1.2.GPIO引脚初始化，
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//1.2.USART引脚初始化--这里只是发送模式
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_InitStructure.USART_Parity =  USART_Parity_No;     //奇偶校验是否开启
 	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
}


//1.按位发送数据,这里Byte是16进制数据，例如0x41
void Serial_SendByte(uint8_t Byte){
	USART_SendData(USART1,Byte);
	//确认数据已经转移完成，转移完成后标志位清0，如果没有转移完成那么已知循环等待
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	
}

//底下都是对这个Serial_SendByte函数的封装

//2.发送数组函数
void Serial_SendArray(uint8_t Array[],uint16_t Length){
	for(uint16_t i = 0; i< Length;i++){
		Serial_SendByte(Array[i]);
	}
}

//3.发送字符串
void Serial_SendString(char* String){
	for(uint16_t i = 0; String[i] != '\0'; i++){
		Serial_SendByte(String[i]);
	}
}


//4.1计算x^y :可以用来计算10的次方 ，给4.2函数使用的
uint32_t Serial_Pow(uint32_t x,uint32_t y){
	uint32_t result = 1;
	while(y--){
		result = result * x;
	}
	return result;
}


//4.2发送数字,从高位到地位依次发送
void Serial_SendNumber(uint32_t Number,uint16_t Length){
	for (uint8_t i = 0; i < Length; i++){
		//Number/Serial_Pow(10,Length-i-1)是依次从高位取出位数；+'0'是需要转换成对应的ascii码
		Serial_SendByte(Number/Serial_Pow(10,Length-i-1)%10 + '0');
	}
		
}

//移植printf函数，需要先打开USB Microlib,printf函数默认输出到屏幕，所以需要先重定向到电脑屏幕
//5.1 移植函数1：printf函数输出重定向到屏幕
int fputc(int ch, FILE *f){
	Serial_SendByte(ch);
	return ch;
}

//5.2

//5.3 移植打印函数3
void Serial_Printf(char* format,...){
	char String[100];
	va_list arg;
	va_start(arg,format);
	vsprintf(String,format,arg);
	va_end(arg);
	Serial_SendString(String);
}

