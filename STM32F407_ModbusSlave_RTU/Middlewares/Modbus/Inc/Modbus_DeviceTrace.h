#include "main.h"
#include "stdbool.h"
#include "ModbusDevice.h"
#include "Modbus.h"


bool Read_Coil(uint16_t Addr, modbusHandler_t *modH);
uint16_t Read_Reg(uint16_t Addr, modbusHandler_t *modH);
void Write_Coil(uint16_t Addr, uint16_t Value, modbusHandler_t *modH);
void Write_Reg(uint16_t Addr, uint16_t Value, modbusHandler_t *modH);
