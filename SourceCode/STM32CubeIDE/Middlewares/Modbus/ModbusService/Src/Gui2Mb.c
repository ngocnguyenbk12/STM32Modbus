/**
 * @file Gui2Mb.c
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Gui2Mb.h"
#include "Master_Polling.h"

void Device_Update(uint16_t Addr, bool state)
{
    for(int i = 0; i < MODBUS_MASTER_REG_NUM ; i++)
    {
        if(Addr == Master_Modbus.MasterDevice->Coil[i].Addr)
        {
            Master_Modbus.MasterDevice->Coil[i].Value = state;
        }
    }
}


void Device_Slave_Update(uint16_t Addr, bool state)
{
    for(int i = 0 ; i< MODBUS_SLAVE_COIL_NUM; i++)
    {
        if(Addr == Slave_Modbus.Device->Coil[i].Addr)
        {
            Slave_Modbus.Device->Coil[i].Value = state;
        }
        if(Addr == AC_ONOFF_STATE_ADDR)
        {
            Master_WriteCoilInject(state);
        }
    }
}

void Device_Slave_UpdateReg(uint16_t Addr, uint16_t value)
{
    for(int i = 0; i < MODBUS_SLAVE_REG_NUM; i++)
    {
        if(Addr == Slave_Modbus.Device->Reg[i].Addr)
        {
            Slave_Modbus.Device->Reg[i].Value = value;
        }
        if( Addr == AC_TEMP_VALUE_ADDR)
        {
            Master_WriteRegInject(value);
        }
    }
}