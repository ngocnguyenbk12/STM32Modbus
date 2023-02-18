#include "main.h"
#include "stdbool.h"

#ifndef MODBUS_DEVICE_
#define MODBUS_DEVICE_


UART_HandleTypeDef huart1;
#define MASTER_MODBUS_PORT  huart1;



#define MODBUS_SLAVE_DEVICE_NUM     10
#define MODBUS_SLAVE_COIL_NUM       10
#define MODBUS_SLAVE_REG_NUM        10

#define MODBUS_MASTER_REG_NUM       10
#define MODBUS_MASTER_COIL_NUM      10


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
