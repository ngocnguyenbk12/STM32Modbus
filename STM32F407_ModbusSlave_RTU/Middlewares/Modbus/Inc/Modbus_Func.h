#include "Modbus.h"


uint16_t calcCRC(uint8_t *Buffer, uint8_t u8length);
void RingAdd(modbusRingBuffer_t *xRingBuffer, uint8_t u8Val); // adds a byte to the ring buffer
uint8_t RingGetAllBytes(modbusRingBuffer_t *xRingBuffer, uint8_t *buffer); // gets all the available bytes into buffer and return the number of bytes read
uint8_t RingGetNBytes(modbusRingBuffer_t *xRingBuffer, uint8_t *buffer, uint8_t uNumber); // gets uNumber of bytes from ring buffer, returns the actual number of bytes read
uint8_t RingCountBytes(modbusRingBuffer_t *xRingBuffer); // return the number of available bytes
void RingClear(modbusRingBuffer_t *xRingBuffer); // flushes the ring buffer
void setTimeOut( uint16_t u16timeOut); //!<write communication watch-dog timer
uint16_t getTimeOut(); //!<get communication watch-dog timer value
bool getTimeOutState(); //!<get communication watch-dog timer state
void ModbusQuery(modbusHandler_t * modH, modbus_t telegram ); // put a query in the queue tail
void ModbusQueryInject(modbusHandler_t * modH, modbus_t telegram); //put a query in the queue head








