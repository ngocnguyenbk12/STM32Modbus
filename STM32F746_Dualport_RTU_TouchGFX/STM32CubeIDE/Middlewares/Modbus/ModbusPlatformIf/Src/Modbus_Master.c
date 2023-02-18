/**
 * @file Modbus_Master.c
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2022-11-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "task.h"
#include "queue.h"
#include "main.h"
#include "Modbus.h"
#include "timers.h"
#include "semphr.h"
#include "Modbus_Func.h"
#include "RTU_Master_Function.h"
#include "ModbusIf.h"
#include "RingBuffer.h"
#include "Crc.h"

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/
#if ENABLE_TCP_MASTER == 1
#include "api.h"
#include "ip4_addr.h"
#include "netif.h"
#endif

#define lowByte(w) ((w) & 0xff)
#define highByte(w) ((w) >> 8)
/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
const osMessageQueueAttr_t Master_QueueTelegram_attributes = {
       .name = "QueueModbusTelegram"
};


const osThreadAttr_t Master_myTaskModbusB_attributes = {
    .name = "TaskModbusMaster",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128 * 4
};


const osThreadAttr_t Master_myTaskModbusB_attributesTCP = {
    .name = "TaskModbusMaster",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 256 * 4
};

const osSemaphoreAttr_t Master_ModBusSphr_attributes = {
    .name = "ModBusSphr"
};

uint8_t Master_numberHandlers = 0;
const unsigned char Master_fctsupported[] =
{
    MB_FC_READ_COILS,
    MB_FC_READ_DISCRETE_INPUT,
    MB_FC_READ_REGISTERS,
    MB_FC_READ_INPUT_REGISTER,
    MB_FC_WRITE_COIL,
    MB_FC_WRITE_REGISTER,
    MB_FC_WRITE_MULTIPLE_COILS,
    MB_FC_WRITE_MULTIPLE_REGISTERS
};

modbusHandler_t *MastermHandler[MAX_M_HANDLERS];
modbusHandler_t Master_Modbus;
uint16_t Master_ModbusData[20];
ModbusMaster_Device MasterDevice;

/******************************************************************************
* Function Prototypes
*******************************************************************************/
static void Master_ModbusInit(modbusHandler_t * modH);
static void Master_ModbusStart(modbusHandler_t * modH);
static void sendTxBuffer(modbusHandler_t *modH);
static int16_t getRxBuffer(modbusHandler_t *modH);
static uint8_t validateAnswer(modbusHandler_t *modH);
static void buildException( uint8_t u8exception, modbusHandler_t *modH );
static uint8_t validateRequest(modbusHandler_t * modH);
static uint16_t word(uint8_t H, uint8_t l);
static void Master_vTimerCallbackT35(TimerHandle_t *pxTimer);
static void Master_vTimerCallbackTimeout(TimerHandle_t *pxTimer);
static int8_t SendQuery(modbusHandler_t *modH ,  modbus_t telegram);
/******************************************************************************
* Function Definitions
*******************************************************************************/

void MMaster_Init(void)
{
	Master_Modbus.uModbusType = MB_MASTER;
	Master_Modbus.port =  &MASTER_MODBUS_PORT; 
	Master_Modbus.u8id = 0; 
	Master_Modbus.u16timeOut = 1000;
	Master_Modbus.EN_Port = NULL; 
	Master_Modbus.u16regs = &Master_ModbusData;
	Master_Modbus.u16regsize= 0xffff;
	Master_Modbus.xTypeHW = USART_HW;
	Master_Modbus.MasterDevice = &MasterDevice;

	Master_Modbus.MasterDevice->Coil[0].Addr = SLAVE_0_ADDR;
	Master_Modbus.MasterDevice->Coil[1].Addr = SLAVE_1_ADDR;
	Master_Modbus.MasterDevice->Coil[2].Addr = SLAVE_2_ADDR;
	Master_Modbus.MasterDevice->Coil[3].Addr = SLAVE_3_ADDR;
	Master_Modbus.MasterDevice->Coil[4].Addr = SLAVE_4_ADDR;


	Master_Modbus.MasterDevice->Reg[5].Addr = SLAVE_10_ADDR;
	Master_Modbus.MasterDevice->Reg[6].Addr = SLAVE_11_ADDR;
	Master_Modbus.MasterDevice->Reg[7].Addr = SLAVE_12_ADDR;
	Master_Modbus.MasterDevice->Reg[8].Addr = SLAVE_13_ADDR;
	Master_Modbus.MasterDevice->Reg[9].Addr = SLAVE_14_ADDR;


	Master_ModbusInit(&Master_Modbus);
	Master_ModbusStart(&Master_Modbus);
}


