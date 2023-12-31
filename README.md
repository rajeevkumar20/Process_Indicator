# Process Indicator

* Process Indicator is the device which collects and process sensor data.
* This device stores that data to the NOR flash memory and shows it on 16x2 LCD display.
* It has ability to take user input over UART serial protocol.
* On user input command it sends temperature and humidity data over UART.

## Components
* Display   -  16x2 LCD
* Sensor    -  DHT11 temperature and humidity sensor
* Serial    -  UART serial interface
* Storage   -  W25Q64 NOR flash memory
