/**
 * @file Modbus2Gui.h
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "main.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "ModbusConfig.h"
#include "Modbus.h"

/**             Modbus Memory Address               **/
/**
 * 30001            Air Conditioner
 * 00001->00008     Digital Input Output
 * TBD
*/


/**                             Type def                        **/



xQueueHandle Q_Mb2Gui_AcOnOff;
xQueueHandle Q_Mb2Gui_AcTempUpdate;

xQueueHandle Q_Mb2Gui_Gpio0;
xQueueHandle Q_Mb2Gui_Gpio1;
xQueueHandle Q_Mb2Gui_Gpio2;
xQueueHandle Q_Mb2Gui_Gpio3;
xQueueHandle Q_Mb2Gui_Gpio4;


xQueueHandle Q_Mb2Gui_SlaveRead_0;
xQueueHandle Q_Mb2Gui_SlaveRead_1;
xQueueHandle Q_Mb2Gui_SlaveRead_2;
xQueueHandle Q_Mb2Gui_SlaveRead_3;
xQueueHandle Q_Mb2Gui_SlaveRead_4;

xQueueHandle Q_Mb2Gui_SlaveReg_0;
xQueueHandle Q_Mb2Gui_SlaveReg_1;
xQueueHandle Q_Mb2Gui_SlaveReg_2;
xQueueHandle Q_Mb2Gui_SlaveReg_3;
xQueueHandle Q_Mb2Gui_SlaveReg_4;
xQueueHandle Q_Mb2Gui_SlaveReg_10;
xQueueHandle Q_Mb2Gui_SlaveReg_11;

void Queue_CoilUpdate(Device_Coil *Coil);
void Queue_RegUpdate(Device_Reg *Reg);


