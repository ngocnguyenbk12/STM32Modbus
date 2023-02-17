/**
 * @file Master_Polling.c
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "Master_Polling.h"
#include "semphr.h"

modbus_t Master_Polling_Telegram[MASTER_POLLING_TELEGRAM_NUM];
void Master_Polling(void)
{
    if(xSemaphoreTake((QueueHandle_t)Master_Modbus.ModBusSphrHandle , 300)==pdTRUE)
	{
		
		Master_Polling_Telegram[0].u8id = 3; // slave address
		Master_Polling_Telegram[0].u8fct = MB_FC_READ_COILS; // function code (this one is registers write)
		Master_Polling_Telegram[0].u16RegAdd = 5000;
		Master_Polling_Telegram[0].u16CoilsNo = 1; // number of elements (coils or registers) to read
		Master_Polling_Telegram[0].u16reg = Master_ModbusData; // pointer to a memory array
		ModbusQuery(&Master_Modbus, &Master_Polling_Telegram[0]);
		xSemaphoreGive((QueueHandle_t)&Master_Modbus.ModBusSphrHandle);
    }
	if(xSemaphoreTake((QueueHandle_t)Master_Modbus.ModBusSphrHandle , 300)==pdTRUE)
	{
		
		Master_Polling_Telegram[1].u8id = 3; // slave address
		Master_Polling_Telegram[1].u8fct = MB_FC_READ_REGISTERS; // function code (this one is registers write)
		Master_Polling_Telegram[1].u16RegAdd = 30011;
		Master_Polling_Telegram[1].u16CoilsNo = 1; // number of elements (coils or registers) to read
		Master_Polling_Telegram[1].u16reg = Master_ModbusData; // pointer to a memory array
		ModbusQuery(&Master_Modbus, &Master_Polling_Telegram[1]);
		xSemaphoreGive((QueueHandle_t)Master_Modbus.ModBusSphrHandle);
    }
}

void Master_Polling_1ms(void)
{
    if(xSemaphoreTake((QueueHandle_t)Master_Modbus.ModBusSphrHandle , 300)==pdTRUE)
	{
		
		Master_Polling_Telegram[0].u8id = 3; // slave address
		Master_Polling_Telegram[0].u8fct = MB_FC_READ_REGISTERS; // function code (this one is registers write)
		Master_Polling_Telegram[0].u16RegAdd = 30010;
		Master_Polling_Telegram[0].u16CoilsNo = 2; // number of elements (coils or registers) to read
		Master_Polling_Telegram[0].u16reg = Master_ModbusData; // pointer to a memory array
		ModbusQuery(&Master_Modbus, &Master_Polling_Telegram[0]);
		xSemaphoreGive((QueueHandle_t)Master_Modbus.ModBusSphrHandle);
    }


}

void Master_Polling_2ms(void)
{
	if(xSemaphoreTake((QueueHandle_t)Master_Modbus.ModBusSphrHandle , 300)==pdTRUE)
	{
		
		Master_Polling_Telegram[1].u8id = 4; // slave address
		Master_Polling_Telegram[1].u8fct = MB_FC_READ_REGISTERS; // function code (this one is registers write)
		Master_Polling_Telegram[1].u16RegAdd = 30011;
		Master_Polling_Telegram[1].u16CoilsNo = 1; // number of elements (coils or registers) to read
		Master_Polling_Telegram[1].u16reg = Master_ModbusData; // pointer to a memory array
		ModbusQuery(&Master_Modbus, &Master_Polling_Telegram[1]);
		xSemaphoreGive((QueueHandle_t)Master_Modbus.ModBusSphrHandle);
    }
}
void Master_Polling_5ms(void)
{
    if(xSemaphoreTake((QueueHandle_t)Master_Modbus.ModBusSphrHandle , 300)==pdTRUE)
	{
		
		Master_Polling_Telegram[0].u8id = 3; // slave address
		Master_Polling_Telegram[0].u8fct = MB_FC_READ_COILS; // function code (this one is registers write)
		Master_Polling_Telegram[0].u16RegAdd = 0020;
		Master_Polling_Telegram[0].u16CoilsNo = 5; // number of elements (coils or registers) to read
		Master_Polling_Telegram[0].u16reg = (uint16_t*)Master_ModbusData; // pointer to a memory array
		ModbusQuery(&Master_Modbus, &Master_Polling_Telegram[0]);
		xSemaphoreGive((QueueHandle_t)Master_Modbus.ModBusSphrHandle);
    }
}


void Master_WriteCoilInject(bool Value)
{
    if(xSemaphoreTake((QueueHandle_t)Master_Modbus.ModBusSphrHandle , 300)==pdTRUE)
	{
		Master_Polling_Telegram[0].u8id = 4; // slave address
		Master_Polling_Telegram[0].u8fct = MB_FC_WRITE_COIL; // function code (this one is registers write)
		Master_Polling_Telegram[0].u16RegAdd = AC_ONOFF_STATE_ADDR;
		Master_Polling_Telegram[0].u16CoilsNo = 1;
		Master_Polling_Telegram[0].u16reg = (uint16_t*)Value;
		ModbusQuery(&Master_Modbus, &Master_Polling_Telegram[0]);
		xSemaphoreGive((QueueHandle_t)Master_Modbus.ModBusSphrHandle);
    }
}

void Master_WriteRegInject(uint16_t Value)
{
    if(xSemaphoreTake((QueueHandle_t)Master_Modbus.ModBusSphrHandle , 300)==pdTRUE)
	{
		Master_Polling_Telegram[0].u8id = 4; // slave address
		Master_Polling_Telegram[0].u8fct = MB_FC_WRITE_REGISTER; // function code (this one is registers write)
		Master_Polling_Telegram[0].u16RegAdd = AC_TEMP_VALUE_ADDR;
		Master_Polling_Telegram[0].u16CoilsNo = 1;
		Master_Polling_Telegram[0].u16reg = (uint16_t*)Value;
		ModbusQuery(&Master_Modbus, &Master_Polling_Telegram[0]);
		xSemaphoreGive((QueueHandle_t)Master_Modbus.ModBusSphrHandle);
    }
}
