/*
 * steppermotors.h
 *
 *  Created on: Aug 23, 2016
 *      Author: scast
 */

#ifndef STEPPERMOTORS_H_
#define STEPPERMOTORS_H_

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include "stm32f4xx_hal.h"
#include <stdio.h>



/* Function Prototypes -------------------------------------------------------*/

/* moveMotorDegrees
 */
void moveMotorDegrees (uint8_t player, uint16_t degrees);

/* changeDir
 */
void changeDir (uint8_t player);

/* moveMotorDistance
 */
void moveMotorDistance (uint8_t player, double centimeters);


#endif /* STEPPERMOTORS_H_ */
