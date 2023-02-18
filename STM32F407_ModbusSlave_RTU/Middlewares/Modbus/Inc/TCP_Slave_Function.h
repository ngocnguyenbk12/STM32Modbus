#include "ModbusDevice.h"
#include "main.h"
#include "Modbus.h"




int8_t Slave_Fc1(modbusHandler_t *modH);
int8_t Slave_Fc3(modbusHandler_t *modH);
int8_t Slave_Fc6(modbusHandler_t *modH );
int8_t Slave_Fc16(modbusHandler_t *modH);
int8_t Slave_Fc5( modbusHandler_t *modH );
int8_t Slave_Fc15( modbusHandler_t *modH );