/**
 * @file Modbus2Gpio.c
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "main.h"
#include "ModbusIf.h"

/**
 * @brief 
 * 
 * @param Pin 
 * @param State 
 */
void WriteGpio(uint16_t Pin, bool State)
{
    HAL_GPIO_WritePin(GPIO_PORT,Pin,(GPIO_PinState)State);
}