/**
 * @brief
 * Initialization for a Master/Slave.
 * this function will check the configuration parameters
 * of the modbus handler
 *
 * @param modH   modbus handler
 */
void Master_ModbusInit(modbusHandler_t * modH)
{

  if (Master_numberHandlers < MAX_M_HANDLERS)
  {
	  RingClear(&modH->xBufferRX);

	  if (modH->uModbusType == MB_MASTER)
	  {

#if ENABLE_TCP_MASTER == 1
		  if( modH->xTypeHW == TCP_HW)
		  {
		     modH->myTaskModbusAHandle = osThreadNew(StartTaskModbusMaster, modH, &Master_myTaskModbusB_attributesTCP);
		  }
		  else
		  {
		     modH->myTaskModbusAHandle = osThreadNew(StartTaskModbusMaster, modH, &Master_myTaskModbusB_attributes);
		  }
#else
		  modH->myTaskModbusAHandle = osThreadNew(StartTaskModbusMaster, modH, &Master_myTaskModbusB_attributes);
#endif

		  modH->xTimerTimeout=xTimerCreate("xTimerTimeout",  // Just a text name, not used by the kernel.
				  	  	modH->u16timeOut ,     		// The timer period in ticks.
						pdFALSE,         // The timers will auto-reload themselves when they expire.
						( void * )modH->xTimerTimeout,     // Assign each timer a unique id equal to its array index.
						(TimerCallbackFunction_t) Master_vTimerCallbackTimeout  // Each timer calls the same callback when it expires.
                  	  	);

		  if(modH->xTimerTimeout == NULL)
		  {
			  while(1); //error creating timer, check heap and stack size
		  }


		  modH->QueueTelegramHandle = osMessageQueueNew (MAX_TELEGRAMS, sizeof(modbus_t), &Master_QueueTelegram_attributes);

		  if(modH->QueueTelegramHandle == NULL)
		  {
			  while(1); //error creating queue for telegrams, check heap and stack size
		  }

	  }
	  else
	  {
		  while(1); //Error Modbus type not supported choose a valid Type
	  }

	  if  (modH->myTaskModbusAHandle == NULL)
	  {
		  while(1); //Error creating Modbus task, check heap and stack size
	  }


	  modH->xTimerT35 = xTimerCreate("TimerT35",         // Just a text name, not used by the kernel.
		  	  	  	  	  	  	  	T35 ,     // The timer period in ticks.
                                    pdFALSE,         // The timers will auto-reload themselves when they expire.
									( void * )modH->xTimerT35,     // Assign each timer a unique id equal to its array index.
                                    (TimerCallbackFunction_t) Master_vTimerCallbackT35     // Each timer calls the same callback when it expires.
                                    );
	  if (modH->xTimerT35 == NULL)
	  {
		  while(1); //Error creating the timer, check heap and stack size
	  }


	  modH->ModBusSphrHandle = osSemaphoreNew(1, 1, &Master_ModBusSphr_attributes);

	  if(modH->ModBusSphrHandle == NULL)
	  {
		  while(1); //Error creating the semaphore, check heap and stack size
	  }

	  MastermHandler[Master_numberHandlers] = modH;
	  Master_numberHandlers++;
  }
  else
  {
	  while(1); //error no more Modbus handlers supported
  }

}


/**
 * @brief
 * Start object.
 *
 * Call this AFTER calling begin() on the serial port, typically within setup().
 *
 * (If you call this function, then you should NOT call any of
 * ModbusRtu's own begin() functions.)
 *
 * @ingroup setup
 */
