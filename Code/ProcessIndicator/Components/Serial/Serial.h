/**
 * @file Serial.h
 * @author Rajeev Kumar
 * @brief
 * @version 0.1
 * @date 2024-01-01
 *
 */
#ifndef SERIAL_H
#define SERIAL_H

/* Includes */
#include <string.h>
#include <Peripherals/Uart.h>

/**
 * @brief 	Initialize Serial(UART1) interface.
 *
 */
void SerialInit(void);

/**
 * @brief 	Send string over UART
 *
 * @param	Pointer to string buffer
 *
 */
void SerialPrint(char *str);

#endif
