/**
 * @file Flash.c
 * @author Rajeev Kumar
 * @brief
 * @version 0.1
 * @date 2024-01-01
 *
 */

/* Includes */
#include "Storage/Flash.h"

/* Static function declarations */
static HAL_StatusTypeDef FlashWriteEnable(void);
static HAL_StatusTypeDef FlashWriteDisable(void);

/* Handle for SPI interface */
SPI_HandleTypeDef SpiHandle;

/* Union for bytes conversion */
typedef union {
	unsigned int U32;
	unsigned char Buffer[4];
} BytesConverter;

void FlashInit(void) {
	/* Initialize SPI interface */
	SpiInit(&SpiHandle);
}

unsigned int FlashGetStartAddress(void) {
	/* Local variables */
	BytesConverter converter;		/* Variable for bytes converson */

	/* Read start Address from 0th memory location */
	FlashReadData(0, converter.Buffer, 4);

	/* return start address in unsigned integer format */
	return converter.U32;
}

void FlashSetStartAddress(unsigned int startAddress) {
	/* Local Variables */
	BytesConverter converter;		/* Variable for bytes converson */
	converter.U32 = startAddress;

	/* Write startAddress at 0th memory location */
	FlashWriteData(0, converter.Buffer, 4);
}

HAL_StatusTypeDef FlashReadData(uint32_t address, void *data, uint16_t length) {
	/* Local Variables */
	uint8_t writedata[4] = {0};						/* Data buffer for command and address */
	HAL_StatusTypeDef ret = HAL_OK;					/* Variable for return output */

	/* Load command and 24 bit address to SPI data packet */
	writedata[0] = FLASH_READ_CMD;
	writedata[1] = address>>16;
	writedata[2] = address>>8;
	writedata[3] = address;

	/* CS pin Low */
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_RESET);

	/* Send read command to flash memory */
	ret = HAL_SPI_Transmit(&SpiHandle, writedata, 4, HAL_MAX_DELAY);
	if(ret != HAL_OK) {
		return ret;
	}

	/* Read data from flash memory */
	ret = HAL_SPI_Receive(&SpiHandle, data, length, HAL_MAX_DELAY);
	if(ret != HAL_OK) {
		return ret;
	}

	/* CS pin High */
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_SET);

	return ret;
}

HAL_StatusTypeDef FlashWriteData(uint32_t address, void *data, uint16_t length) {
	/* Local Variables */
	uint8_t writedata[4] = {0};						/* Data buffer for command and address */
	HAL_StatusTypeDef ret = HAL_OK;					/* Variable for return output */

	/* Load command and 24 bit address to SPI data packet */
	writedata[0] = FLASH_WRITE_CMD;
	writedata[1] = address >> 16;
	writedata[2] = address >> 8;
	writedata[3] = address;

	/* Write Enable */
	ret = FlashWriteEnable();
	if (ret != HAL_OK) {
		return ret;
	}

	/* CS pin Low */
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_RESET);

	/* Send Program page command to flash memory */
	ret = HAL_SPI_Transmit(&SpiHandle, writedata, 4, HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		return ret;
	}

	/* Write data to flash memory */
	ret = HAL_SPI_Receive(&SpiHandle, data, length, HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		return ret;
	}

	/* CS pin High */
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_SET);

	/* Write Disable */
	ret = FlashWriteDisable();
	if (ret != HAL_OK) {
		return ret;
	}

	return ret;
}

HAL_StatusTypeDef FlashSectorErase(uint32_t address) {
	/* Local Variables */
	uint8_t writedata[4] = {0};						/* Data buffer for command and address */
	HAL_StatusTypeDef ret = HAL_OK;					/* Variable for return output */

	/* Load command and address to SPI data packet */
	writedata[0] = FLASH_ERASE_SECTOR_CMD;
	writedata[1] = address>>16;
	writedata[2] = address>>8;
	writedata[3] = address;

	/* Write Enable */
	ret = FlashWriteEnable();
	if(ret != HAL_OK) {
		return ret;
	}

	/* CS pin Low */
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_RESET);

	/* Send erase address command to Flash */
	ret = HAL_SPI_Transmit(&SpiHandle, writedata, 4, HAL_MAX_DELAY);
	if(ret != HAL_OK) {
		return ret;
	}

	/* CS pin High */
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_SET);

	/* Write Disable */
	ret = FlashWriteDisable();
	if(ret != HAL_OK) {
		return ret;
	}

	return ret;
}

HAL_StatusTypeDef FlashChipErase(void) {
	/* Local Variables */
	uint8_t cmd = FLASH_ERASE_CHIP_CMD;				/* Variable for command */
	HAL_StatusTypeDef ret = HAL_OK;					/* Variable for return output */

	/* Write Enable */
	ret = FlashWriteEnable();
	if(ret != HAL_OK) {
		return ret;
	}

	/* CS pin Low */
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_RESET);

	/* Send erase chip command to Flash */
	ret = HAL_SPI_Transmit(&SpiHandle, &cmd, 1, HAL_MAX_DELAY);
	if(ret != HAL_OK) {
		return ret;
	}

	/* CS pin High */
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_SET);

	/* Write Disable */
	ret = FlashWriteDisable();
	if(ret != HAL_OK) {
		return ret;
	}

	return ret;
}

static HAL_StatusTypeDef FlashWriteEnable(void) {
	/* Local Variables */
	uint8_t cmd = FLASH_WRITE_ENABLE_CMD;			/* Variable for command */
	HAL_StatusTypeDef ret = HAL_OK;					/* Variable for return output */

	// CS Low
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_RESET);

	// Send write enable command to Flash
	ret = HAL_SPI_Transmit(&SpiHandle, &cmd, 1, HAL_MAX_DELAY);
	if(ret != HAL_OK) {
		return ret;
	}

	// CS High
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_SET);

	return ret;
}

static HAL_StatusTypeDef FlashWriteDisable(void) {
	/* Local Variables */
	uint8_t cmd = FLASH_WRITE_DISABLE_CMD;			/* Variable for command */
	HAL_StatusTypeDef ret = HAL_OK;					/* Variable for return output */

	// CS Low
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_RESET);

	// Send write disable command to Flash
	ret = HAL_SPI_Transmit(&SpiHandle, &cmd, 1, HAL_MAX_DELAY);
	if(ret != HAL_OK) {
		return ret;
	}

	// CS High
	HAL_GPIO_WritePin(GPIOB, CS_Pin, GPIO_PIN_SET);

	return ret;
}
