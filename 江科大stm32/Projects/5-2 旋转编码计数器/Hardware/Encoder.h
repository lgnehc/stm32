#ifndef __Encoder_H
#define __Encoder_H

void Encoder_Init(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
int16_t Encoder_Get_Cnt(void);

#endif
