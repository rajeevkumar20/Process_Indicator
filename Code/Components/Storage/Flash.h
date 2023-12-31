/**
 * @file Flash.h
 * @author Rajeev Kumar
 * @brief
 * @version 0.1
 * @date 2024-01-01
 *
 */
#ifndef FLASH_H
#define FLASH_H

/* Includes */
#include "Peripherals/Spi.h"
#include "stdbool.h"

/*
 * W25Q64
 * 1 Page	: 256 bytes
 * 1 Sector : 4096 bytes
 */

/* W25Q64 Commands */
#define FLASH_WRITE_CMD				0x02		/* Page Program */
#define FLASH_READ_CMD				0x03		/* Page Read */
#define FLASH_READ_STATUS_CMD		0x05		/* Read Status */
#define FLASH_WRITE_DISABLE_CMD		0X04		/* Write Disable */
#define FLASH_WRITE_ENABLE_CMD		0X06		/* Write Enable */
#define FLASH_ERASE_SECTOR_CMD		0x20		/* Sector Erase */
#define FLASH_ERASE_CHIP_CMD		0xC7		/* Chip Erase */

/**
 * brief 	Initialize NOR flash storage and spi interface.
 *
 */
void FlashInit(void);

/**
 * @brief	Get start address from 1st sector of the flash,
 * where new data will be written.
 *
 * @return 	Start address
 *
 */
unsigned int FlashGetStartAddress(void);

/**
 * @brief	Set start address in 1st sector of the flash
 *
 * @return 	None
 *
 */
void FlashSetStartAddress(unsigned int startAddress);

/**
 * @brief	Read data from flash storage with given address location.
 *
 * @param	address		Memory location from where data read will start
 * @param	data		Pointer to data buffer
 * @param	length		Number of bytes to be read
 *
 * @return	HAL status
 *
 */
HAL_StatusTypeDef FlashReadData(uint32_t address, void *data, uint16_t length);

/**
 * @brief	Write data to flash storage at given address location.
 *
 * @param	address		Memory location from where data write will start
 * @param	data		Pointer to data buffer
 * @param	length		Number of bytes to be written
 *
 * @return	HAL status
 *
 */
HAL_StatusTypeDef FlashWriteData(uint32_t address, void *data, uint16_t length);

/**
 * @brief	Erase Sector of flash storage with given address location
 *
 * @param	address 	Memory location of sector
 *
 * @return	HAL status
 *
 */
HAL_StatusTypeDef FlashSectorErase(uint32_t address);

/**
 * @brief	Erase full flash storage
 *
 * @return	HAL status
 *
 */
HAL_StatusTypeDef FlashChipErase(void);

#endif
