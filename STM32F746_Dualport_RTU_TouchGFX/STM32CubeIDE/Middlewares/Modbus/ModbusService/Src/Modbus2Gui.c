/**
 * @file Modbus2Gui.c
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


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
    Device_Reg * RegTemp;
    if(Reg->Addr == AC_TEMP_VALUE_ADDR)
    {
        RegVal = Reg->Value;
        xQueueSend(Q_Mb2Gui_AcTempUpdate,&RegVal,0);
    }
   if(Reg->Addr == SLAVE_10_ADDR)
   {
       RegVal = Reg->Value;
       xQueueSend(Q_Mb2Gui_SlaveReg_0,&RegVal,0);
   }
   if(Reg->Addr == SLAVE_11_ADDR)
   {
       RegVal = Reg->Value;
       xQueueSend(Q_Mb2Gui_SlaveReg_1,&RegVal,0);
   }
   if(Reg->Addr == SLAVE_12_ADDR)
   {
       RegVal = Reg->Value;
       xQueueSend(Q_Mb2Gui_SlaveReg_2,&RegVal,0);
   }
   if(Reg->Addr == SLAVE_13_ADDR)
   {
       RegVal = Reg->Value;
       xQueueSend(Q_Mb2Gui_SlaveReg_3,&RegVal,0);
   }
   if(Reg->Addr == SLAVE_14_ADDR)
   {
       RegTemp = Reg;
       RegVal = Reg->Value;
       xQueueSend(Q_Mb2Gui_SlaveReg_4,&Reg,0);
   }
    
}
