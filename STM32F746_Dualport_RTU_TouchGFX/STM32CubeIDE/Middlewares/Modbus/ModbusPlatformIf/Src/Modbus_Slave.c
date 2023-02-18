/**
 * @file Modbus_Slave.c
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
#include "TCP_Slave_Function.h"
#include "Modbus_Func.h"
#include "RingBuffer.h"
#include "Crc.h"

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/
#if ENABLE_TCP == 1
#include "api.h"
#include "ip4_addr.h"
#include "netif.h"
#endif

#define lowByte(w) ((w) & 0xff)
#define highByte(w) ((w) >> 8)
/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
///Queue Modbus telegrams for master
const osMessageQueueAttr_t QueueTelegram_attributes = {
       .name = "QueueModbusTelegram"
};


const osThreadAttr_t myTaskModbusA_attributes = {
    .name = "TaskModbusSlave",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128 * 4
};

const osThreadAttr_t myTaskModbusA_attributesTCP = {
    .name = "TaskModbusSlave",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 256 * 4
};



//Task Modbus Master
//osThreadId_t myTaskModbusAHandle;
const osThreadAttr_t myTaskModbusB_attributes = {
    .name = "TaskModbusMaster",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 128 * 4
};


const osThreadAttr_t myTaskModbusB_attributesTCP = {
    .name = "TaskModbusMaster",
    .priority = (osPriority_t) osPriorityNormal,
    .stack_size = 256 * 4
};

//Semaphore to access the Modbus Data
const osSemaphoreAttr_t ModBusSphr_attributes = {
    .name = "ModBusSphr"
};

modbusHandler_t *mHandlers[MAX_M_HANDLERS];
uint8_t numberHandlers = 0;
uint16_t ModbusDATA[10];
modbusHandler_t Slave_Modbus;
ModbusSlave_Device SlaveDevice;

/******************************************************************************
* Function Prototypes
*******************************************************************************/

static void sendTxBuffer(modbusHandler_t *modH);
static int16_t getRxBuffer(modbusHandler_t *modH);
static uint8_t validateAnswer(modbusHandler_t *modH);
static void buildException( uint8_t u8exception, modbusHandler_t *modH );
static uint8_t validateRequest(modbusHandler_t * modH);
static uint16_t word(uint8_t H, uint8_t l);
static void vTimerCallbackT35(TimerHandle_t *pxTimer);
static void vTimerCallbackTimeout(TimerHandle_t *pxTimer);
//static int16_t getRxBuffer(modbusHandler_t *modH);
static int8_t SendQuery(modbusHandler_t *modH ,  modbus_t telegram);

/******************************************************************************
* Function Definitions
*******************************************************************************/

#if ENABLE_TCP ==1

static bool TCPwaitConnData(modbusHandler_t *modH);
static void  TCPinitserver(modbusHandler_t *modH);
static mb_errot_t TCPconnectserver(modbusHandler_t * modH, modbus_t *telegram);
static mb_errot_t TCPgetRxBuffer(modbusHandler_t * modH);

#endif






/* End of Ring Buffer functions */



const unsigned char fctsupported[] =
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

