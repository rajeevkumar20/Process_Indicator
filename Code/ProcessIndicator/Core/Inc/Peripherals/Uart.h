/**
 * @file Uart.h
 * @author Rajeev Kumar
 * @brief
 * @version 0.1
 * @date 2024-01-01
 *
 */

#ifndef __USART_H__
#define __USART_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

#define TX_Pin		GPIO_PIN_9
#define RX_Pin		GPIO_PIN_10

HAL_StatusTypeDef UartInit(UART_HandleTypeDef *huart);

#endif /* __USART_H__ */

