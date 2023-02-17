/**
 * @file ModbusIf_Uart.c
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
 * @param port 
 * @param Buffer 
 * @return Std_ReturnType 
 */
Std_ReturnType ModbusIf_Serial(UART_HandleTypeDef * port, uint8_t * Buffer)
{
    Std_ReturnType RetVal = E_NOT_OK;
    if(HAL_UART_Receive_IT(port, Buffer,1) != HAL_OK)
    {
        return RetVal;
    }
    RetVal = E_OK;
    return RetVal;
}

/**
 * @brief 
 * 
 * @param port 
 * @param Buffer 
 * @param size 
 */
void ModbusIf_Transmit(UART_HandleTypeDef * port, uint8_t * Buffer, uint16_t size)
{
    HAL_UART_Transmit(port,Buffer,size, HAL_MAX_DELAY);
}

