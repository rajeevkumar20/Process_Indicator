/**
 * @file Lcd.c
 * @author Rajeev Kumar
 * @brief
 * @version 0.1
 * @date 2024-01-01
 *
 */

/* Includes */
#include <Display/Lcd.h>

/* Static functions declarations */
static void LcdSendCommand(uint8_t cmd);
static void LcdSendData(uint8_t data);

void LcdInit(void) {
	/* Local variable */
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOA, D0_Pin | D1_Pin | D2_Pin | D3_Pin | D4_Pin | D5_Pin | D6_Pin | D7_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, EN_Pin | RS_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : PAPin PAPin PAPin PAPin
	 PAPin PAPin PAPin PAPin */
	GPIO_InitStruct.Pin = D0_Pin | D1_Pin | D2_Pin | D3_Pin | D4_Pin | D5_Pin | D6_Pin | D7_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/*Configure GPIO pins : PBPin PBPin PBPin PBPin */
	GPIO_InitStruct.Pin = EN_Pin | RS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* 8 bit mode */
	LcdSendCommand(0x38);
	HAL_Delay(10);

	/* Clear Screen */
	LcdSendCommand(0x0F);
	HAL_Delay(10);

	/* Display On, Cursor on */
	LcdSendCommand(0x01);
	HAL_Delay(10);

	/* Increment cursor */
	LcdSendCommand(0x06);
	HAL_Delay(10);
}

void LcdPrint(uint8_t line, char *str) {
	/* Cursor line */
	LcdSendCommand(line);
	HAL_Delay(10);				/* 10 ms delay */

	/* Write string to LCD */
	while(*str) {
		LcdSendData(*str);
		str++;
	}
}

void LcdClear(void) {
	/* Clear Screen */
	LcdSendCommand(0x0F);
	HAL_Delay(10);				/* 10 ms delay */
}

static void LcdSendCommand(uint8_t cmd) {
	/* Write command to port */
	GPIOA->ODR = cmd;

	/* Register Select Pin
	 * RS = 0 : Command Mode
	 * RS = 1 : Data Mode
	 */
	HAL_GPIO_WritePin(GPIOB, RS_Pin, GPIO_PIN_RESET);

	/* High to low pulse need to enable the LCD */
	HAL_GPIO_WritePin(GPIOB, EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, EN_Pin, GPIO_PIN_RESET);
}

static void LcdSendData(uint8_t data) {
	/* Write data to port */
	GPIOA->ODR = data;

	/* Register Select Pin
	 * RS = 0 : Command Mode
	 * RS = 1 : Data Mode
	 */
	HAL_GPIO_WritePin(GPIOB, RS_Pin, GPIO_PIN_SET);

	/* High to low pulse need to enable the LCD */
	HAL_GPIO_WritePin(GPIOB, EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, EN_Pin, GPIO_PIN_RESET);
}
