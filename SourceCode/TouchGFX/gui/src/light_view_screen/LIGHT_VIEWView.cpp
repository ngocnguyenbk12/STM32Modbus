#include <gui/light_view_screen/LIGHT_VIEWView.hpp>
extern "C"
{
    #include "Modbus.h"
	// #include "Modbus_GPIO.h"
    #include "stm32f7xx_hal_gpio.h"
    #include "touchgfx/hal/Types.hpp"
    #include "Gui2Mb.h"
#include "ModbusIf.h"
   // #include "Modbus_Cfg.h"
    //extern DeviceCoil_Type Coil_Data[MODBUS_SLAVE_COIL_MAX];
}

static bool Light_0_State = false;
static bool Light_1_State = false;
static bool Light_2_State = false;
static bool Light_3_State = false;
static bool Light_4_State = false;

LIGHT_VIEWView::LIGHT_VIEWView()
{

}

void LIGHT_VIEWView::setupScreen()
{
    LIGHT_VIEWViewBase::setupScreen();
}

void LIGHT_VIEWView::tearDownScreen()
{
    LIGHT_VIEWViewBase::tearDownScreen();
}

void LIGHT_VIEWView::Light_Updater(uint16_t pin)
{

}

void LIGHT_VIEWView::LIGHT_Updater(uint16_t pin)
{

}

void LIGHT_VIEWView::Light_Button0()
{
   if(Light_0_State == false)
   {
       WriteGpio(GPIO_0_PIN,GPIO_PIN_RESET);
       Light_0_State = true;
       Device_Slave_Update(GPIO_0_ADDR,Light_0_State);
   }
   else if(Light_0_State == true)
   {
       WriteGpio(GPIO_0_PIN,GPIO_PIN_SET);
       Light_0_State = false;
       Device_Slave_Update(GPIO_0_ADDR,Light_0_State);
   }
}


void LIGHT_VIEWView::Light_Button1()
{
   if(Light_1_State == false)
   {
       WriteGpio(GPIO_1_PIN,GPIO_PIN_RESET);
       Light_1_State = true;
       Device_Slave_Update(GPIO_1_ADDR,Light_1_State);
   }
   else if(Light_1_State == true)
   {
       WriteGpio(GPIO_1_PIN,GPIO_PIN_SET);
       Light_1_State = false;
       Device_Slave_Update(GPIO_1_ADDR,Light_1_State);
   }
}

void LIGHT_VIEWView::Light_Button2()
{
   if(Light_2_State == false)
   {
       WriteGpio(GPIO_2_PIN,GPIO_PIN_RESET);
       Light_2_State = true;
       Device_Slave_Update(GPIO_2_ADDR,Light_2_State);
   }
   else if(Light_2_State == true)
   {
       WriteGpio(GPIO_2_PIN,GPIO_PIN_SET);
       Light_2_State = false;
       Device_Slave_Update(GPIO_2_ADDR,Light_2_State);
   }
}


void LIGHT_VIEWView::Light_Button3()
{
   if(Light_3_State == false)
   {
       WriteGpio(GPIO_3_PIN,GPIO_PIN_RESET);
       Light_3_State = true;
       Device_Slave_Update(GPIO_3_ADDR,Light_3_State);
   }
   else if(Light_3_State == true)
   {
       WriteGpio(GPIO_3_PIN,GPIO_PIN_SET);
       Light_3_State = false;
       Device_Slave_Update(GPIO_3_ADDR,Light_3_State);
   }
}

void LIGHT_VIEWView::Light_Button4()
{
   if(Light_4_State == false)
   {
       WriteGpio(GPIO_4_PIN,GPIO_PIN_RESET);
       Light_4_State = true;
       Device_Slave_Update(GPIO_4_ADDR,Light_4_State);
   }
   else if(Light_4_State == true)
   {
       WriteGpio(GPIO_4_PIN,GPIO_PIN_SET);
       Light_4_State = false;
       Device_Slave_Update(GPIO_4_ADDR,Light_4_State);
   }
}

void LIGHT_VIEWView::LIGHT_Update_0(bool State)
{
    LIGHT0_BUTTON.forceState(State);
    LIGHT0_BUTTON.invalidate();
}
void LIGHT_VIEWView::LIGHT_Update_1(bool State)
{
    LIGHT1_BUTTON.forceState(State);
    LIGHT1_BUTTON.invalidate();
}
void LIGHT_VIEWView::LIGHT_Update_2(bool State)
{
    LIGHT2_BUTTON.forceState(State);
    LIGHT2_BUTTON.invalidate();
}
void LIGHT_VIEWView::LIGHT_Update_3(bool State)
{
    LIGHT3_BUTTON.forceState(State);
    LIGHT3_BUTTON.invalidate();  
}
void LIGHT_VIEWView::LIGHT_Update_4(bool State)
{
    LIGHT4_BUTTON.forceState(State);
    LIGHT4_BUTTON.invalidate();
}

