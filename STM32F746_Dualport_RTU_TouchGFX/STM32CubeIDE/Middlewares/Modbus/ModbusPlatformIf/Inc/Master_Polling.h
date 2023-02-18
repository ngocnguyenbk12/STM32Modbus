/**
 * @file Master_Polling.h
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
#include "Modbus2Gui.h"
#include "stdbool.h"


#define MASTER_POLLING_TELEGRAM_NUM		2
extern modbus_t Master_Polling_Telegram[MASTER_POLLING_TELEGRAM_NUM];
modbus_t telegram[1]; 
void Master_Polling(void);
void Master_Polling_1ms(void);
void Master_Polling_5ms(void);
void Master_Polling_2ms(void);
void Master_WriteCoilInject(bool Value);
void Master_WriteRegInject(uint16_t Value);
