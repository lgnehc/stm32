#include "stm32f10x.h"                  // Device header
#include "MyI2C.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS 0xD0

//读写操作，参照PPT
//指定寄存器写数据
void MPU6050_WriteReg(uint8_t RegAdress,uint8_t Data)
{
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS); 	//寻址
	MyI2C_ReceiveAck();    				//应答
	MyI2C_SendByte(RegAdress); 			//指定寄存器
	MyI2C_ReceiveAck();    				//应答
	MyI2C_SendByte(Data); 				//写入数据
	MyI2C_ReceiveAck();    				//应答
	MyI2C_Stop();
}

//指定寄存器读数据
uint8_t MPU6050_ReadReg(uint8_t RegAdress)
{
	uint8_t Data;
	
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS); 	//寻址
	MyI2C_ReceiveAck();    				//应答
	MyI2C_SendByte(RegAdress); 			//指定寄存器
	MyI2C_ReceiveAck();
	
	//需要重新起始
	MyI2C_Start();
	MyI2C_SendByte(MPU6050_ADDRESS | 0x01);  //转化成0xD1,最后一位转为读
	MyI2C_ReceiveAck();
	Data = MyI2C_ReceiveByte();
	//这里只接受一个Bite,接收多个MyI2C_SendAck(0)
	MyI2C_SendAck(1);           
	MyI2C_Stop();
	
	return Data;
}


void MPU6050_init(void)
{
	MyI2C_init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1	,0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2	,0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV	,0x09);
	MPU6050_WriteReg(MPU6050_CONFIG	,0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);	
}


//获取设备ID号
uint8_t MPU6050_GetID(void)
{
	return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}


//获取陀螺仪和加速器的内部数据
//这里传参使用结构体更合适
void MPU6050_GetData(uint16_t* AccX,uint16_t* AccY,uint16_t* AccZ,
					uint16_t* GyroX,uint16_t* GyroY,uint16_t* GyroZ)
{
	uint16_t DataH ,DataL ;
	//改进：可以使用读取多个字节的函数依次读取这些数据，因为这些寄存器在规格书上是连续的
	//获取加速器X轴的数据
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
	*AccX = (DataH << 8 ) | DataL;          //需要合并成16bit

	DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
	*AccY = (DataH << 8 ) | DataL;          //需要合并成16bit
	
	DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
	*AccZ = (DataH << 8 ) | DataL;          //需要合并成16bit
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
	*GyroX = (DataH << 8 ) | DataL;          //需要合并成16bit
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
	*GyroY = (DataH << 8 ) | DataL;          //需要合并成16bit
	
	DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
	DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
	*GyroZ = (DataH << 8 ) | DataL;          //需要合并成16bit
}


