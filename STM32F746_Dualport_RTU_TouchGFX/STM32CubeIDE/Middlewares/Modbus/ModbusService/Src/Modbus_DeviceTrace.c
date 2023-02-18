/**
 * @file Modbus_DeviceTrace.c
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "Modbus_DeviceTrace.h"
#include "Modbus.h"
#include "Modbus2Gui.h"
#include "ModbusSync.h"

bool Read_Coil(uint16_t Addr, modbusHandler_t *modH)
{
    for(int i = 0; i < MODBUS_SLAVE_COIL_NUM ; i++)
    {
        if(Addr == modH->Device->Coil[i].Addr)
        {
            return modH->Device->Coil[i].Value;
        }
    }
}

uint16_t Read_Reg(uint16_t Addr, modbusHandler_t *modH)
{
    for(int i = 0; i < MODBUS_SLAVE_REG_NUM ; i++)
    {
        if(Addr == modH->Device->Reg[i].Addr)
        {
            return modH->Device->Reg[i].Value;
        }
    } 
}

void Write_Coil(uint16_t Addr, uint16_t Value, modbusHandler_t *modH)
{
    Device_Coil Coil;
    for(int i = 0; i < MODBUS_SLAVE_COIL_NUM ; i++)
    {
        if(Addr == modH->Device->Coil[i].Addr)
        {
            Coil.Addr = Addr;
            Coil.Value = Value;
            modH->Device->Coil[i].Value = Value;
            Queue_CoilUpdate(&Coil);
        }
    }
}
void Write_Reg(uint16_t Addr, uint16_t Value, modbusHandler_t *modH)
{
    Device_Reg  Reg;
    for(int i = 0; i < MODBUS_SLAVE_REG_NUM ; i++)
    {
        if(Addr == modH->Device->Reg[i].Addr)
        {
            Reg.Addr = Addr;
            Reg.Value = Value;
            modH->Device->Reg[i].Value = Value;
            Queue_RegUpdate(&Reg);
        }
    } 
}


void Master_WriteCoil(uint16_t Addr, uint16_t Value, modbusHandler_t *modH)
{
    Device_Coil Coil;
    for(int i = 0; i < MODBUS_MASTER_COIL_NUM ; i++)
    {
        if(Addr == modH->MasterDevice->Coil[i].Addr)
        {
            Coil.Addr = Addr;
            Coil.Value = Value;
            modH->MasterDevice->Coil[i].Value = Value;
            Sync_SlaveToMaster_Coil(Addr,Value);
            Queue_CoilUpdate(&Coil);
        }
    }
}
void Master_WriteReg(uint16_t Addr, uint16_t Value, modbusHandler_t *modH)
{
    Device_Reg  Reg;
    for(int i = 0; i < MODBUS_MASTER_COIL_NUM ; i++)
    {
        if(Addr == modH->MasterDevice->Reg[i].Addr)
        {
            Reg.Addr = Addr;
            Reg.Value = Value;
            modH->MasterDevice->Reg[i].Value = Value;
            Sync_SlaveToMaster_Reg(Addr,Value);
            Queue_RegUpdate(&Reg);
        }
    } 
}
