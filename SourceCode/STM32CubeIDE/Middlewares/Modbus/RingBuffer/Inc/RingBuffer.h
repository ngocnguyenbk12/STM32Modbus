/**
 * @file RingBuffer.h
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <inttypes.h>
#include <stdbool.h>
#include "StdType.h"
#include "Modbus.h"


#ifndef RING_BUFFER_H_
#define RING_BUFFER_H_

#define RINGBUFFER_SIZE     (128U)

typedef struct _RingBuffer_
{
    uint16_t Head;
    uint16_t Tail;
    uint8_t Buffer[RINGBUFFER_SIZE];
    bool Overflow;
}RingBuffer;

typedef struct
{
uint8_t uxBuffer[MAX_BUFFER];
uint8_t u8start;
uint8_t u8end;
uint8_t u8available;
bool    overflow;
}modbusRingBuffer_t;


RingBuffer * RingBuffer_Init(void);
RingBuffer * RingBuffer_DeInit(void);
void RingBuffer_Stuffing(RingBuffer * Buffer, uint8_t data);
Std_ReturnType RingBuffer_GetBufffer(RingBuffer * Buffer, uint8_t * BufferOut,uint16_t Buffersize);

extern void RingAdd(modbusRingBuffer_t *xRingBuffer, uint8_t u8Val); // adds a byte to the ring buffer
extern uint8_t RingGetAllBytes(modbusRingBuffer_t *xRingBuffer, uint8_t *buffer); // gets all the available bytes into buffer and return the number of bytes read
extern uint8_t RingGetNBytes(modbusRingBuffer_t *xRingBuffer, uint8_t *buffer, uint8_t uNumber); // gets uNumber of bytes from ring buffer, returns the actual number of bytes read
extern uint8_t RingCountBytes(modbusRingBuffer_t *xRingBuffer); // return the number of available bytes
extern void RingClear(modbusRingBuffer_t *xRingBuffer); // flushes the ring buffer

#endif
