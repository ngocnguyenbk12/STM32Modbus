/**
 * @file Crc.c
 * @author Ngoc Nguyen - ngocnguyenbk12@gmail.com
 * @brief 
 * @version 0.1
 * @date 2023-02-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "Crc.h"

/**
 * 
 * @brief
 * This method calculates CRC
 *
 * @return uint16_t calculated CRC value for the message
 * @ingroup Buffer
 * @ingroup u8length
 */
uint16_t calcCRC(uint8_t *Buffer, uint8_t u8length)
{
    unsigned int temp, temp2, flag;
    temp = 0xFFFF;
    for (unsigned char i = 0; i < u8length; i++)
    {
        temp = temp ^ Buffer[i];
        for (unsigned char j = 1; j <= 8; j++)
        {
            flag = temp & 0x0001;
            temp >>=1;
            if (flag)
                temp ^= 0xA001;
        }
    }
    // Reverse byte order.
    temp2 = temp >> 8;
    temp = (temp << 8) | temp2;
    temp &= 0xFFFF;
    return temp;

}

/**
 * @brief 
 * 
 * @param buf 
 * @param len 
 * @param IsFirstCall 
 * @return uint32_t 
 */
uint32_t Crc32_Calc(uint8_t *buf, uint32_t len, uint32_t IsFirstCall)
{
  uint32_t crc = IsFirstCall;
  while (len--)
    {
      crc = (crc << 8) ^ Crc32_Table[((crc >> 24) ^ *buf) & 255];
      buf++;
    }
  return crc;
}
