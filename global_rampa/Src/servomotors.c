/*
* servomotors.c
*
*
*   Created on: Aug 9, 2016
*       Author: scastillom
******************************************************************************
*/


#include "servomotors.h"

/** @moveServomotor
  * @brief  mueve el servomotor que se quiera un número determinado
  * 		de grados entre 0 y 180.
  * @param  servoMotor: el servo que se quiere mover, hay hasta 6.
  * @param	degrees: número de grados que se desea mover el servo.
  * @retval none
  */
void moveServomotor(uint8_t servoMotor, double degrees)
{//y=mx+n		->	n=2650, m=-((1700-750)/(210-105))=-9.05, y=ccrx, x= degrees
	uint32_t CCRX = 0;
	double m = -9.05;
	double n = 2650;

	CCRX = round((m*degrees) + n);

	if (CCRX > 2650)
	{
		CCRX = 2650;
	}

	if (CCRX < 750)
	{
		CCRX = 750;
	}

	switch(servoMotor)
	{
	case 1:
		TIM3->CCR1=CCRX;
		break;
	case 2:
		TIM3->CCR2=CCRX;
		break;
	case 3:
		TIM3->CCR3=CCRX;
		break;
	case 4:
		TIM4->CCR1=CCRX;
		break;
	case 5:
		TIM4->CCR2=CCRX;
		break;
	case 6:
		TIM4->CCR3=CCRX;
		break;
	}
}//moveServomotor

/** @startServomotors
  * @brief  inicializa todos los servos y la interrupción del tim3 por "update".
  * @param  none
  * @retval none
  */
void startServomotors (void)
{

	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);

	HAL_TIM_Base_Start_IT(&htim3);
}//startServomotors

/** @stopServomotors
  * @brief  Envía servomotores a posición inicial y los para.
  * @param  none
  * @retval none
  */
void stopServomotors (void)
{
	uint32_t CCRX = 2650;

	TIM3->CCR1=CCRX;
	TIM3->CCR2=CCRX;
	TIM3->CCR3=CCRX;
	TIM4->CCR1=CCRX;
	TIM4->CCR2=CCRX;
	TIM4->CCR3=CCRX;

	HAL_TIM_Base_Stop_IT(&htim3);

	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
}//stopServomotors


/** @moveServosRamp
  * @brief  Mueve lo servomotores de la rampa a una posición aleatoria
  * 		entre 0 y 180 grados.
  * @param  none
  * @retval none
  */
void moveServosRamp (void)
{
	uint8_t random = 0;

	do {
		random = rand();
	} while (random > 180);

	moveServomotor(1, random);

	do {
		random = rand();
	} while (random > 180);

	moveServomotor(2, random);

	do {
		random = rand();
	} while (random > 180);

	moveServomotor(3, random);

	do {
		random = rand();
	} while (random > 180);

	moveServomotor(4, random);
}