void SModbus_Init(void)
{
	Slave_Modbus.uModbusType = MB_SLAVE;
	Slave_Modbus.u8id = 1; //slave ID
	Slave_Modbus.xTypeHW = USART_HW;
	Slave_Modbus.port =  &SLAVE_MODBUS_PORT;
	Slave_Modbus.u16timeOut = 1000;
	Slave_Modbus.EN_Port = NULL; 
	Slave_Modbus.u16regs = &ModbusDATA;
	Slave_Modbus.u16regsize= 0xFFFF; //sizeof(ModbusDATA)/sizeof(ModbusDATA[0]);
	//Slave_Modbus.xTypeHW = TCP_HW;
	//Slave_Modbus.uTcpPort = 502;   // used only for the slave (i.e., server)
	Slave_Modbus.Device = &SlaveDevice;


	Slave_Modbus.Device->Coil[0].Addr = 0x0000;
	Slave_Modbus.Device->Coil[0].Value = true;
	Slave_Modbus.Device->Coil[1].Addr = 0x0001;
	Slave_Modbus.Device->Coil[1].Value = true;
	Slave_Modbus.Device->Coil[2].Addr = 0x0002;
	Slave_Modbus.Device->Coil[2].Value = true;
	Slave_Modbus.Device->Coil[3].Addr = 0x0003;
	Slave_Modbus.Device->Coil[3].Value = true;
	Slave_Modbus.Device->Coil[4].Addr = 0x0004;
	Slave_Modbus.Device->Coil[4].Value = true;
	Slave_Modbus.Device->Reg[0].Addr = 30000;
	Slave_Modbus.Device->Reg[1].Addr = 30001;
	Slave_Modbus.Device->Reg[2].Addr = 30002;
	Slave_Modbus.Device->Reg[3].Addr = 30003;
	Slave_Modbus.Device->Reg[4].Addr = 30004;
	Slave_Modbus.Device->Reg[0].Value = 0x0020;
	Slave_Modbus.Device->Reg[1].Value = 0x0010;
	Slave_Modbus.Device->Reg[2].Value = 0x0020;
	Slave_Modbus.Device->Reg[3].Value = 0x0040;
	Slave_Modbus.Device->Reg[4].Value = 0xff20;




	Slave_Modbus.Device->Coil[5].Addr = AC_ONOFF_STATE_ADDR;
	Slave_Modbus.Device->Coil[5].Value = false;
	Slave_Modbus.Device->Reg[5].Addr = AC_TEMP_VALUE_ADDR;
	Slave_Modbus.Device->Reg[5].Value = 0;

	Slave_Modbus.Device->Coil[6].Addr = GPIO_0_ADDR;
	Slave_Modbus.Device->Coil[6].Value = false;
	Slave_Modbus.Device->Coil[7].Addr = GPIO_1_ADDR;
	Slave_Modbus.Device->Coil[7].Value = false;
	Slave_Modbus.Device->Coil[8].Addr = GPIO_2_ADDR;
	Slave_Modbus.Device->Coil[8].Value = false;
	Slave_Modbus.Device->Coil[9].Addr = GPIO_3_ADDR;
	Slave_Modbus.Device->Coil[9].Value = false;
	Slave_Modbus.Device->Coil[10].Addr = GPIO_4_ADDR;
	Slave_Modbus.Device->Coil[10].Value = false;

	Slave_Modbus.Device->Reg[6].Addr = SLAVE_10_ADDR;
	Slave_Modbus.Device->Reg[6].Value = 0;
	Slave_Modbus.Device->Reg[7].Addr = SLAVE_11_ADDR;
	Slave_Modbus.Device->Reg[7].Value = 0;
	Slave_Modbus.Device->Reg[8].Addr = SLAVE_12_ADDR;

	ModbusInit(&Slave_Modbus);
	ModbusStart(&Slave_Modbus);
}



/**
 * @brief
 * Initialization for a Master/Slave.
 * this function will check the configuration parameters
 * of the modbus handler
 *
 * @param modH   modbus handler
 */
