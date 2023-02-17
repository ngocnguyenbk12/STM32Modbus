/**
 * @file ModbusIf_Gpio.c
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ModbusIf.h"
#include "main.h"


/**
 * @brief 
 * 
 * @param Pin 
 * @param State 
 */
void ModbusIF_WriteGPIO(uint16_t Pin, bool State)
{
    HAL_GPIO_WritePin(GPIO_PORT,Pin,(GPIO_PinState)State);
}

/**
 * @brief 
 * 
 * @param Pin 
 * @return GPIO_PinState 
 */
GPIO_PinState ModbusIf_ReadGPIo(uint16_t Pin)
{
    return HAL_GPIO_ReadPin(GPIO_PORT, Pin);
}
