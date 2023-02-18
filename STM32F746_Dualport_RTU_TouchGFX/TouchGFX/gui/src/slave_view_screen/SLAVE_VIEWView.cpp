#include <gui/slave_view_screen/SLAVE_VIEWView.hpp>
#include "touchgfx/hal/Types.hpp"

extern "C"
{
    #include "Gui2Mb.h"
    #include "Modbus_DeviceCfg.h"
}
static bool Slave_ButtonState[5] = {false};


SLAVE_VIEWView::SLAVE_VIEWView()
{

}

void SLAVE_VIEWView::setupScreen()
{
    SLAVE_VIEWViewBase::setupScreen();
}

void SLAVE_VIEWView::tearDownScreen()
{
    SLAVE_VIEWViewBase::tearDownScreen();
}

void SLAVE_VIEWView::Slave_Button0()
{
    if(Slave_ButtonState[0] == false)
    {
        Slave_ButtonState[0] = true;
        
    }
    else
    {
        Slave_ButtonState[0] = false;
    }
    Device_Update(SLAVE_0_ADDR,Slave_ButtonState[0]);
}
void SLAVE_VIEWView::Slave_Button1()
{
    if(Slave_ButtonState[1] == false)
    {
        Slave_ButtonState[1] = true;
    }
    else
    {
        Slave_ButtonState[1] = false;
    }
    Device_Update(SLAVE_1_ADDR,Slave_ButtonState[1]);
}
void SLAVE_VIEWView::Slave_Button2()
{
    if(Slave_ButtonState[2] == false)
    {
        Slave_ButtonState[2] = true;
    }
    else
    {
        Slave_ButtonState[2] = false;
    }
    Device_Update(SLAVE_2_ADDR,Slave_ButtonState[2]);
}
void SLAVE_VIEWView::Slave_Button3()
{
    if(Slave_ButtonState[3] == false)
    {
        Slave_ButtonState[3] = true;
    }
    else
    {
        Slave_ButtonState[3] = false;
    }
    Device_Update(SLAVE_3_ADDR,Slave_ButtonState[3]);
}
void SLAVE_VIEWView::Slave_Button4()
{
    if(Slave_ButtonState[4] == false)
    {
        Slave_ButtonState[4] = true;
    }
    else
    {
        Slave_ButtonState[4] = false;
    }
    Device_Update(SLAVE_4_ADDR,Slave_ButtonState[4]);
}


