/*
 * steppermotors.c
 *
 *  Created on: Aug 23, 2016
 *      Author: scastillom
 */

#include "steppermotors.h"

 volatile uint16_t MA0_Flag = 0;
 volatile uint16_t MA1_Flag = 0;
 volatile uint16_t MA2_Flag = 0;
 volatile uint16_t MAAux_Flag = 0;

 /** @putChr
   * @brief  Activa el movimiento del motor del jugador correspondiente
   * 		un número de pasos equivalente a los grados que se desee.
   * @param  player: jugador actual, en función de este valor se mueve
   * 		uno de los cuatro motores.
   * @param	degrees: grados que se desea mover el motor.
   * @retval none
   */
void moveMotorDegrees (uint8_t player, uint16_t degrees)
{
	double steps = 0;
	uint16_t cycles = 0;
	uint16_t i = 0;
	uint8_t stop = 0;
	double oneLapSteps = 200;
	double oneLapDegrees = 360;


	steps = degrees * (oneLapSteps/oneLapDegrees);
	cycles = round(2 * steps);

	switch (player)
	{
	case 1:
		HAL_GPIO_WritePin(RESET_M1_GPIO_Port, RESET_M1_Pin, GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(RESET_M2_GPIO_Port, RESET_M2_Pin, GPIO_PIN_SET);
		break;
	case 3:
		HAL_GPIO_WritePin(RESET_M3_GPIO_Port, RESET_M3_Pin, GPIO_PIN_SET);
		break;
	case 4:
		HAL_GPIO_WritePin(RESET_M4_GPIO_Port, RESET_M4_Pin, GPIO_PIN_SET);
		break;
	}


	for (i = 0; i < cycles; i++)
		  {
			  HAL_Delay(5);
			  switch (player)
			  	{
			  	case 1:
					if (stop == 0)
					{
				  		HAL_GPIO_TogglePin(STEP_M1_GPIO_Port, STEP_M1_Pin);
					}
				  	if ((MA2_Flag == 1 && MA1_Flag == 1 && MA0_Flag == 1) || (MA2_Flag == 1 && MA1_Flag == 1 && MA0_Flag == 0))
				  	{
				  		stop = 1;
				  		HAL_GPIO_WritePin(STEP_M1_GPIO_Port, STEP_M1_Pin, GPIO_PIN_RESET);
				  	}
			  		break;
			  	case 2:
					if (stop == 0)
					{
						HAL_GPIO_TogglePin(STEP_M2_GPIO_Port, STEP_M2_Pin);
					}
					if ((MA2_Flag == 1 && MA1_Flag == 0 && MA0_Flag == 0) || (MA2_Flag == 1 && MA1_Flag == 0 && MA0_Flag == 1))
					{
						stop = 1;
						HAL_GPIO_WritePin(STEP_M2_GPIO_Port, STEP_M2_Pin, GPIO_PIN_RESET);
					}
					break;
			  	case 3:
					if (stop == 0)
					{
						HAL_GPIO_TogglePin(STEP_M3_GPIO_Port, STEP_M3_Pin);
					}
					if ((MA2_Flag == 0 && MA1_Flag == 1 && MA0_Flag == 0) || (MA2_Flag == 0 && MA1_Flag == 1 && MA0_Flag == 1))
					{
						stop = 1;
						HAL_GPIO_WritePin(STEP_M3_GPIO_Port, STEP_M3_Pin, GPIO_PIN_RESET);
					}
					break;
			  	case 4:
					if (stop == 0)
					{
						HAL_GPIO_TogglePin(STEP_M4_GPIO_Port, STEP_M4_Pin);
					}
					if ((MA2_Flag == 0 && MA1_Flag == 0 && MA0_Flag == 1) || (MAAux_Flag == 1))
					{
						stop = 1;
						HAL_GPIO_WritePin(STEP_M4_GPIO_Port, STEP_M4_Pin, GPIO_PIN_RESET);
					}
					break;
			  	}
		  }

	stop = 0;
	MAAux_Flag = 0;
	MA2_Flag = 0;
	MA1_Flag = 0;
	MA0_Flag = 0;

	HAL_Delay(200);
	switch (player)
	{
	case 1:
		HAL_GPIO_WritePin(RESET_M1_GPIO_Port, RESET_M1_Pin, GPIO_PIN_RESET);
		break;
	case 2:
		HAL_GPIO_WritePin(RESET_M2_GPIO_Port, RESET_M2_Pin, GPIO_PIN_RESET);
		break;
	case 3:
		HAL_GPIO_WritePin(RESET_M3_GPIO_Port, RESET_M3_Pin, GPIO_PIN_RESET);
		break;
	case 4:
		HAL_GPIO_WritePin(RESET_M4_GPIO_Port, RESET_M4_Pin, GPIO_PIN_RESET);
		break;
	}
}//moveMotorDegrees


/** @changeDir
  * @brief  Cambia la dirección del motor correspondiente al jugador
  * 		un número de pasos equivalente a los grados que se desee.
  * @param  player: jugador actual, en función de este valor se actúa
  * 		sobre uno de los motores..
  * @retval none
  */
void changeDir (uint8_t player)
{
	switch(player)
	{
	case 1:
		HAL_GPIO_TogglePin(DIR_M1_GPIO_Port, DIR_M1_Pin);
		break;
	case 2:
		HAL_GPIO_TogglePin(DIR_M2_GPIO_Port, DIR_M2_Pin);
		break;
	case 3:
		HAL_GPIO_TogglePin(DIR_M3_GPIO_Port, DIR_M3_Pin);
		break;
	case 4:
		HAL_GPIO_TogglePin(DIR_M4_GPIO_Port, DIR_M4_Pin);
		break;
	}
}//changeDir

/** @putChr
  * @brief  Activa el movimiento del motor del jugador correspondiente
  * 		un número de pasos equivalente a los centímetros que se desee.
  * @param  player: jugador actual, en función de este valor se mueve
  * 		uno de los cuatro motores.
  * @param	centimeters: centímetros que se desea mover el motor.
  * @retval none
  */
void moveMotorDistance (uint8_t player, double centimeters)
{
	double pi = 3.14159265;
	double radius = 2.5;		//en centimetros
	double perimeter;
	uint16_t degrees;
	perimeter = 2*pi*radius;	//en centimetros

	//360 degrees is equal to perimeter
	degrees = round((centimeters * 360) / perimeter);
	moveMotorDegrees (player, degrees);
}//moveMotorDegrees
