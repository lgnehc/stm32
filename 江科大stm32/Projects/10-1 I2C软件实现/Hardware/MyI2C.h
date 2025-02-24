#ifndef __MYI2C_H
#define __MYI2C_H

void MyI2C_W_SCL(uint8_t Bitvalue);
void MyI2C_W_SDA(uint8_t Bitvalue);
uint8_t MyI2C_R_SDA(void);
void MyI2C_init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_ReceiveByte(void);
void MyI2C_SendAck(uint8_t AckBit);
uint8_t  MyI2C_ReceiveAck(void);

#endif