void Master_ModbusStart(modbusHandler_t * modH)
{

	if(modH->xTypeHW != USART_HW && modH->xTypeHW != TCP_HW && modH->xTypeHW != USB_CDC_HW  && modH->xTypeHW != USART_HW_DMA )
	{

		while(1); //ERROR select the type of hardware
	}

	if (modH->xTypeHW == USART_HW || modH->xTypeHW ==  USART_HW_DMA )
	{

	      if (modH->EN_Port != NULL )
          {
              // return RS485 transceiver to transmit mode
          	HAL_GPIO_WritePin(modH->EN_Port, modH->EN_Pin, GPIO_PIN_RESET);
          }

          if (modH->uModbusType == MB_SLAVE &&  modH->u16regs == NULL )
          {
          	while(1); //ERROR define the DATA pointer shared through Modbus
          }

          while (HAL_UART_GetState(modH->port) != HAL_UART_STATE_READY)
          {

          }


          if(ModbusIf_Serial(modH->port, modH->u16regs) != E_OK)
          {
                while(1)
                {
				}
          }

          if(modH->u8id !=0 && modH->uModbusType == MB_MASTER )
          {
        	  while(1)
        	  {
        	     	  //error Master ID must be zero
        	  }

          }

          if(modH->u8id ==0 && modH->uModbusType == MB_SLAVE )
          {
             	  while(1)
               	  {
                  	     	  //error Master ID must be zero
               	  }

           }

	}

#if ENABLE_TCP_MASTER == 1



#endif


    modH->u8lastRec = modH->u8BufferSize = 0;
    modH->u16InCnt = modH->u16OutCnt = modH->u16errCnt = 0;

}



void Master_vTimerCallbackT35(TimerHandle_t *pxTimer)
{
	int i;
	for(i = 0; i < Master_numberHandlers; i++)
	{

		if( (TimerHandle_t *)MastermHandler[i]->xTimerT35 ==  pxTimer ){
			if(MastermHandler[i]->uModbusType == MB_MASTER)
			{
				xTimerStop(MastermHandler[i]->xTimerTimeout,0);
			}
			xTaskNotify(MastermHandler[i]->myTaskModbusAHandle, 0, eSetValueWithOverwrite);
		}

	}
}

void Master_vTimerCallbackTimeout(TimerHandle_t *pxTimer)
{
	int i;
	for(i = 0; i < Master_numberHandlers; i++)
	{
		if( (TimerHandle_t *)MastermHandler[i]->xTimerTimeout ==  pxTimer ){
				xTaskNotify(MastermHandler[i]->myTaskModbusAHandle, ERR_TIME_OUT, eSetValueWithOverwrite);
		}

	}

}



/**
 * @brief
 * *** Only Modbus Master ***
 * Generate a query to an slave with a modbus_t telegram structure
 * The Master must be in COM_IDLE mode. After it, its state would be COM_WAITING.
 * This method has to be called only in loop() section.
 *
 * @see modbus_t
 * @param modH  modbus handler
 * @param modbus_t  modbus telegram structure (id, fct, ...)
 * @ingroup loop
 */
