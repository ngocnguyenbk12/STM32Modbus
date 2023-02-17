#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "touchgfx/hal/Types.hpp"


extern "C"
{
	/* Include 	*/
	#include "FreeRTOS.h"
	#include "queue.h"
	#include "task.h"
	#include "main.h"
	#include "Modbus.h"
	#include "semphr.h"
	#include "cmsis_os.h"
	#include "stm32f7xx_hal.h"
	#include "Modbus2Gui.h"

	/* Local Variable */
	uint8_t counter = 0;
	uint16_t reg ;
	uint16_t pin;
	uint16_t Reg_0;
	uint16_t Reg_1;
	uint16_t Reg_2;
	/* Extern Variable */
	extern RTC_HandleTypeDef hrtc;
	extern RTC_TimeTypeDef RTC_Time;
	extern RTC_DateTypeDef RTC_Date;

	extern xQueueHandle Q_Mb2Gui_AcOnOff;
	extern xQueueHandle Q_Mb2Gui_AcTempUpdate;
	extern xQueueHandle Q_Mb2Gui_Gpio0;
	extern xQueueHandle Q_Mb2Gui_Gpio1;
	extern xQueueHandle Q_Mb2Gui_Gpio2;
	extern xQueueHandle Q_Mb2Gui_Gpio3;
	extern xQueueHandle Q_Mb2Gui_Gpio4;

	extern xQueueHandle Q_Mb2Gui_SlaveReg_0;
	extern xQueueHandle Q_Mb2Gui_SlaveReg_1;
	extern xQueueHandle Q_Mb2Gui_SlaveReg_2;
	extern xQueueHandle Q_Mb2Gui_SlaveReg_3;
	extern xQueueHandle Q_Mb2Gui_SlaveReg_4;
	

	Device_Reg Slave_Reg_Value;
}
extern "C" void ModbusQueryInject(modbusHandler_t * modH, modbus_t telegram);
unsigned short Value ;

unsigned short Slave_Reg_value;
bool Ac_onoff_Q;
unsigned short Ac_Value;
bool Gpio_TempState;






Model::Model() : modelListener(0)
{
//    Q_Modbus2AC = xQueueGenericCreate(1,1,0);
//	Q_Modbus2Light = xQueueGenericCreate(1,1,0);
	Q_Mb2Gui_AcOnOff= xQueueGenericCreate(1,1,0);
	Q_Mb2Gui_AcTempUpdate = xQueueGenericCreate(1,1,0);
	Q_Mb2Gui_Gpio0	= xQueueGenericCreate(1,1,0);
	Q_Mb2Gui_Gpio1	= xQueueGenericCreate(1,1,0);
	Q_Mb2Gui_Gpio2	= xQueueGenericCreate(1,1,0);
	Q_Mb2Gui_Gpio3	= xQueueGenericCreate(1,1,0);
	Q_Mb2Gui_Gpio4	= xQueueGenericCreate(1,1,0);
	
	Q_Mb2Gui_SlaveReg_0 = xQueueGenericCreate(1,1,0);
	Q_Mb2Gui_SlaveReg_1	= xQueueGenericCreate(1,1,0);
	Q_Mb2Gui_SlaveReg_2	= xQueueGenericCreate(1,sizeof(uint16_t),0);
	Q_Mb2Gui_SlaveReg_3	= xQueueGenericCreate(1,1,0);
	Q_Mb2Gui_SlaveReg_4	= xQueueGenericCreate(1,1,0);


}

