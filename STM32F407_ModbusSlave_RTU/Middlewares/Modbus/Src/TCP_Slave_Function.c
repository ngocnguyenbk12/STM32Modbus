#include "TCP_Slave_Function.h"
#include "Modbus.h"
#include "Modbus2Gui.h"


#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSet(value, bit) ((value) |= (1UL << (bit)))
#define bitClear(value, bit) ((value) &= ~(1UL << (bit)))
#define bitWrite(value, bit, bitvalue) ((bitvalue) ? bitSet(value, bit) : bitClear(value, bit))

#define lowByte(w) ((w) & 0xff)
#define highByte(w) ((w) >> 8)

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

int8_t Slave_Fc1(modbusHandler_t *modH)
{
    uint16_t u16currentRegister;
    uint8_t u8currentBit, u8bytesno, u8bitsno;
    uint8_t u8CopyBufferSize;
    uint16_t u16currentCoil, u16coil;

    // get the first and last coil from the message
    uint16_t u16StartCoil = word( modH->u8Buffer[ ADD_HI ], modH->u8Buffer[ ADD_LO ] );
    uint16_t u16Coilno = word( modH->u8Buffer[ NB_HI ], modH->u8Buffer[ NB_LO ] );

    // put the number of bytes in the outcoming message
    u8bytesno = (uint8_t) (u16Coilno / 8);
    if (u16Coilno % 8 != 0) u8bytesno ++;
    modH->u8Buffer[ ADD_HI ]  = u8bytesno;
    modH->u8BufferSize         = ADD_LO;
    modH->u8Buffer[modH->u8BufferSize + u8bytesno - 1 ] = 0;

    // read each coil from the register map and put its value inside the outcoming message
    u8bitsno = 0;

    for (u16currentCoil = 0; u16currentCoil < u16Coilno; u16currentCoil++)
    {
        u16coil = u16StartCoil + u16currentCoil;
        u16currentRegister =  (u16coil / 16);
        u8currentBit = (uint8_t) (u16coil % 16);

        bitWrite(
        	modH->u8Buffer[ modH->u8BufferSize ],
            u8bitsno,
		    Read_Coil(u16coil,modH) );
        u8bitsno ++;

        if (u8bitsno > 7)
        {
            u8bitsno = 0;
            modH->u8BufferSize++;
        }
    }

    // send outcoming message
    if (u16Coilno % 8 != 0) modH->u8BufferSize ++;
    u8CopyBufferSize = modH->u8BufferSize +2;
    // 
    return u8CopyBufferSize;
}
int8_t Slave_Fc3(modbusHandler_t *modH)
{
    uint16_t u16StartAdd = word( modH->u8Buffer[ ADD_HI ], modH->u8Buffer[ ADD_LO ] ) ;
    uint8_t u8regsno = word( modH->u8Buffer[ NB_HI ], modH->u8Buffer[ NB_LO ] );
    uint8_t u8CopyBufferSize;
    uint16_t i;

    modH->u8Buffer[ 2 ]       = u8regsno * 2;
    modH->u8BufferSize         = 3;
	uint16_t Val;
    for (i = u16StartAdd ; i < u16StartAdd + u8regsno; i++)
    {
    	// modH->u8Buffer[ modH->u8BufferSize ] = highByte(modH->u16regs[i]);
    	// modH->u8BufferSize++;
    	// modH->u8Buffer[ modH->u8BufferSize ] = lowByte(modH->u16regs[i]);
    	// modH->u8BufferSize++;

		// modH->u8Buffer[ modH->u8BufferSize ] = highByte(modH->Device[1].Value);
    	// modH->u8BufferSize++;
    	// modH->u8Buffer[ modH->u8BufferSize ] = lowByte(modH->Device[1].Value);
    	// modH->u8BufferSize++;
		Val = Read_Reg(i, modH);
		modH->u8Buffer[ modH->u8BufferSize ] = highByte(Val);
    	modH->u8BufferSize++;
    	modH->u8Buffer[ modH->u8BufferSize ] = lowByte(Val);
    	modH->u8BufferSize++;



    }
    u8CopyBufferSize = modH->u8BufferSize +2;
    

    return u8CopyBufferSize;
}

