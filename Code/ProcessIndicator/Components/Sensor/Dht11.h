/**
 * @file Dht11.h
 * @author Rajeev Kumar
 * @brief
 * @version 0.1
 * @date 2024-01-01
 *
 */

#ifndef SRC_SENSOR_DHT11_H_
#define SRC_SENSOR_DHT11_H_

/* Includes */
#include "stm32f4xx_hal.h"

/* Macro used for INPUT pin */
#define IN_Pin 							GPIO_PIN_10

/* Macro used for a function to read INPUT pin */
#define READ_SENSOR_INPUT				HAL_GPIO_ReadPin(GPIOB, IN_Pin)

/**
 * @brief	Initialize Dht11 temperature and humidity sensor.
 *
 */
void Dht11Init(void);

/**
 * @brief	Read temperature from Dht11 sensor.
 *
 * @param	temperature		Pointer to temperature variable
 *
 */
void Dht11ReadTemperature(float *temperature);

/**
 * @brief	Read humidity from Dht11 sensor.
 *
 * @param	humidity		Pointer to humidity variable
 *
 */
void Dht11ReadHumidity(float *humidity);

#endif