void Model::tick()
{

	HAL_RTC_GetTime(&hrtc, &RTC_Time, RTC_FORMAT_BCD);
	HAL_RTC_GetDate(&hrtc, &RTC_Date, RTC_FORMAT_BCD);
	modelListener->RTC_UpdateTime(RTC_Time.Hours, RTC_Time.Minutes, RTC_Time.Seconds);


	if(xQueueReceive(Q_Mb2Gui_AcOnOff,&Gpio_TempState,0) == pdTRUE)
	{
		// Update New value //
		modelListener->AC_SetOnOff(Gpio_TempState);
	}
	if(xQueueReceive(Q_Mb2Gui_AcTempUpdate,&Ac_Value,0) == pdTRUE)
	{
		modelListener->AC_Setnewvalue(Ac_Value);
	}

	if(xQueueReceive(Q_Mb2Gui_Gpio0,&Gpio_TempState,0) == pdTRUE)
	{
		// Update New value //
		modelListener->LIGHT_Setnewvalue_0(Gpio_TempState);
	}
	if(xQueueReceive(Q_Mb2Gui_Gpio1,&Gpio_TempState,0) == pdTRUE)
	{
		// Update New value //
		modelListener->LIGHT_Setnewvalue_1(Gpio_TempState);
	}
	if(xQueueReceive(Q_Mb2Gui_Gpio2,&Gpio_TempState,0) == pdTRUE)
	{
		// Update New value //
		modelListener->LIGHT_Setnewvalue_2(Gpio_TempState);
	}
	if(xQueueReceive(Q_Mb2Gui_Gpio3,&Gpio_TempState,0) == pdTRUE)
	{
		// Update New value //
		modelListener->LIGHT_Setnewvalue_3(Gpio_TempState);
	}
	if(xQueueReceive(Q_Mb2Gui_Gpio4,&Gpio_TempState,0) == pdTRUE)
	{
		// Update New value //
		modelListener->LIGHT_Setnewvalue_4(Gpio_TempState);
	}



	if(xQueueReceive(Q_Mb2Gui_SlaveReg_0,&Reg_0,0) == pdTRUE)
	{
		// Update New value //
		modelListener->Temp_Setnewvalue(Reg_0);
	}
	if(xQueueReceive(Q_Mb2Gui_SlaveReg_1,&Reg_1,0) == pdTRUE)
	{
		// Update New value //
		modelListener->Hump_Setnewvalue(Reg_1);
	}
	if(xQueueReceive(Q_Mb2Gui_SlaveReg_2,&Reg_2,0) == pdTRUE)
	{
		// Update New value //
		modelListener->Light_Setnewvalue(Reg_2);
	}
}

void Model::TestAction(void)
{
    	 modbus_t telegram[1];


	//  if(xSemaphoreTake((QueueHandle_t)Master_Modbus.ModBusSphrHandle , 300)==pdTRUE)
	//  {
		
	// 	 Master_ModbusData[0] = 0xFFFF;
	// 	 telegram[0].u8id = 1; // slave address
	// 	 telegram[0].u8fct = MB_FC_WRITE_COIL; // function code (this one is registers write)
	// 	 telegram[0].u16RegAdd = 0x0;
	// 	 telegram[0].u16CoilsNo = 1; // number of elements (coils or registers) to read
	// 	 telegram[0].u16reg = Master_ModbusData; // pointer to a memory array
	// 	 ModbusQueryInject(&Master_Modbus, telegram[0]);
	// 	 xSemaphoreGive((QueueHandle_t)Master_Modbus.ModBusSphrHandle);

	//  }
    // // 	modbus_t telegram[1];

	// //Master_ModbusData[0] = value;

	// //xSemaphoreTake((QueueHandle_t)ModbusH.ModBusSphrHandle , portMAX_DELAY);
	// telegram[0].u8id = 1; // slave address
	// telegram[0].u8fct = MB_FC_WRITE_COIL; // function code (this one is registers write)
	// telegram[0].u16RegAdd = 0x0;
	// telegram[0].u16CoilsNo = 1; // number of elements (coils or registers) to read
	// telegram[0].u16reg = Master_ModbusData; // pointer to a memory array
	// //xSemaphoreGive((QueueHandle_t)ModbusH.ModBusSphrHandle);
	// ModbusQueryInject(&Master_Modbus, telegram[0]);
}