int8_t Slave_Fc5( modbusHandler_t *modH )
{
    uint8_t u8currentBit;
    uint16_t u16currentRegister;
    uint8_t u8CopyBufferSize;
    uint16_t u16coil = word( modH->u8Buffer[ ADD_HI ], modH->u8Buffer[ ADD_LO ] );

    // point to the register and its bit
    u16currentRegister = (u16coil / 16);
    u8currentBit = (uint8_t) (u16coil % 16);

    // // write to coil
    // // bitWrite(
    // // 	modH->u16regs[ u16currentRegister ],
    // //     u8currentBit,
	// // 	modH->u8Buffer[ NB_HI ] == 0xff );
    // // bitWrite(
    // // 	modH->u16regs[ u16currentRegister ],
    // //     u8currentBit,
	// // 	modH->u8Buffer[ NB_HI ] == 0xff );

	// Device_WriteCoil(u16coil,modH->u8Buffer[ NB_HI ]);
	// ModbusGpio_WritebyAddr(u16coil,modH->u8Buffer[ NB_HI ]);
	// Light_QueueUpdate(u16coil);

    Write_Coil(u16coil,modH->u8Buffer[ NB_HI ], modH);
	

    // send answer to master
    modH->u8BufferSize = 6;
    u8CopyBufferSize =  modH->u8BufferSize +2;
    

    return u8CopyBufferSize;
}

int8_t Slave_Fc6(modbusHandler_t *modH )
{
    uint16_t u16add = word( modH->u8Buffer[ ADD_HI ], modH->u8Buffer[ ADD_LO ] );
    uint8_t u8CopyBufferSize;
    uint16_t u16val = word( modH->u8Buffer[ NB_HI ], modH->u8Buffer[ NB_LO ] );

//     //modH->u16regs[ u16add ] = u16val;
// 	Device_WriteRegister(u16add,u16val);
// /**	USR Call Modbus Create Queue	**/
// 	Ac_TempQueueUpdate(u16val);

    Write_Reg(u16add,u16val,modH);


    // keep the same header
    modH->u8BufferSize = RESPONSE_SIZE;

    u8CopyBufferSize = modH->u8BufferSize + 2;
    

    return u8CopyBufferSize;
}

int8_t Slave_Fc16(modbusHandler_t *modH)
{
    uint16_t u16StartAdd = modH->u8Buffer[ ADD_HI ] << 8 | modH->u8Buffer[ ADD_LO ];
    uint16_t u16regsno = modH->u8Buffer[ NB_HI ] << 8 | modH->u8Buffer[ NB_LO ];
    uint8_t u8CopyBufferSize;
    uint16_t i;
    uint16_t temp;

    // build header
    modH->u8Buffer[ NB_HI ]   = 0;
    modH->u8Buffer[ NB_LO ]   = (uint8_t) u16regsno; // answer is always 256 or less bytes
    modH->u8BufferSize         = RESPONSE_SIZE;

    // write registers
    for (i = 0; i < u16regsno; i++)
    {
        temp = word(
        		modH->u8Buffer[ (BYTE_CNT + 1) + i * 2 ],
				modH->u8Buffer[ (BYTE_CNT + 2) + i * 2 ]);

        Write_Reg(u16StartAdd + i,temp, modH );

        //modH->u16regs[ u16StartAdd + i ] = temp;
    }
    u8CopyBufferSize = modH->u8BufferSize +2;
    //sendTxBuffer(modH);

    return u8CopyBufferSize;
}

int8_t Slave_Fc15( modbusHandler_t *modH )
{
     uint8_t u8currentBit, u8frameByte, u8bitsno;
    uint16_t u16currentRegister;
    uint8_t u8CopyBufferSize;
    uint16_t u16currentCoil, u16coil;
    bool bTemp;

    // get the first and last coil from the message
    uint16_t u16StartCoil = word( modH->u8Buffer[ ADD_HI ], modH->u8Buffer[ ADD_LO ] );
    uint16_t u16Coilno = word( modH->u8Buffer[ NB_HI ], modH->u8Buffer[ NB_LO ] );


    // read each coil from the register map and put its value inside the outcoming message
    u8bitsno = 0;
    u8frameByte = 7;
    for (u16currentCoil = 0; u16currentCoil < u16Coilno; u16currentCoil++)
    {

        u16coil = u16StartCoil + u16currentCoil;
		        bTemp = bitRead(
        			modH->u8Buffer[ u8frameByte ],
                    u8bitsno );
		// Device_WriteCoil(u16coil,(bool)(((modH->u8Buffer[ u8frameByte ])>>(u8bitsno)) & 0x01));
		// ModbusGpio_WritebyAddr(u16coil,(bool)(((modH->u8Buffer[ u8frameByte ])>>(u8bitsno)) & 0x01));
	    // Light_QueueUpdate(u16coil);

        Write_Coil(u16coil, (bool)(((modH->u8Buffer[ u8frameByte ])>>(u8bitsno)) & 0x01), modH);
        u8bitsno ++;

        if (u8bitsno > 7)
        {
            u8bitsno = 0;
            u8frameByte++;
        }
    }

    // send outcoming message
    // it's just a copy of the incomping frame until 6th byte
    modH->u8BufferSize         = 6;
    u8CopyBufferSize = modH->u8BufferSize +2;

    return u8CopyBufferSize;
}





