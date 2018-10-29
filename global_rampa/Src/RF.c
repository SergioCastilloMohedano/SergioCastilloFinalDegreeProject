/*
* RF.c
*
*
*   Created on: Aug 9, 2016
*       Author: scastillom
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "RF.h"


/** @RF_Command
  * @brief  Función que separa bit a bit el comando que se desea mandar
  * 		y se asigna a su output correspondiente.
  * @param  RF_Command: Byte que se desea mandar a través de RF
  * @retval none
  */
void RF_Command (uint8_t RF_Command)
{
	int i;
	uint8_t singleBit = 0;
	for(i = 3; 0 <= i; i --)	//extrae los 4 bits menos significativos del Byte
	{
		singleBit = (RF_Command >> i) & 0x01;
		switch (i)
		{
		case 3:		//lectura bit mas significativo
			if (singleBit == 0)
			{
				HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(S3_GPIO_Port, S3_Pin, GPIO_PIN_SET);
			}
			break;
		case 2:		//lectura segundo bit mas significativo
			if (singleBit == 0)
			{
				HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(S2_GPIO_Port, S2_Pin, GPIO_PIN_SET);
			}
			break;
		case 1:		//lectura segundo bit menos significativo
			if (singleBit == 0)
			{
				HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(S1_GPIO_Port, S1_Pin, GPIO_PIN_SET);
			}
			break;
		case 0:		//lectura bit menos significativo
			if (singleBit == 0)
			{
				HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, GPIO_PIN_RESET);
			}
			else
			{
				HAL_GPIO_WritePin(S0_GPIO_Port, S0_Pin, GPIO_PIN_SET);
			}
			break;
		default:
			break;
		}
	}
}//RF_Command
