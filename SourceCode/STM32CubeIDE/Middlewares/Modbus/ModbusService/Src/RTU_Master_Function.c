/**
 * @file RTU_Master_Function.c
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "RTU_Master_Function.h"
#include "Modbus_DeviceTrace.h"
#include "Master_Polling.h"


#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

#define lowByte(w) ((w) & 0xff)
#define highByte(w) ((w) >> 8)

/**
 * @brief
 * This method creates a mword from 2 bytes
 *
 * @return uint16_t (mword)
 * @ingroup H  Most significant byte
 * @ingroup L  Less significant byte
 */
uint16_t mword(uint8_t H, uint8_t L)
{
	bytesFields W;
	W.u8[0] = L;
	W.u8[1] = H;
	return W.u16[0];
}

void Master_Fc1(modbusHandler_t *modH)
{
    for(uint8_t i = 0; i < MASTER_POLLING_TELEGRAM_NUM ; i++)
    {
        if(Master_Polling_Telegram[i].u8fct == MB_FC_READ_COILS)
        {
            Master_WriteCoil(Master_Polling_Telegram[i].u16RegAdd, modH->u8Buffer[ADD_HI],modH);
        }
    } 
}
void Master_Fc3(modbusHandler_t *modH)
{
    uint16_t Val;
    for(uint8_t i = 0; i < MASTER_POLLING_TELEGRAM_NUM ; i++)
    {
        if(Master_Polling_Telegram[i].u8fct == MB_FC_READ_REGISTERS)
        {
            Val = mword(modH->u8Buffer[3],modH->u8Buffer[4]);
            Master_WriteReg(Master_Polling_Telegram[i].u16RegAdd, Val, modH);
            Val = mword(modH->u8Buffer[5],modH->u8Buffer[6]);
            Master_WriteReg(Master_Polling_Telegram[i].u16RegAdd+1, Val, modH);
        }
    }
}
