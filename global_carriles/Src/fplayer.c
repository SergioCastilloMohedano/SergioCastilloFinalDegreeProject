/*
 * fplayer.c
 *
 *  Created on: Aug 28, 2016
 *      Author: scastillom
 */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "fplayer.h"

/** @putChr
  * @brief  Pone un 1 byte en la posición Index del buffer
  * @param  Word: Byte de información que se desea indexar en el buffer
  * @param	Indx: índice del buffer, cada byte se guarda en un espacio
  * 		del buffer distinto.
  * @param	Buff[]: Buffer.
  * @retval none
  */
void putChr(uint8_t Word, uint8_t Indx, uint8_t Buff[])
{
	Buff[Indx] = Word;
}//putChr

/** @buildCommand
  * @brief  Construye el dato que se va a enviar al FPlayer para que
  * 		este lo entienda correctamente
  * @param  Word: Byte de información que se desea indexar en el buffer.
  * @param	Buff[]: Buffer.
  * @retval none
  */
void buildCommand(uint8_t Word, uint16_t Param, uint8_t Buff[])
{
	uint16_t xorsum = 0;
	uint8_t i;

	putChr(STARTBYTE, 0, Buff);
	putChr(VERSIONBYTE, 1, Buff);
	putChr(LENGTHBYTE, 2, Buff);
	putChr(Word, 3, Buff);
	putChr(FEEDBACKBYTE, 4, Buff);
	putChr((uint8_t)(Param >> 8), 5, Buff);
	putChr((uint8_t)(Param & 0x00ff), 6, Buff);

	for(i=1;i<7;i++)						//CHECKSUM = 0 -(VERSIONBYTE + LENGTHBYTE + COMMAND
	{										// + FDBCK + PARAM_MSB + PARAM_LSB) =0xHHhh
		xorsum = xorsum + Buff[i];
	}
	xorsum = 0 - xorsum;

	putChr((uint8_t)(xorsum >> 8), 7, Buff);
	putChr((uint8_t)(xorsum & 0x00ff), 8, Buff);
	putChr(ENDBYTE, 9, Buff);
}//buildCommand
