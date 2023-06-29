
#define	__EXT_EEPROM_
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************
��������ʼ����
*************************************************************/
void Memory_Init(void)
{

}

/************************************************************
������д���ݣ�
*************************************************************/
void Memory_Write(uint16_t sector_addr, uint8_t *pdataIn, uint8_t len)
{
	uint8_t i;
	
	FLASH_UnLock();
		
	FLASH_Erase(FLASH_DATA, sector_addr);
	
	for(i = 0; i < len; i++)
	{
		FLASH_Write(FLASH_DATA, sector_addr + i, *(pdataIn + i));
	}
	
	FLASH_Lock();	
}

/************************************************************
�����������ݣ�
*************************************************************/
void Memory_Read(uint16_t sector_addr, uint8_t *pdataOut, uint8_t len)
{
	uint8_t i;
	
	FLASH_UnLock();	
	
	for(i = 0; i < len; i++)
	{
		pdataOut[i] = FLASH_Read(FLASH_DATA, sector_addr + i);
	}
	
	FLASH_Lock();	
}