int8_t SendQuery(modbusHandler_t *modH ,  modbus_t telegram )
{
	uint8_t u8regsno, u8bytesno;
	uint8_t  error = 0;
	xSemaphoreTake(modH->ModBusSphrHandle , portMAX_DELAY); //before processing the message get the semaphore

	if (modH->u8id!=0) error = ERR_NOT_MASTER;
	if (modH->i8state != COM_IDLE) error = ERR_POLLING ;
	if ((telegram.u8id==0) || (telegram.u8id>247)) error = ERR_BAD_SLAVE_ID;


	if(error)
	{
		 modH->i8lastError = error;
		 xSemaphoreGive(modH->ModBusSphrHandle);
		 return error;
	}


	modH->u16regs = telegram.u16reg;

	// telegram header
	modH->u8Buffer[ ID ]         = telegram.u8id;
	modH->u8Buffer[ FUNC ]       = telegram.u8fct;
	modH->u8Buffer[ ADD_HI ]     = highByte(telegram.u16RegAdd );
	modH->u8Buffer[ ADD_LO ]     = lowByte( telegram.u16RegAdd );

	switch( telegram.u8fct )
	{
	case MB_FC_READ_COILS:
	case MB_FC_READ_DISCRETE_INPUT:
	case MB_FC_READ_REGISTERS:
	case MB_FC_READ_INPUT_REGISTER:
	    modH->u8Buffer[ NB_HI ]      = highByte(telegram.u16CoilsNo );
	    modH->u8Buffer[ NB_LO ]      = lowByte( telegram.u16CoilsNo );
	    modH->u8BufferSize = 6;
	    break;
	case MB_FC_WRITE_COIL:
	    modH->u8Buffer[ NB_HI ]      = (( telegram.u16reg[0]> 0) ? 0xff : 0);
	    modH->u8Buffer[ NB_LO ]      = 0;
	    modH->u8BufferSize = 6;
	    break;
	case MB_FC_WRITE_REGISTER:
	    modH->u8Buffer[ NB_HI ]      = highByte( telegram.u16reg[0]);
	    modH->u8Buffer[ NB_LO ]      = lowByte( telegram.u16reg[0]);
	    modH->u8BufferSize = 6;
	    break;
	case MB_FC_WRITE_MULTIPLE_COILS: // TODO: implement "sending coils"
	    u8regsno = telegram.u16CoilsNo / 16;
	    u8bytesno = u8regsno * 2;
	    if ((telegram.u16CoilsNo % 16) != 0)
	    {
	        u8bytesno++;
	        u8regsno++;
	    }

	    modH->u8Buffer[ NB_HI ]      = highByte(telegram.u16CoilsNo );
	    modH->u8Buffer[ NB_LO ]      = lowByte( telegram.u16CoilsNo );
	    modH->u8Buffer[ BYTE_CNT ]    = u8bytesno;
	    modH->u8BufferSize = 7;

	    for (uint16_t i = 0; i < u8bytesno; i++)
	    {
	        if(i%2)
	        {
	        	modH->u8Buffer[ modH->u8BufferSize ] = lowByte( telegram.u16reg[ i/2 ] );
	        }
	        else
	        {
	        	modH->u8Buffer[  modH->u8BufferSize ] = highByte( telegram.u16reg[ i/2 ] );

	        }
	        modH->u8BufferSize++;
	    }
	    break;

	case MB_FC_WRITE_MULTIPLE_REGISTERS:
	    modH->u8Buffer[ NB_HI ]      = highByte(telegram.u16CoilsNo );
	    modH->u8Buffer[ NB_LO ]      = lowByte( telegram.u16CoilsNo );
	    modH->u8Buffer[ BYTE_CNT ]    = (uint8_t) ( telegram.u16CoilsNo * 2 );
	    modH->u8BufferSize = 7;

	    for (uint16_t i=0; i< telegram.u16CoilsNo; i++)
	    {

	        modH->u8Buffer[  modH->u8BufferSize ] = highByte(  telegram.u16reg[ i ] );
	        modH->u8BufferSize++;
	        modH->u8Buffer[  modH->u8BufferSize ] = lowByte( telegram.u16reg[ i ] );
	        modH->u8BufferSize++;
	    }
	    break;
	}


	sendTxBuffer(modH);

	xSemaphoreGive(modH->ModBusSphrHandle);

	modH->i8state = COM_WAITING;
	modH->i8lastError = 0;
	return 0;


}





/**
 * @brief
 * This method validates master incoming messages
 *
 * @return 0 if OK, EXCEPTION if anything fails
 * @ingroup buffer
 */
uint8_t validateAnswer(modbusHandler_t *modH)
{
    // check message crc vs calculated crc

#if ENABLE_TCP_MASTER ==1
	if(modH->xTypeHW != TCP_HW)
	{
#endif
	uint16_t u16MsgCRC =
        ((modH->u8Buffer[modH->u8BufferSize - 2] << 8)
         | modH->u8Buffer[modH->u8BufferSize - 1]); // combine the crc Low & High bytes
    if ( calcCRC(modH->u8Buffer,  modH->u8BufferSize-2) != u16MsgCRC )
    {
    	modH->u16errCnt ++;
        return ERR_BAD_CRC;
    }
#if ENABLE_TCP_MASTER ==1
	}
#endif


    // check exception
    if ((modH->u8Buffer[ FUNC ] & 0x80) != 0)
    {
    	modH->u16errCnt ++;
        return ERR_EXCEPTION;
    }

    // check fct code
    bool isSupported = false;
    for (uint8_t i = 0; i< sizeof( Master_fctsupported ); i++)
    {
        if (Master_fctsupported[i] == modH->u8Buffer[FUNC])
        {
            isSupported = 1;
            break;
        }
    }
    if (!isSupported)
    {
    	modH->u16errCnt ++;
        return EXC_FUNC_CODE;
    }

    return 0; // OK, no exception code thrown
}


