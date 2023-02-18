/**
 * @file UARTCallback.c
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "task.h"
#include "main.h"
#include "Modbus.h"
#include "Modbus_Func.h"
#include "stm32f7xx_hal.h"
#include "RingBuffer.h"



extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart6;

/**
 * @brief
 * This is the callback for HAL interrupts of UART TX used by Modbus library.
 * This callback is shared among all UARTS, if more interrupts are used
 * user should implement the correct control flow and verification to maintain
 * Modbus functionality.
 * @ingroup UartHandle UART HAL handler
 */

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	/* Modbus RTU TX callback BEGIN */
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	int i;
	for (i = 0; i < numberHandlers; i++ )
	{
	   	if (MastermHandler[i]->port == huart  )
	   	{
	   		// notify the end of TX
	   		xTaskNotifyFromISR(MastermHandler[i]->myTaskModbusAHandle, 0, eNoAction, &xHigherPriorityTaskWoken);
	   		break;
	   	}

	}
	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

	/* Modbus RTU TX callback END */

	/*
	 * Here you should implement the callback code for other UARTs not used by Modbus
	 *
	 * */

}



/**
 * @brief
 * This is the callback for HAL interrupt of UART RX
 * This callback is shared among all UARTS, if more interrupts are used
 * user should implement the correct control flow and verification to maintain
 * Modbus functionality.
 * @ingroup UartHandle UART HAL handler
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{


	if(UartHandle == &huart6)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	/* Modbus RTU RX callback BEGIN */
		int i;
		for (i = 0; i < Master_numberHandlers; i++ )
		{
			if(MastermHandler[i]->xTypeHW == USART_HW)
			{
				RingAdd(&MastermHandler[i]->xBufferRX, MastermHandler[i]->dataRX);
				HAL_UART_Receive_IT(MastermHandler[i]->port, &MastermHandler[i]->dataRX, 1);
				xTimerResetFromISR(MastermHandler[i]->xTimerT35, &xHigherPriorityTaskWoken);
			}
			break;
		}
    	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}
	else if(UartHandle == &huart1)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		int i;
		for (i = 0; i < numberHandlers; i++ )
		{
			if(mHandlers[i]->xTypeHW == USART_HW)
			{
				RingAdd(&mHandlers[i]->xBufferRX, mHandlers[i]->dataRX);
				HAL_UART_Receive_IT(mHandlers[i]->port, &mHandlers[i]->dataRX, 1);
				xTimerResetFromISR(mHandlers[i]->xTimerT35, &xHigherPriorityTaskWoken);
			}
			break;
		}
		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}
	/* Modbus RTU RX callback END */

	/*
	 * Here you should implement the callback code for other UARTs not used by Modbus
	 *
	 *
	 * */

}
