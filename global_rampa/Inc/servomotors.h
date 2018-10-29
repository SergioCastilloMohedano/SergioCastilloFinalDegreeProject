/*
* servomotors.h
*
*
*   Created on: Aug 9, 2016
*       Author: scastillom
******************************************************************************
*/

#ifndef SERVOMOTORS_H_
#define SERVOMOTORS_H_


#include "stm32f4xx_hal.h"
#include <math.h>
#include <stdlib.h>

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/* moveServomotor
 */
void moveServomotor(uint8_t servoMotor, double degrees);

/* startServomotors
 */
void startServomotors (void);

/* stopServomotors
 */
void stopServomotors (void);

/* moveServosRamp
 */
void moveServosRamp (void);

#endif /* SERVOMOTORS_H_ */