/**
 * @brief
 * This method moves Serial buffer data to the Modbus u8Buffer.
 *
 * @return buffer size if OK, ERR_BUFF_OVERFLOW if u8BufferSize >= MAX_BUFFER
 * @ingroup buffer
 */
int16_t getRxBuffer(modbusHandler_t *modH)
{

    int16_t i16result;

    if(modH->xTypeHW == USART_HW)
    {
    	HAL_UART_AbortReceive_IT(modH->port); // disable interrupts to avoid race conditions on serial port
    }

	if (modH->xBufferRX.overflow)
    {
       	RingClear(&modH->xBufferRX); // clean up the overflowed buffer
       	i16result =  ERR_BUFF_OVERFLOW;
    }
	else
	{
		modH->u8BufferSize = RingGetAllBytes(&modH->xBufferRX, modH->u8Buffer);
		modH->u16InCnt++;
		i16result = modH->u8BufferSize;
	}

	if(modH->xTypeHW == USART_HW)
	{
		HAL_UART_Receive_IT(modH->port, &modH->dataRX, 1);
	}

    return i16result;
}





/**
 * @brief
 * This method validates slave incoming messages
 *
 * @return 0 if OK, EXCEPTION if anything fails
 * @ingroup modH Modbus handler
 */
uint8_t validateRequest(modbusHandler_t *modH)
{
	// check message crc vs calculated crc

#if ENABLE_TCP_MASTER ==1
	    uint16_t u16MsgCRC;
		    u16MsgCRC= ((modH->u8Buffer[modH->u8BufferSize - 2] << 8)
		   	         | modH->u8Buffer[modH->u8BufferSize - 1]); // combine the crc Low & High bytes

	    if (modH->xTypeHW != TCP_HW)
	    {
	    	if ( calcCRC( modH->u8Buffer,  modH->u8BufferSize-2 ) != u16MsgCRC )
	    	{
	    		modH->u16errCnt ++;
	    		return ERR_BAD_CRC;
	    		}
	    }
#else
	    uint16_t u16MsgCRC;
	    u16MsgCRC= ((modH->u8Buffer[modH->u8BufferSize - 2] << 8)
	    		   	         | modH->u8Buffer[modH->u8BufferSize - 1]); // combine the crc Low & High bytes


	    if ( calcCRC( modH->u8Buffer,  modH->u8BufferSize-2 ) != u16MsgCRC )
	    {
	       		modH->u16errCnt ++;
	       		return ERR_BAD_CRC;
	    }


#endif

	    // check fct code
	    bool isSupported = false;
	    for (uint8_t i = 0; i< sizeof( Master_fctsupported ); i++)
	    {
	        if (Master_fctsupported[i] == modH->u8Buffer[FUNC])
	        {
	            isSupported = 1;
	            break;
	        }
	    }
	    if (!isSupported)
	    {
	    	modH->u16errCnt ++;
	        return EXC_FUNC_CODE;
	    }

	    // check start address & nb range
	    uint16_t u16AdRegs = 0;
	    uint16_t u16NRegs = 0;

	    //uint8_t u8regs;
	    switch ( modH->u8Buffer[ FUNC ] )
	    {
	    case MB_FC_READ_COILS:
	    case MB_FC_READ_DISCRETE_INPUT:
	    case MB_FC_WRITE_MULTIPLE_COILS:
	    	u16AdRegs = word( modH->u8Buffer[ ADD_HI ], modH->u8Buffer[ ADD_LO ]) / 16;
	    	u16NRegs = word( modH->u8Buffer[ NB_HI ], modH->u8Buffer[ NB_LO ]) /16;
	    	if(word( modH->u8Buffer[ NB_HI ], modH->u8Buffer[ NB_LO ]) % 16) u16NRegs++; // check for incomplete words
	    	// verify address range
	    	if((u16AdRegs + u16NRegs) > modH->u16regsize) return EXC_ADDR_RANGE;

	    	//verify answer frame size in bytes

	    	u16NRegs = word( modH->u8Buffer[ NB_HI ], modH->u8Buffer[ NB_LO ]) / 8;
	    	if(word( modH->u8Buffer[ NB_HI ], modH->u8Buffer[ NB_LO ]) % 8) u16NRegs++;
	    	u16NRegs = u16NRegs + 5; // adding the header  and CRC ( Slave address + Function code  + number of data bytes to follow + 2-byte CRC )
	        if(u16NRegs > 256) return EXC_REGS_QUANT;

	        break;
	    case MB_FC_WRITE_COIL:
	    	u16AdRegs = word( modH->u8Buffer[ ADD_HI ], modH->u8Buffer[ ADD_LO ]) / 16;
	    	if(word( modH->u8Buffer[ ADD_HI ], modH->u8Buffer[ ADD_LO ]) % 16) u16AdRegs++;	// check for incomplete words
	        if (u16AdRegs > modH->u16regsize) return EXC_ADDR_RANGE;
	        break;
	    case MB_FC_WRITE_REGISTER :
	    	u16AdRegs = word( modH->u8Buffer[ ADD_HI ], modH->u8Buffer[ ADD_LO ]);
	        if (u16AdRegs > modH-> u16regsize) return EXC_ADDR_RANGE;
	        break;
	    case MB_FC_READ_REGISTERS :
	    case MB_FC_READ_INPUT_REGISTER :
	    case MB_FC_WRITE_MULTIPLE_REGISTERS :
	    	u16AdRegs = word( modH->u8Buffer[ ADD_HI ], modH->u8Buffer[ ADD_LO ]);
	        u16NRegs = word( modH->u8Buffer[ NB_HI ], modH->u8Buffer[ NB_LO ]);
	        if (( u16AdRegs + u16NRegs ) > modH->u16regsize) return EXC_ADDR_RANGE;

	        //verify answer frame size in bytes
	        u16NRegs = u16NRegs*2 + 5; // adding the header  and CRC
	        if ( u16NRegs > 256 ) return EXC_REGS_QUANT;
	        break;
	    }
	    return 0; // OK, no exception code thrown

}

