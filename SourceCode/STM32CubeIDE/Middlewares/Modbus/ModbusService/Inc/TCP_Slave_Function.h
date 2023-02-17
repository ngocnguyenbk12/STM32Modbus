/**
 * @file TCP_Slave_Function.h
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ModbusDeviceType.h"
#include "main.h"
#include "Modbus.h"

int8_t Slave_Fc1(modbusHandler_t *modH);
int8_t Slave_Fc3(modbusHandler_t *modH);
int8_t Slave_Fc6(modbusHandler_t *modH );
int8_t Slave_Fc16(modbusHandler_t *modH);
int8_t Slave_Fc5( modbusHandler_t *modH );
int8_t Slave_Fc15( modbusHandler_t *modH );