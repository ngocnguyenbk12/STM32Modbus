/**
 * @file Modbus_Func.c
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Modbus.h"
#include "Modbus_Func.h"



void ModbusQuery(modbusHandler_t * modH, modbus_t * telegram )
{
	//Add the telegram to the TX tail Queue of Modbus
	if (modH->uModbusType == MB_MASTER)
	{
	telegram->u32CurrentTask = (uint32_t *) osThreadGetId();
	xQueueSendToBack(modH->QueueTelegramHandle, telegram, 0);
	}
	else{
		while(1);// error a slave cannot send queries as a master
	}
}



void ModbusQueryInject(modbusHandler_t * modH, modbus_t * telegram )
{
	//Add the telegram to the TX head Queue of Modbus
	xQueueReset(modH->QueueTelegramHandle);
	telegram->u32CurrentTask = (uint32_t *) osThreadGetId();
	xQueueSendToFront(modH->QueueTelegramHandle, telegram, 0);
}

