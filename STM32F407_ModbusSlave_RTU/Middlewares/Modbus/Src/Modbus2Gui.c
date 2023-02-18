#include "Modbus2Gui.h"

void Queue_CoilUpdate(Device_Coil *Coil)
{
    bool    CoilVal;
    if(Coil->Addr == AC_ONOFF_STATE_ADDR)
    {
        CoilVal = Coil->Value;
        xQueueSend(Q_Mb2Gui_AcOnOff,&CoilVal,0);
    }



/**     Update for GPIO       */
    if(Coil->Addr == GPIO_0_ADDR)
    {
        CoilVal = Coil->Value;
        xQueueSend(Q_Mb2Gui_Gpio0,&CoilVal,0);
        WriteGpio(GPIO_0_PIN,Coil->Value);
    }
    if(Coil->Addr == GPIO_1_ADDR)
    {
        CoilVal = Coil->Value;
        xQueueSend(Q_Mb2Gui_Gpio1,&CoilVal,0);
        WriteGpio(GPIO_1_PIN,Coil->Value);
    }
    if(Coil->Addr == GPIO_2_ADDR)
    {
        CoilVal = Coil->Value;
        xQueueSend(Q_Mb2Gui_Gpio2,&CoilVal,0);
        WriteGpio(GPIO_2_PIN,Coil->Value);
    }
    if(Coil->Addr == GPIO_3_ADDR)
    {
        CoilVal = Coil->Value;
        xQueueSend(Q_Mb2Gui_Gpio3,&CoilVal,0);
        WriteGpio(GPIO_3_PIN,Coil->Value);
    }
    if(Coil->Addr == GPIO_4_ADDR)
    {
        CoilVal = Coil->Value;
        xQueueSend(Q_Mb2Gui_Gpio4,&CoilVal,0);
        WriteGpio(GPIO_4_PIN,Coil->Value);
    }


}


void Queue_RegUpdate(Device_Reg *Reg)
{
    uint16_t RegVal;
    if(Reg->Addr == AC_TEMP_VALUE_ADDR)
    {
        RegVal = Reg->Value;
        xQueueSend(Q_Mb2Gui_AcTempUpdate,&RegVal,0);
    }
}
