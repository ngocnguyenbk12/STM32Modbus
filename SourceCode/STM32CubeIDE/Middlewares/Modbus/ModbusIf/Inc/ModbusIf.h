/**
 * @file ModbusIf.h
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "main.h"
#include "stdbool.h"
#include "StdType.h"
#include "ModbusConfig.h"



/**
 * @brief Communication port Setup 
 * Please change uart type follow your project
 */
extern UART_HandleTypeDef huart1;
#define SLAVE_MODBUS_PORT  huart1;

extern UART_HandleTypeDef huart6;
#define MASTER_MODBUS_PORT  huart6;


/**
 * @brief GPIO port Setup
 * 
 */

#define GPIO_0_PIN             GPIO_PIN_10
#define GPIO_1_PIN             GPIO_PIN_9
#define GPIO_2_PIN             GPIO_PIN_8
#define GPIO_3_PIN             GPIO_PIN_7
#define GPIO_4_PIN             GPIO_PIN_6
#define GPIO_PORT              GPIOF


void ModbusIF_WriteGPIO(uint16_t Pin, bool State); 
Std_ReturnType ModbusIF_Init(UART_HandleTypeDef * port, uint8_t * Buffer);
void ModbusIf_Transmit(UART_HandleTypeDef * port, uint8_t * Buffer, uint16_t size);
Std_ReturnType ModbusIf_Serial(UART_HandleTypeDef * port, uint8_t * Buffer);
void WriteGpio(uint16_t Pin, bool State);

