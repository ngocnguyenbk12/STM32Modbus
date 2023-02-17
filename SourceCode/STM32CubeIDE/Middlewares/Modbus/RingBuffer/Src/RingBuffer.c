/**
 * @file RingBuffer.c
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "RingBuffer.h"


static RingBuffer Buffer;
static RingBuffer nullptr;
static Std_ReturnType RingBuffer_CheckAvailable(RingBuffer * Buffer)
{
    Std_ReturnType RetVal = E_NOT_OK;
    if(Buffer->Head == Buffer->Tail)
    {
        return RetVal;
    }
    else
    {
        RetVal = E_OK;
    }
    return RetVal;
}

/**
 * @brief Return Ring Buffer pointer. This function only use for Single port
 * 
 * @return RingBuffer* 
 */
RingBuffer * RingBuffer_Init(void)
{
    Buffer.Head = 0;
    Buffer.Tail = 0;
    Buffer.Overflow = false;
    return &Buffer;
}
/**
 * @brief DeInit Ring Buffer. This function require nullptr supported
 * 
 * @return RingBuffer* 
 */
RingBuffer * RingBuffer_DeInit(void)
{
    return &nullptr;
}

/**
 * @brief This function should be involked after Disable Uart interrupt
 * 
 * @param Buffer 
 * @param data 
 */
void RingBuffer_Stuffing(RingBuffer * Buffer, uint8_t data)
{
    Buffer->Head++;
    if(Buffer->Head == RINGBUFFER_SIZE)
    {
        Buffer->Head = 0;
    }
    Buffer->Buffer[Buffer->Head] = data;
}

/**
 * @brief This function should be involked after Disable Uart interrupt
 * 
 * @param Buffer 
 * @param BufferOut 
 * @param Buffersize 
 * @return Std_ReturnType 
 */
Std_ReturnType RingBuffer_GetBufffer(RingBuffer * Buffer, uint8_t * BufferOut,uint16_t Buffersize)
{
    Std_ReturnType RetVal = E_NOT_OK;
    if(RingBuffer_CheckAvailable(Buffer) == E_OK)
    {
        for (uint16_t i = Buffer->Tail; i <= Buffer->Head; i++)
        {
            BufferOut[i] = Buffer->Buffer[i];
        }
        Buffersize = Buffer->Head = Buffer->Tail;
        Buffer->Tail = Buffer->Head;
        RetVal = E_OK;
    }
    else
    {   
        /* Do Nothing, Return E_NOT_OK, issues Buffer is not available. */
    }
    return RetVal;
}

/**
 * @brief . This function should be involked after Disable Uart interrupt
 * 
 * @param xRingBuffer 
 * @param u8Val 
 */
void RingAdd(modbusRingBuffer_t *xRingBuffer, uint8_t u8Val)
{

	xRingBuffer->uxBuffer[xRingBuffer->u8end] = u8Val;
	xRingBuffer->u8end = (xRingBuffer->u8end + 1) % MAX_BUFFER;
	if (xRingBuffer->u8available == MAX_BUFFER)
	{
		xRingBuffer->overflow = true;
		xRingBuffer->u8start = (xRingBuffer->u8start + 1) % MAX_BUFFER;
	}
	else
	{
		xRingBuffer->overflow = false;
		xRingBuffer->u8available++;
	}

}



/**
 * @brief Get N data from Ring Buffer. This function should be involked after Disable Uart interrupt
 * 
 * @param xRingBuffer 
 * @param buffer 
 * @param uNumber 
 * @return uint8_t 
 */
uint8_t RingGetNBytes(modbusRingBuffer_t *xRingBuffer, uint8_t *buffer, uint8_t uNumber)
{
	uint8_t uCounter;
	if(xRingBuffer->u8available == 0  || uNumber == 0 ) return 0;
	if(uNumber > MAX_BUFFER) return 0;
	for(uCounter = 0; uCounter < uNumber && uCounter< xRingBuffer->u8available ; uCounter++)
	{
		buffer[uCounter] = xRingBuffer->uxBuffer[xRingBuffer->u8start];
		xRingBuffer->u8start = (xRingBuffer->u8start + 1) % MAX_BUFFER;
	}
	xRingBuffer->u8available = xRingBuffer->u8available - uCounter;
	xRingBuffer->overflow = false;
	RingClear(xRingBuffer);
	return uCounter;
}

/**
 * @brief 
 * 
 * @param xRingBuffer 
 * @return uint8_t 
 */
uint8_t RingCountBytes(modbusRingBuffer_t *xRingBuffer)
{
	return xRingBuffer->u8available;
}

/**
 * @brief Clear all the Buffer
 * 
 * @param xRingBuffer 
 */
void RingClear(modbusRingBuffer_t *xRingBuffer)
{
	xRingBuffer->u8start = 0;
	xRingBuffer->u8end = 0;
	xRingBuffer->u8available = 0;
	xRingBuffer->overflow = false;
}

/**
 * @brief Get all data from Ring Buffer. This function should be involked after Disable Uart interrupt
 * 
 * @param xRingBuffer 
 * @param buffer 
 * @return uint8_t 
 */
uint8_t RingGetAllBytes(modbusRingBuffer_t *xRingBuffer, uint8_t *buffer)
{
	return RingGetNBytes(xRingBuffer, buffer, xRingBuffer->u8available);
}
