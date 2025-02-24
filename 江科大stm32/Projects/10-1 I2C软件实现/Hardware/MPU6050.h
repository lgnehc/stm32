#ifndef __MPU6050_H
#define __MPU6050_H

void MPU6050_WriteReg(uint8_t RegAdress,uint8_t Data);
uint8_t MPU6050_ReadReg(uint8_t RegAdress);
void MPU6050_init(void);
uint8_t MPU6050_GetID(void);
void MPU6050_GetData(uint16_t* AccX,uint16_t* AccY,uint16_t* AccZ,
					uint16_t* GyroX,uint16_t* GyroY,uint16_t* GyroZ);

#endif
