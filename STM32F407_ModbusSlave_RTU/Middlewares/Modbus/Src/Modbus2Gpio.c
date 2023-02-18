#include "main.h"
#include "Modbus2Gpio.h"

void WriteGpio(uint16_t Pin, bool State)
{
    HAL_GPIO_WritePin(GPIO_PORT,Pin,(GPIO_PinState)State);
}

