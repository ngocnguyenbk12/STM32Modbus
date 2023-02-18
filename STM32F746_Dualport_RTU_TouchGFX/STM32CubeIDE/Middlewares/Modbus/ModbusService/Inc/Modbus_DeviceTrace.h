/**
 * @file Modbus_DeviceTrace.h
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
#include "ModbusDeviceType.h"
#include "Modbus.h"


bool Read_Coil(uint16_t Addr, modbusHandler_t *modH);
uint16_t Read_Reg(uint16_t Addr, modbusHandler_t *modH);
void Write_Coil(uint16_t Addr, uint16_t Value, modbusHandler_t *modH);
void Write_Reg(uint16_t Addr, uint16_t Value, modbusHandler_t *modH);

void Master_WriteCoil(uint16_t Addr, uint16_t Value, modbusHandler_t *modH);
void Write_Reg(uint16_t Addr, uint16_t Value, modbusHandler_t *modH);
