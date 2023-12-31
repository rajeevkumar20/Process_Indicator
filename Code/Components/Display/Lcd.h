/**
 * @file Lcd.c
 * @author Rajeev Kumar
 * @brief
 * @version 0.1
 * @date 2024-01-01
 *
 */
#ifndef LCD_H
#define LCD_H

/* Includes */
#include "stm32f4xx_hal.h"

// LCD data pins
#define D0_Pin 			GPIO_PIN_0
#define D0_GPIO_Port 	GPIOA
#define D1_Pin 			GPIO_PIN_1
#define D1_GPIO_Port 	GPIOA
#define D2_Pin 			GPIO_PIN_2
#define D2_GPIO_Port 	GPIOA
#define D3_Pin 			GPIO_PIN_3
#define D3_GPIO_Port 	GPIOA
#define D4_Pin 			GPIO_PIN_4
#define D4_GPIO_Port 	GPIOA
#define D5_Pin 			GPIO_PIN_5
#define D5_GPIO_Port 	GPIOA
#define D6_Pin 			GPIO_PIN_6
#define D6_GPIO_Port 	GPIOA
#define D7_Pin 			GPIO_PIN_7
#define D7_GPIO_Port 	GPIOA

// LCD Control pins
#define EN_Pin 			GPIO_PIN_0
#define EN_GPIO_Port 	GPIOB
#define RS_Pin 			GPIO_PIN_1
#define RS_GPIO_Port 	GPIOB

#define LINE1			0x80
#define LINE2			0xC0

/**
 * @brief	Initialize 16x2 LCD display and set cursor on 0th position.
 *
 */
void LcdInit(void);

/**
 * @brief	Print string on LCD in given line
 *
 * @param	line	Line1 or Line2
 * @param	str		Pointer to string buffer
 *
 */
void LcdPrint(uint8_t line, char *str);

/**
 * @brief 	Clear screen of LCD display
 *
 */
void LcdClear(void);

#endif
