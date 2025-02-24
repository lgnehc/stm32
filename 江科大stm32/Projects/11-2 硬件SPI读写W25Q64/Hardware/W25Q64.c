#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_ins.h"

//W25Q64的分配：先分block--分扇区--分页，见视频解释

void W25Q64_init(void)
{
	MySPI_init();
}

//1.读取设备ID（24位），这个需要根据手册写
//MID存放16-23位，DID存放0-16位
void W25Q64_ReadID(uint8_t* MID,uint16_t* DID)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_JEDEC_ID);  //规格书的读ID的指令
	*MID = MySPI_SwapByte(0xFF);  //随便给个数据交换出16-23位
	*DID = MySPI_SwapByte(0xFF);  //随便给个数据交换出8-16位
	*DID = (*DID << 8);
	*DID = (*DID | MySPI_SwapByte(0xFF));  //随便给个数据交换出0-8位
	MySPI_Stop();
}

//写指令
void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

//判断是否busy状态
void W25Q64_WaitBusy(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);  		  //发送读取状态寄存器1指令，所以不需要返回值
	
	uint32_t Timeout = 10000;
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01)== 0x01)  //交换出状态寄存器的数值并判断最后一位是否是1
	{
		Timeout--;
		if(Timeout == 0)  { break; }
	}
	MySPI_Stop();
}	


//页编程函数,参照规格书的时序图，先发送24bit地址，然后是数据
void W64Q25_PageProgram(uint32_t Adress, uint8_t* DataArray, uint16_t count)
{
	//寄存器要求，写入需要先开使能端
	W25Q64_WriteEnable();                
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	//依次发送地址Adress,先发送高位(规格书描述的)  假设0x00123456
	MySPI_SwapByte(Adress >> 16 );   //发送0x00000012 ,但是MySPI_SwapByte只接受最后8bit
	MySPI_SwapByte(Adress >> 8);     //发送0x00001234,是MySPI_SwapByte只接受最后8bit:0x34
	MySPI_SwapByte(Adress);
	
	//写入数据
	for(uint16_t i = 0; i < count; i++)
	{
		MySPI_SwapByte(DataArray[i]);
	}
	MySPI_Stop();
	//事后等待，等写入完成后再退出
	//NOTE：可以事前等待，效率更高，但是读数据是需要判断是否busy
	W25Q64_WaitBusy();
}


//扇区擦除程序
void W25Q64_SectorErase(uint32_t Adress)
{
	//寄存器要求，写入需要先开使能端
	W25Q64_WriteEnable();						
	
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);  //擦除指令
	MySPI_SwapByte(Adress >> 16 );   
	MySPI_SwapByte(Adress >> 8);     
	MySPI_SwapByte(Adress);
	MySPI_Stop();
	
	//事后等待，等写入完成后再退出
	W25Q64_WaitBusy();
}


//读数据函数:这个数组是读取的数据存放的地方
void W25Q64_ReadData(uint32_t Adress, uint8_t* DataArray, uint32_t count)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	MySPI_SwapByte(Adress >> 16 );   
	MySPI_SwapByte(Adress >> 8);     
	MySPI_SwapByte(Adress);
	
	//读出数据
	for(uint32_t i = 0; i < count; i++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();
}
