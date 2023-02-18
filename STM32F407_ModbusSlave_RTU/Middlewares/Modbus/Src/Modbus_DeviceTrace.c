#include "Modbus_DeviceTrace.h"
#include "Modbus.h"
#include "Modbus2Gui.h"


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