/**
 * @brief
 * This method creates a word from 2 bytes
 *
 * @return uint16_t (word)
 * @ingroup H  Most significant byte
 * @ingroup L  Less significant byte
 */
uint16_t word(uint8_t H, uint8_t L)
{
	bytesFields W;
	W.u8[0] = L;
	W.u8[1] = H;

	return W.u16[0];
}



/**
 * @brief
 * This method builds an exception message
 *
 * @ingroup u8exception exception number
 * @ingroup modH modbus handler
 */
void buildException( uint8_t u8exception, modbusHandler_t *modH )
{
    uint8_t u8func = modH->u8Buffer[ FUNC ];  // get the original FUNC code

    modH->u8Buffer[ ID ]      = modH->u8id;
    modH->u8Buffer[ FUNC ]    = u8func + 0x80;
    modH->u8Buffer[ 2 ]       = u8exception;
    modH->u8BufferSize         = EXCEPTION_SIZE;
}



/**
 * @brief
 * This method transmits u8Buffer to Serial line.
 * Only if u8txenpin != 0, there is a flow handling in order to keep
 * the RS485 transceiver in output state as long as the message is being sent.
 * This is done with TC bit.
 * The CRC is appended to the buffer before starting to send it.
 *
 * @return nothing
 * @ingroup modH Modbus handler
 */