void ModbusInit(modbusHandler_t * modH)
{

  if (numberHandlers < MAX_M_HANDLERS)
  {

	  //Initialize the ring buffer

	  RingClear(&modH->xBufferRX);

	  if(modH->uModbusType == MB_SLAVE)
	  {
		  //Create Modbus task slave
#if ENABLE_TCP == 1
		  if( modH->xTypeHW == TCP_HW)
		  {
			  modH->myTaskModbusAHandle = osThreadNew(StartTaskModbusSlave, modH, &myTaskModbusA_attributesTCP);
		  }
		  else{
			  modH->myTaskModbusAHandle = osThreadNew(StartTaskModbusSlave, modH, &myTaskModbusA_attributes);
		  }
#else
		  modH->myTaskModbusAHandle = osThreadNew(StartTaskModbusSlave, modH, &myTaskModbusA_attributes);
#endif


	  }
	  else if (modH->uModbusType == MB_MASTER)
	  {
		  //Create Modbus task Master  and Queue for telegrams

#if ENABLE_TCP == 1
		  if( modH->xTypeHW == TCP_HW)
		  {
		    //  modH->myTaskModbusAHandle = osThreadNew(StartTaskModbusMaster, modH, &myTaskModbusB_attributesTCP);
		  }
		  else
		  {
		    //  modH->myTaskModbusAHandle = osThreadNew(StartTaskModbusMaster, modH, &myTaskModbusB_attributes);
		  }
#else
		//   modH->myTaskModbusAHandle = osThreadNew(StartTaskModbusMaster, modH, &myTaskModbusB_attributes);
#endif



		  modH->xTimerTimeout=xTimerCreate("xTimerTimeout",  // Just a text name, not used by the kernel.
				  	  	modH->u16timeOut ,     		// The timer period in ticks.
						pdFALSE,         // The timers will auto-reload themselves when they expire.
						( void * )modH->xTimerTimeout,     // Assign each timer a unique id equal to its array index.
						(TimerCallbackFunction_t) vTimerCallbackTimeout  // Each timer calls the same callback when it expires.
                  	  	);

		  if(modH->xTimerTimeout == NULL)
		  {
			  while(1); //error creating timer, check heap and stack size
		  }


		  modH->QueueTelegramHandle = osMessageQueueNew (MAX_TELEGRAMS, sizeof(modbus_t), &QueueTelegram_attributes);

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
                                    (TimerCallbackFunction_t) vTimerCallbackT35     // Each timer calls the same callback when it expires.
                                    );
	  if (modH->xTimerT35 == NULL)
	  {
		  while(1); //Error creating the timer, check heap and stack size
	  }


	  modH->ModBusSphrHandle = osSemaphoreNew(1, 1, &ModBusSphr_attributes);

	  if(modH->ModBusSphrHandle == NULL)
	  {
		  while(1); //Error creating the semaphore, check heap and stack size
	  }

	  mHandlers[numberHandlers] = modH;
	  numberHandlers++;
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
void ModbusStart(modbusHandler_t * modH)
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

          //check that port is initialized
          while (HAL_UART_GetState(modH->port) != HAL_UART_STATE_READY)
          {

          }


          // Receive data from serial port for Modbus using interrupt
          if(HAL_UART_Receive_IT(modH->port, &modH->dataRX, 1) != HAL_OK)
          {
                while(1)
                {
                     	  //error in your initialization code
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

#if ENABLE_TCP == 1



#endif


    modH->u8lastRec = modH->u8BufferSize = 0;
    modH->u16InCnt = modH->u16OutCnt = modH->u16errCnt = 0;

}


void vTimerCallbackT35(TimerHandle_t *pxTimer)
{
	//Notify that a stream has just arrived
	int i;
	//TimerHandle_t aux;
	for(i = 0; i < numberHandlers; i++)
	{
		if( (TimerHandle_t *)mHandlers[i]->xTimerT35 ==  pxTimer ){
			if(mHandlers[i]->uModbusType == MB_MASTER)
			{
				xTimerStop(mHandlers[i]->xTimerTimeout,0);
			}
			xTaskNotify(mHandlers[i]->myTaskModbusAHandle, 0, eSetValueWithOverwrite);
		}
	}
}

void vTimerCallbackTimeout(TimerHandle_t *pxTimer)
{
	//Notify that a stream has just arrived
	int i;
	//TimerHandle_t aux;
	for(i = 0; i < numberHandlers; i++)
	{
		if( (TimerHandle_t *)mHandlers[i]->xTimerTimeout ==  pxTimer ){
				xTaskNotify(mHandlers[i]->myTaskModbusAHandle, ERR_TIME_OUT, eSetValueWithOverwrite);
		}
	}

}


#if ENABLE_TCP ==1

bool TCPwaitConnData(modbusHandler_t *modH)
{
  struct netbuf *inbuf;
  err_t recv_err, accept_err;
  char* buf;
  uint16_t buflen;
  uint16_t uLength;
  bool xTCPvalid;
  xTCPvalid = false;
  tcpclients_t *clientconn;

  //select the next connection slot to work with using round-robin
  modH->newconnIndex++;
  if (modH->newconnIndex>NUMBERTCPCONN)
  {
	  modH->newconnIndex = 0;
  }
  clientconn = &modH->newconns[modH->newconnIndex];


  //NULL means there is a free connection slot, so we can accept an incoming client connection
  if (clientconn->conn == NULL){
      /* accept any incoming connection */
	  accept_err = netconn_accept(modH->conn, &clientconn->conn);
	  if(accept_err != ERR_OK)
	  {
		  // not valid incoming connection at this time
		  //ModbusCloseConn(clientconn->conn);
		  ModbusCloseConnNull(modH);
		  return xTCPvalid;
      }
	  else
	  {
		  clientconn->aging=0;
	  }

  }

  netconn_set_recvtimeout(clientconn->conn ,  modH->u16timeOut);
  recv_err = netconn_recv(clientconn->conn, &inbuf);

  if (recv_err == ERR_CLSD) //the connection was closed
  {
	  //Close and clean the connection
	  //ModbusCloseConn(clientconn->conn);
	  ModbusCloseConnNull(modH);

	  clientconn->aging = 0;
	  return xTCPvalid;

  }

  if (recv_err == ERR_TIMEOUT) //No new data
   {
 	  //continue the aging process
	  modH->newconns[modH->newconnIndex].aging++;

	  // if the connection is old enough and inactive close and clean it up
	  if (modH->newconns[modH->newconnIndex].aging >= TCPAGINGCYCLES)
	  {
		  //ModbusCloseConn(clientconn->conn);
		  ModbusCloseConnNull(modH);
		  clientconn->aging = 0;
	  }

 	  return xTCPvalid;

   }

  if (recv_err == ERR_OK)
  {
      if (netconn_err(clientconn->conn) == ERR_OK)
      {
    	  /* Read the data from the port, blocking if nothing yet there.
    	  We assume the request (the part we care about) is in one netbuf */
   	      netbuf_data(inbuf, (void**)&buf, &buflen);
		  if (buflen>11) // minimum frame size for modbus TCP
		  {
			  if(buf[2] == 0 || buf[3] == 0 ) //validate protocol ID
			  {
			  	  uLength = (buf[4]<<8 & 0xff00) | buf[5];
			  	  if(uLength< (MAX_BUFFER-2)  && (uLength + 6) <= buflen)
			   	  {
			          for(int i = 0; i < uLength; i++)
			          {
			        	  modH->u8Buffer[i] = buf[i+6];
			          }
			          modH->u16TransactionID = (buf[0]<<8 & 0xff00) | buf[1];
			          modH->u8BufferSize = uLength + 2; //add 2 dummy bytes for CRC
			          xTCPvalid = true; // we have data for the modbus slave

			      }
			  }

		  }
		  netbuf_delete(inbuf); // delete the buffer always
		  clientconn->aging = 0; //reset the aging counter
	   }
   }

  return xTCPvalid;

}


void  TCPinitserver(modbusHandler_t *modH)
{
      err_t err;

	  /* Create a new TCP connection handle */
	  if(modH-> xTypeHW == TCP_HW)
	  {
		modH->conn = netconn_new(NETCONN_TCP);
		if (modH->conn!= NULL)
		{
			/* Bind to port (502) Modbus with default IP address */
			if(modH->uTcpPort == 0) modH->uTcpPort = 502; //if port not defined
			err = netconn_bind(modH->conn, NULL, modH->uTcpPort);
			if (err == ERR_OK)
			{
				/* Put the connection into LISTEN state */
				netconn_listen(modH->conn);
				netconn_set_recvtimeout(modH->conn, 1); // this is necessary to make it non blocking
			}
			else
			{
				while(1)
				{
					// error binding the TCP Modbus port check your configuration
				}
			}
		}
		else
		{
			while(1)
			{
			// error creating new connection check your configuration,
			// this function must be called after the scheduler is started
			}
		}
	  }
}

#endif



void StartTaskModbusSlave(void *argument)
{

  modbusHandler_t *modH =  (modbusHandler_t *)argument;
  //uint32_t notification;

#if ENABLE_TCP ==1
  if( modH->xTypeHW == TCP_HW )
  {
	  TCPinitserver(modH); // start the Modbus server slave
  }
#endif

  for(;;)
  {

	modH->i8lastError = 0;

#if ENABLE_TCP ==1
	  if(modH-> xTypeHW == TCP_HW)
	  {

		  if(TCPwaitConnData(modH) == false) // wait for connection and receive data
		  {
			continue; // TCP package was not validated
		  }

	  }
#endif


   if(modH->xTypeHW == USART_HW || modH->xTypeHW == USART_HW_DMA)
   {

	  ulTaskNotifyTake(pdTRUE, portMAX_DELAY); /* Block until a Modbus Frame arrives */

	  if (getRxBuffer(modH) == ERR_BUFF_OVERFLOW)
	  {
	      modH->i8lastError = ERR_BUFF_OVERFLOW;
	   	  modH->u16errCnt++;
		  continue;
	  }

   }

   if (modH->u8BufferSize < 7)
   {
      //The size of the frame is invalid
      modH->i8lastError = ERR_BAD_SIZE;
      modH->u16errCnt++;

	  continue;
    }


   // check slave id
    if ( modH->u8Buffer[ID] !=  modH->u8id)
	{

#if ENABLE_TCP == 0
    	continue; // continue this is not for us
#else
    	if(modH->xTypeHW != TCP_HW)
    	{
    		continue; //for Modbus TCP this is not validated, user should modify accordingly if needed
    	}
#endif
	 }

	  // validate message: CRC, FCT, address and size
    uint8_t u8exception = validateRequest(modH);
	if (u8exception > 0)
	{
	    if (u8exception != ERR_TIME_OUT)
		{
		    buildException( u8exception, modH);
			sendTxBuffer(modH);
		}
		modH->i8lastError = u8exception;
		//return u8exception

		continue;
	 }

	 modH->i8lastError = 0;
	xSemaphoreTake(modH->ModBusSphrHandle , portMAX_DELAY); //before processing the message get the semaphore

	 // process message
	 switch(modH->u8Buffer[ FUNC ] )
	 {
			case MB_FC_READ_COILS:
			case MB_FC_READ_DISCRETE_INPUT:
				modH->i8state = Slave_Fc1(modH);
				break;
			case MB_FC_READ_INPUT_REGISTER:
			case MB_FC_READ_REGISTERS :
				modH->i8state = Slave_Fc3(modH);
				break;
			case MB_FC_WRITE_COIL:
				modH->i8state = Slave_Fc5(modH);
				break;
			case MB_FC_WRITE_REGISTER :
				modH->i8state = Slave_Fc6(modH);
				break;
			case MB_FC_WRITE_MULTIPLE_COILS:
				modH->i8state = Slave_Fc15(modH);
				break;
			case MB_FC_WRITE_MULTIPLE_REGISTERS :
				modH->i8state = Slave_Fc16(modH);
				break;
			default:
				break;
	 }
	sendTxBuffer(modH);

	 xSemaphoreGive(modH->ModBusSphrHandle); //Release the semaphore

	 continue;

   }

}




#if ENABLE_TCP ==1
void ModbusCloseConn(struct netconn *conn)
{

	if(conn != NULL)
	{
		netconn_close(conn);
		netconn_delete(conn);
	}

}

void ModbusCloseConnNull(modbusHandler_t * modH)
{

	if(modH->newconns[modH->newconnIndex].conn  != NULL)
	{

		netconn_close(modH->newconns[modH->newconnIndex].conn);
		netconn_delete(modH->newconns[modH->newconnIndex].conn);
		modH->newconns[modH->newconnIndex].conn = NULL;
	}

}

#endif


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

#if ENABLE_TCP == 1

static  mb_errot_t TCPconnectserver(modbusHandler_t * modH, modbus_t *telegram)
{


	err_t err;
	 tcpclients_t *clientconn;


	//select the current connection slot to work with
    clientconn = &modH->newconns[modH->newconnIndex];

	if(telegram->u8clientID >= NUMBERTCPCONN )
	{
		return ERR_BAD_TCP_ID;
	}

	// if the connection is null open a new connection
	if (clientconn->conn == NULL)
	{
		 clientconn->conn = netconn_new(NETCONN_TCP);
	     if (clientconn->conn  == NULL)
	     {
	   	     while(1)
	   	     {
	     	  // error creating new connection check your configuration and heap size
	     	 }
	     }


	     err = netconn_connect(clientconn->conn, (ip_addr_t *)&telegram->xIpAddress, telegram->u16Port);

	     if (err  != ERR_OK )
	     {

	    	   //ModbusCloseConn(clientconn->conn);
	    	   ModbusCloseConnNull(modH);

	           return ERR_TIME_OUT;
	      }
	}
	return ERR_OK;
}


static mb_errot_t TCPgetRxBuffer(modbusHandler_t * modH)
{

	struct netbuf *inbuf;
	err_t err = ERR_TIME_OUT;
	char* buf;
	uint16_t buflen;
	uint16_t uLength;

	 tcpclients_t *clientconn;
	 //select the current connection slot to work with
     clientconn = &modH->newconns[modH->newconnIndex];

	netconn_set_recvtimeout(clientconn->conn, modH->u16timeOut);
	err = netconn_recv(clientconn->conn, &inbuf);

	uLength = 0;

    if (err == ERR_OK)
    {
    	err = netconn_err(clientconn->conn) ;
    	if (err == ERR_OK)
    	{
    		/* Read the data from the port, blocking if nothing yet there.
   	  	  	We assume the request (the part we care about) is in one netbuf */
  	        err = netbuf_data(inbuf, (void**)&buf, &buflen);
  	        if(err == ERR_OK )
  	        {
                 if( (buflen>11  && (modH->uModbusType == MB_SLAVE  ))  ||
                	 (buflen>=10 && (modH->uModbusType == MB_MASTER ))  ) // minimum frame size for modbus TCP
                 {
        	         if(buf[2] == 0 || buf[3] == 0 ) //validate protocol ID
        	         {
        	  	          uLength = (buf[4]<<8 & 0xff00) | buf[5];
        	  	          if(uLength< (MAX_BUFFER-2)  && (uLength + 6) <= buflen)
        	  	          {
        	  	  	          for(int i = 0; i < uLength; i++)
        	  	  	          {
        	  	  	  	         modH->u8Buffer[i] = buf[i+6];
        	  	  	          }
        	  	  	          modH->u16TransactionID = (buf[0]<<8 & 0xff00) | buf[1];
        	  	  	          modH->u8BufferSize = uLength + 2; //include 2 dummy bytes for CRC
        	  	           }
        	          }
                  }
  	        } // netbuf_data
  	        netbuf_delete(inbuf); //delete the buffer always
    	}
    }

    //netconn_close(modH->newconn);
	//netconn_delete(modH->newconn);
	return err;
}

#endif





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

#if ENABLE_TCP ==1
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
#if ENABLE_TCP ==1
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
    for (uint8_t i = 0; i< sizeof( fctsupported ); i++)
    {
        if (fctsupported[i] == modH->u8Buffer[FUNC])
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

#if ENABLE_TCP ==1
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
	    for (uint8_t i = 0; i< sizeof( fctsupported ); i++)
	    {
	        if (fctsupported[i] == modH->u8Buffer[FUNC])
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

#if  ENABLE_TCP == 1
if(modH->xTypeHW != TCP_HW)
	 {
#endif

	uint16_t u16crc = calcCRC(modH->u8Buffer, modH->u8BufferSize);
    modH->u8Buffer[ modH->u8BufferSize ] = u16crc >> 8;
    modH->u8BufferSize++;
    modH->u8Buffer[ modH->u8BufferSize ] = u16crc & 0x00ff;
    modH->u8BufferSize++;

#if ENABLE_TCP == 1
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
#if ENABLE_TCP == 1

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




