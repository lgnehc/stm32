#ifndef __W25Q64_H
#define __W25Q64_H

void W25Q64_init(void);
void W25Q64_ReadID(uint8_t* MID,uint16_t* DID);
void W25Q64_WriteEnable(void);
void W25Q64_WaitBusy(void);
void W64Q25_PageProgram(uint32_t Adress, uint8_t* DataArray, uint16_t count);
void W25Q64_SectorErase(uint32_t Adress);
void W25Q64_ReadData(uint32_t Adress, uint8_t* DataArray, uint32_t count);



#endif
