/**
 * @file Modbus_Func.h
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Modbus.h"


void setTimeOut( uint16_t u16timeOut); //!<write communication watch-dog timer
uint16_t getTimeOut(); //!<get communication watch-dog timer value
bool getTimeOutState(); //!<get communication watch-dog timer state
void ModbusQuery(modbusHandler_t * modH, modbus_t * telegram ); // put a query in the queue tail
void ModbusQueryInject(modbusHandler_t * modH, modbus_t * telegram); //put a query in the queue head








