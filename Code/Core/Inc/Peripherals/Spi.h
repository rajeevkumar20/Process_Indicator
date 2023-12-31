/**
 * @file Spi.h
 * @author Rajeev Kumar
 * @brief
 * @version 0.1
 * @date 2024-01-01
 *
 */

#ifndef __SPI_H__
#define __SPI_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

// SPI pins
#define CS_Pin 			GPIO_PIN_12
#define CS_Port 		GPIOB
#define SCLK_Pin 		GPIO_PIN_13
#define SCLK_Port 		GPIOB
#define MISO_Pin 		GPIO_PIN_14
#define MISO_Port 		GPIOB
#define MOSI_Pin 		GPIO_PIN_15
#define MOSI_Port 		GPIOB

HAL_StatusTypeDef SpiInit(SPI_HandleTypeDef *hspi);

#endif /* __SPI_H__ */
