/*
 * controlpanel.h
 *
 *  Created on: Aug 18, 2016
 *      Author: scast
 */

#ifndef CONTROLPANEL_H_
#define CONTROLPANEL_H_

/* Includes ------------------------------------------------------------------*/
#include "mxconstants.h"
#include "stm32f4xx_hal.h"
#include "LCD.h"

/* Global Variables ----------------------------------------------------------*/
volatile uint8_t usedFlag;

/* Function Prototypes -------------------------------------------------------*/
void init_PanelConfig(void);
uint8_t numeroJugadores(void);
uint8_t seleccionPersonaje(uint8_t jugador);
uint8_t checkPersonajes(uint8_t personaje);
void redButtonScreen (uint8_t jugador);
void endScreen (uint8_t *puntuaciones);
void pointPlayersScreen ( uint8_t puntuacion, uint8_t jugador);
void waitOkButton(void);

#endif /* CONTROLPANEL_H_ */
