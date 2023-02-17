/**
 * @file ModbusSync.h
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Modbus.h"

extern modbusHandler_t Master_Modbus;
extern modbusHandler_t Slave_Modbus;
void Sync_SlaveToMaster_Reg(uint16_t Addr, uint16_t Value);
void Sync_SlaveToMaster_Coil(uint16_t Addr, bool Value);