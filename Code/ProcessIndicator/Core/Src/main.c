/**
 * @file main.c
 * @author Rajeev Kumar
 * @brief
 * @version 0.1
 * @date 2024-01-01
 *
 */

/* Includes */
#include <main.h>
#include <Display/Lcd.h>
#include <Sensor/Dht11.h>
#include <Storage/Flash.h>
#include <Serial/Serial.h>

/* Union for bytes conversion */
typedef union {
	float F32;
	unsigned char Buffer[4];
} BytesConverter;

/* Global variables */
char Temperature[16] = {0};				/* Data buffer for temperature reading in string format */
char Humidity[16] = {0};				/* Data buffer for humidity reading in string format */

void SaveToFlash(float temperature, float humidity) {
	/* local variables */
	unsigned int startAddress; 					/* Variable for startAddress */
	BytesConverter converter; 					/* Variable for bytes conversion */
	HAL_StatusTypeDef ret = HAL_OK; 			/* Variable for return  */

	/* Get start address, where to write new data */
	startAddress = FlashGetStartAddress();

	/* startAddress should be greater than 4096 */
	if(startAddress < 4096) {
		startAddress = 4096;
	}

	/* Erase sector if start address is multiple of sector size (4096) */
	if (startAddress % 4096 == 0) {
		ret = FlashSectorErase(startAddress);
		if (ret != HAL_OK) {
			return;
		}
	}

	/* Write temperature data in flash */
	converter.F32 = temperature;
	ret = FlashWriteData(startAddress, converter.Buffer, 4);
	if (ret != HAL_OK) {
		return;
	}
	/* Increase start address by 4 */
	startAddress = startAddress + 4;

	/* Write humidity data in flash */
	converter.F32 = humidity;
	ret = FlashWriteData(startAddress, converter.Buffer, 4);
	if (ret != HAL_OK) {
		return;
	}

	/* Increase start address by 4 */
	startAddress = startAddress + 4;

	/* Update start address */
	FlashSetStartAddress(startAddress);
}

/* The application entry point */
int main(void) {
	/* MCU Configuration */
	HAL_Init();
	SystemClock_Config();

	/* Initialize LCD display */
	LcdInit();

	/* Initialize DHT11 temperature and humidity sensor */
	Dht11Init();

	/* Initialize Serial Interface */
	SerialInit();

	/* Initialize NOR Flash storage */
	FlashInit();

	/* Clear LCD display */
	LcdClear();

	while (1) {
		/* Local variables */
		float temp = 0;				/* Variable for temperature reading */
		float humd = 0;				/* Variable for humidity reading */

		/* Read temperature and humidity */
		Dht11ReadTemperature(&temp);
		Dht11ReadHumidity(&humd);

		/* Save temperature and humidity to flash */
		SaveToFlash(temp, humd);

		/* Prepare strings to print data on LCD display */
		sprintf(Temperature, "TEMP     : %0.2f", temp);
		sprintf(Humidity, "HUMIDITY : %0.2f", humd);

		/* Print temperature and humidity data on LCD */
		LcdPrint(LINE1, Temperature);
		LcdPrint(LINE2, Humidity);
	}
}

/* System Clock Configuration */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/* Configure the main internal regulator output voltage */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	/* Initializes the RCC Oscillators */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 84;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/* Initializes the CPU, AHB and APB buses clocks */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
		Error_Handler();
	}
}

/* This function is executed in case of error occurrence */
void Error_Handler(void) {
	__disable_irq();
	while (1) {
	}
}
