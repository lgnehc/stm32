#ifndef __Serial_H
#define __Serial_H

#include <stdio.h>

extern uint8_t Serial_TxPacket[];
extern uint8_t Serial_RxPacket[];

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t Array[],uint16_t Length);
void Serial_SendString(char* String);
void Serial_SendNumber(uint32_t Number,uint16_t Length);
void Serial_Printf(char* format,...);
uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);
void Serial_SendPacket(void);
//void Serial_SendPacket(uint8_t Serial_TxPacket[],uint8_t lenght);

#endif
