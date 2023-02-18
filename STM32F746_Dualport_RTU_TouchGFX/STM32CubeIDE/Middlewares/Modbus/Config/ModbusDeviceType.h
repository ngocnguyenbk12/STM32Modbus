/**
 * @file ModbusDeviceType.h
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2023-02-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "main.h"
#include "stdbool.h"

#ifndef MODBUS_DEVICE_
#define MODBUS_DEVICE_


extern UART_HandleTypeDef huart1;
#define SLAVE_MODBUS_PORT  huart1;

extern UART_HandleTypeDef huart6;
#define MASTER_MODBUS_PORT  huart6;

#define MODBUS_SLAVE_DEVICE_NUM     20
#define MODBUS_SLAVE_COIL_NUM       20
#define MODBUS_SLAVE_REG_NUM        20

#define MODBUS_MASTER_REG_NUM       20
#define MODBUS_MASTER_COIL_NUM      20


typedef struct 
{
    uint16_t Addr;
    uint16_t Value;
}Device_Reg;

typedef struct 
{
    uint16_t Addr;
    bool    Value;
}Device_Coil;

typedef struct 
{
    Device_Reg Reg[MODBUS_SLAVE_REG_NUM];
    Device_Coil Coil[MODBUS_SLAVE_COIL_NUM];
}ModbusSlave_Device;

typedef struct 
{
    Device_Reg Reg[MODBUS_MASTER_REG_NUM];
    Device_Coil Coil[MODBUS_MASTER_COIL_NUM];
}ModbusMaster_Device;



#endif
