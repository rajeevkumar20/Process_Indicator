/**
 * @file Serial.c
 * @author Rajeev Kumar
 * @brief
 * @version 0.1
 * @date 2024-01-01
 *
 */

/* Includes */
#include <Serial/Serial.h>

/* Handle for UART peripheral */
UART_HandleTypeDef UartHandle;

/* Global temperature and humidity variables */
extern char Temperature[16];		/* Data buffer for temperature reading in string format */
extern char Humidity[16];			/* Data buffer for humidity reading in string format */

/* This function handles USART1 global interrupt */
void USART1_IRQHandler(void)
{
	if (((USART1->SR & USART_SR_RXNE) != RESET) && ((USART1->CR1 & USART_CR1_RXNEIE) != RESET)) {
		uint8_t receivedByte = USART1->DR;

		/* If received byte is ? */
		if(receivedByte == '?') {
			SerialPrint(Temperature);		/* Send temperature string */
			SerialPrint("\r\n");			/* Send CR LF */
			SerialPrint(Humidity);			/* Send humidity string */
			SerialPrint("\r\n");			/* Send CR LF */
		}
	}
  HAL_UART_IRQHandler(&UartHandle);
}

/* Initialize Serial Interface */
void SerialInit(void) {
	/* Initialize UART interface */
	UartInit(&UartHandle);
}

/* Print data on Serial interface */
void SerialPrint(char *str) {
	HAL_UART_Transmit(&UartHandle, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}