static void sendTxBuffer(modbusHandler_t *modH)
{
    // append CRC to message

#if  ENABLE_TCP_MASTER == 1
if(modH->xTypeHW != TCP_HW)
	 {
#endif

	uint16_t u16crc = calcCRC(modH->u8Buffer, modH->u8BufferSize);
    modH->u8Buffer[ modH->u8BufferSize ] = u16crc >> 8;
    modH->u8BufferSize++;
    modH->u8Buffer[ modH->u8BufferSize ] = u16crc & 0x00ff;
    modH->u8BufferSize++;

#if ENABLE_TCP_MASTER == 1
	 }
#endif


    	if (modH->EN_Port != NULL)
        {
    		//enable transmitter, disable receiver to avoid echo on RS485 transceivers
    		HAL_HalfDuplex_EnableTransmitter(modH->port);
    		HAL_GPIO_WritePin(modH->EN_Port, modH->EN_Pin, GPIO_PIN_SET);
        }

    		// transfer buffer to serial line IT
    		HAL_UART_Transmit_IT(modH->port, modH->u8Buffer,  modH->u8BufferSize);


        ulTaskNotifyTake(pdTRUE, 250); //wait notification from TXE interrupt
/*
* If you are porting the library to a different MCU check the 
* USART datasheet and add the corresponding family in the following
* preprocessor conditions
*/
#if defined(STM32H7)  || defined(STM32F3) || defined(STM32L4)  
          while((modH->port->Instance->ISR & USART_ISR_TC) ==0 )
#else
          // F429, F103, L152 ...
	  while((modH->port->Instance->ISR & USART_ISR_TC) ==0 )
#endif
         {
 	        //block the task until the the last byte is send out of the shifting buffer in USART
         }


         if (modH->EN_Port != NULL)
         {

             //return RS485 transceiver to receive mode
        	 HAL_GPIO_WritePin(modH->EN_Port, modH->EN_Pin, GPIO_PIN_RESET);
        	 //enable receiver, disable transmitter
        	 HAL_HalfDuplex_EnableReceiver(modH->port);

         }

         // set timeout for master query
         if(modH->uModbusType == MB_MASTER )
         {
        	 xTimerReset(modH->xTimerTimeout,0);
         }


#if ENABLE_TCP_MASTER == 1

    else if(modH->xTypeHW == TCP_HW)
    	{

    	  struct netvector  xNetVectors[2];
    	  uint8_t u8MBAPheader[6];
    	  size_t uBytesWritten;


    	  u8MBAPheader[0] = highByte(modH->u16TransactionID); // this might need improvement the transaction ID could be validated
    	  u8MBAPheader[1] = lowByte(modH->u16TransactionID);
    	  u8MBAPheader[2] = 0; //protocol ID
    	  u8MBAPheader[3] = 0; //protocol ID
    	  u8MBAPheader[4] = 0; //highbyte data length always 0
    	  u8MBAPheader[5] = modH->u8BufferSize; //highbyte data length

    	  xNetVectors[0].len = 6;
    	  xNetVectors[0].ptr = (void *) u8MBAPheader;

    	  xNetVectors[1].len = modH->u8BufferSize;
    	  xNetVectors[1].ptr = (void *) modH->u8Buffer;


    	  netconn_set_sendtimeout(modH->newconns[modH->newconnIndex].conn, modH->u16timeOut);
    	  err_enum_t err;

    	  err = netconn_write_vectors_partly(modH->newconns[modH->newconnIndex].conn, xNetVectors, 2, NETCONN_COPY, &uBytesWritten);
    	  if (err != ERR_OK )
    	  {

    		 // ModbusCloseConn(modH->newconns[modH->newconnIndex].conn);
    		 ModbusCloseConnNull(modH);

    	  }


    	  if(modH->uModbusType == MB_MASTER )
    	  {
    	    xTimerReset(modH->xTimerTimeout,0);
    	  }
    	}

#endif


     modH->u8BufferSize = 0;
     // increase message counter
     modH->u16OutCnt++;


}

