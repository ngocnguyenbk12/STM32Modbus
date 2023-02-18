#include "Modbus_DeviceTrace.h"
#include "Modbus.h"


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
    for(int i = 0; i < MODBUS_SLAVE_COIL_NUM ; i++)
    {
        if(Addr == modH->Device->Coil[i].Addr)
        {
            modH->Device->Coil[i].Value = Value;
        }
    }
}
void Write_Reg(uint16_t Addr, uint16_t Value, modbusHandler_t *modH)
{
    for(int i = 0; i < MODBUS_SLAVE_REG_NUM ; i++)
    {
        if(Addr == modH->Device->Reg[i].Addr)
        {
            modH->Device->Reg[i].Value = Value;
        }
    } 
}
