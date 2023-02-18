/**
 * @file ModbusSync.c
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ModbusSync.h"

void Sync_Init(void)
{

}

void Sync_SlaveToMaster_Reg(uint16_t Addr, uint16_t Value)
{
    for(int i = 0; i< MODBUS_SLAVE_REG_NUM; i++)
    {
        if(Addr == Slave_Modbus.Device->Reg[i].Addr)
        {
            Slave_Modbus.Device->Reg[i].Value = Value;
        }
    }
}

void Sync_SlaveToMaster_Coil(uint16_t Addr, bool Value)
{
    for(int i = 0; i< MODBUS_SLAVE_COIL_NUM; i++)
    {
        if(Addr == Slave_Modbus.Device->Coil[i].Addr)
        {
            Slave_Modbus.Device->Coil[i].Value = Value;
        }
    } 
}