void StartTaskModbusMaster(void *argument)
{

  modbusHandler_t *modH =  (modbusHandler_t *)argument;
  uint32_t ulNotificationValue;
  modbus_t telegram;



  for(;;)
  {
	  /*Wait indefinitely for a telegram to send */
	  xQueueReceive(modH->QueueTelegramHandle, &telegram, portMAX_DELAY);


#if ENABLE_TCP_MASTER ==1
     if(modH->xTypeHW == TCP_HW)
     {
    	  modH->newconnIndex = telegram.u8clientID;
    	  ulNotificationValue = TCPconnectserver( modH, &telegram);
 	      if(ulNotificationValue == ERR_OK)
	      {


 	    	  SendQuery(modH, telegram);
 		     /* Block until a Modbus Frame arrives or query timeouts*/
 		      ulNotificationValue = TCPgetRxBuffer(modH); // TCP receives the data and the notification simultaneously since it is synchronous

 		      if (ulNotificationValue != ERR_OK) //close the TCP connection
 		      {

 		    	 //ModbusCloseConn(modH->newconns[modH->newconnIndex].conn);
 		    	 ModbusCloseConnNull(modH);

 		      }
	      }
 	      else
 	      {
 	    	 //ModbusCloseConn(modH->newconns[modH->newconnIndex].conn);
 	    	 ModbusCloseConnNull(modH);
 	      }
     }
     else // send a query for USART and USB_CDC
     {
   	   SendQuery(modH, telegram);
       /* Block until a Modbus Frame arrives or query timeouts*/
   	   ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
     }
#else
     // This is the case for implementations with only USART support
     SendQuery(modH, telegram);
     /* Block indefinitely until a Modbus Frame arrives or query timeouts*/
     ulNotificationValue = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

#endif

	  // notify the task the request timeout
      modH->i8lastError = 0;
      if(ulNotificationValue)
      {
    	  modH->i8state = COM_IDLE;
    	  modH->i8lastError = ERR_TIME_OUT;
    	  modH->u16errCnt++;
    	  xTaskNotify((TaskHandle_t)telegram.u32CurrentTask, modH->i8lastError, eSetValueWithOverwrite);
    	  continue;
      }


#if ENABLE_TCP_MASTER ==1

      if(modH->xTypeHW == USART_HW) //TCP and USB_CDC use different methods to get the buffer
      {
    	  getRxBuffer(modH);
      }

#else
      getRxBuffer(modH);
#endif



	  if ( modH->u8BufferSize < 6){

		  modH->i8state = COM_IDLE;
		  modH->i8lastError = ERR_BAD_SIZE;
		  modH->u16errCnt++;
		  xTaskNotify((TaskHandle_t)telegram.u32CurrentTask, modH->i8lastError, eSetValueWithOverwrite);
		  continue;
	  }

	  xTimerStop(modH->xTimerTimeout,0); // cancel timeout timer


	  // validate message: id, CRC, FCT, exception
	  int8_t u8exception = validateAnswer(modH);
	  if (u8exception != 0)
	  {
		 modH->i8state = COM_IDLE;
         modH->i8lastError = u8exception;
		 xTaskNotify((TaskHandle_t)telegram.u32CurrentTask, modH->i8lastError, eSetValueWithOverwrite);
	     continue;
	  }

	  modH->i8lastError = u8exception;

	  xSemaphoreTake(modH->ModBusSphrHandle , portMAX_DELAY); //before processing the message get the semaphore
	  // process answer
	  switch( modH->u8Buffer[ FUNC ] )
	  {
	  case MB_FC_READ_COILS:
	  case MB_FC_READ_DISCRETE_INPUT:
		  Master_Fc1(modH);
	      break;
	  case MB_FC_READ_INPUT_REGISTER:
	  case MB_FC_READ_REGISTERS :
		  Master_Fc3(modH);
	      break;
	  case MB_FC_WRITE_COIL:
	  case MB_FC_WRITE_REGISTER :
	  case MB_FC_WRITE_MULTIPLE_COILS:
	  case MB_FC_WRITE_MULTIPLE_REGISTERS :
	      // nothing to do
	      break;
	  default:
	      break;
	  }
	  modH->i8state = COM_IDLE;

	  if (modH->i8lastError ==0) // no error the error_OK, we need to use a different value than 0 to detect the timeout
	  {
		  xSemaphoreGive(modH->ModBusSphrHandle); //Release the semaphore
		  xTaskNotify((TaskHandle_t)telegram.u32CurrentTask, ERR_OK_QUERY, eSetValueWithOverwrite);
	  }


	  continue;
	 }

}















