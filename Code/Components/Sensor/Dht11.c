/**
 * @file Dht11.c
 * @author Rajeev Kumar
 * @brief
 * @version 0.1
 * @date 2024-01-01
 *
 */

/* Includes */
#include <Sensor/Dht11.h>

/* Static function declarations */
static void Dht11Start(void);
static uint8_t Dht11ReadByte(void);

void Dht11Init(void){
	/* GPIOB Port Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();
}

void Dht11ReadTemperature(float *temperature) {
	/* Local variables */
	uint8_t data[5] = { 0 };			/* Data buffer to store data of Dht11 sensor */
	uint8_t timeout = 0;				/* Variable for timeout counter */

	HAL_Delay(150);					/* 150 ms initial delay */

	/* Start Dht11 sensor */
	Dht11Start();

	/* Read input for validation */
	while (READ_SENSOR_INPUT == GPIO_PIN_SET) {
		if (timeout > 254) {
			break;
		}
		HAL_Delay(10);
		timeout++;
	}

	if (READ_SENSOR_INPUT == GPIO_PIN_RESET) {
		HAL_Delay(80);
		if (READ_SENSOR_INPUT == GPIO_PIN_SET) {
			HAL_Delay(80);
			for (int i = 0; i < 5; i++) {
				data[i] = Dht11ReadByte();
			}
			// Check we read 40 bits and that the checksum matches.
			if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xff)) {
				*temperature = (float) data[1] + (float) (data[0] * 0.1);
			}
		}
	}
}

void Dht11ReadHumidity(float *humidity) {
	/* Local variables */
	uint8_t data[5] = { 0 };			/* Data buffer to store data of Dht11 sensor */
	uint8_t timeout = 0;				/* Variable for timeout counter */

	HAL_Delay(150);					/* 150 ms initial delay */

	/* Start Dht11 sensor */
	Dht11Start();

	/* Read input for validation */
	while (READ_SENSOR_INPUT == GPIO_PIN_SET) {
		if (timeout > 254) {
			break;
		}
		HAL_Delay(10);
		timeout++;
	}

	if (READ_SENSOR_INPUT == GPIO_PIN_RESET) {
		HAL_Delay(80);
		if (READ_SENSOR_INPUT == GPIO_PIN_SET) {
			HAL_Delay(80);
			for (int i = 0; i < 5; i++) {
				data[i] = Dht11ReadByte();
			}

			// Check we read 40 bits and that the checksum matches.
			if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xff)) {
				*humidity = (float) data[3] + (float) (data[2] * 0.1);
			}
		}
	}
}

static void Dht11Start(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* Configure Input sensor pin as output */
	GPIO_InitStruct.Pin = IN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* Send start signal to DHT sensor */
	HAL_GPIO_WritePin(GPIOB, IN_Pin, GPIO_PIN_RESET);
	HAL_Delay(18);
	HAL_GPIO_WritePin(GPIOB, IN_Pin, GPIO_PIN_SET);
	HAL_Delay(40);

	/* Configure Input sensor pin as input */
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

static uint8_t Dht11ReadByte(void) {
	/* Local variable */
	uint8_t value = 0;				/* Variable for received byte from Dht11 sensor */

	for (int i = 0; i < 8; i++) {
		while (READ_SENSOR_INPUT == GPIO_PIN_RESET);

		HAL_Delay(30);
		if (READ_SENSOR_INPUT == GPIO_PIN_SET) {
			value |= (1 << (7 - i));
		}

		while (READ_SENSOR_INPUT == GPIO_PIN_SET);
	}

	return value;
}
