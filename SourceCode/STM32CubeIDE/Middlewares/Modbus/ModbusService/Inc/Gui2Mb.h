/**
 * @file Gui2Mb.h
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "Modbus.h"
#include "main.h"
#include "ModbusDeviceType.h"
#include "Modbus_DeviceCfg.h"

void Device_Update(uint16_t Addr, bool state);
void Device_Slave_Update(uint16_t Addr, bool state);
void Device_Slave_UpdateReg(uint16_t Addr, uint16_t value);

