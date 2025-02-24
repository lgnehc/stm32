#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
//#include "MyI2C.h"
#include "MPU6050.h"


int main(void){
	OLED_Init();
	MPU6050_init();
	/*
	//测试I2C的6个单元函数
	MyI2C_Start();
	MyI2C_SendByte(0xD0);
	uint8_t Ack = MyI2C_ReceiveAck();
	MyI2C_Stop();
	OLED_ShowNum(1,1,Ack,3);
	*/
	
	/*测试函数
	//MyI2C_Start();   //一开始显示FF，加这个重新刷新就可以正常显示
	//MPU6050规格书默认规定0X75是只读的，内容是0x68
	uint8_t ID = MPU6050_ReadReg(0x75);
	OLED_ShowHexNum(1,1,ID,2);
	*/
	/*
	MPU6050_WriteReg(0x6B,0X00);  //解除睡眠模式
	MPU6050_WriteReg(0x19,0x66);  //修改数据
	uint8_t ID = MPU6050_ReadReg(0x19);
	OLED_ShowHexNum(1,1,ID,2);
	*/
	
	uint8_t ID;
	uint16_t AX,AY,AZ,GX,GY,GZ;
	ID = MPU6050_GetID();
	OLED_ShowString(1,1,"ID:");
	OLED_ShowHexNum(1,6,ID,2);
	
	while(1)
	{
		MPU6050_GetData(&AX,&AY,&AZ,&GX,&GY,&GZ);
		OLED_ShowSignedNum(2,1,AX,5);
		OLED_ShowSignedNum(3,1,AY,5);
		OLED_ShowSignedNum(4,1,AZ,5);
		OLED_ShowSignedNum(2,8,GX,5);
		OLED_ShowSignedNum(3,8,GY,5);
		OLED_ShowSignedNum(4,8,GZ,5);	
	}
	
}
