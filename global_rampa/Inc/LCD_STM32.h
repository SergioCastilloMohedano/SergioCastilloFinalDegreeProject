/*
* LCD_STM32.h
*
*      fuente: https://github.com/geekfactory/LCD/blob/master/LCD-PIC16.h
*      		http://www.geekfactory.mx/tutoriales/tutoriales-pic/pantalla-lcd-16x2-con-pic-libreria/
*
*   Created on: Aug 16, 2016
*       Author: scastillom
******************************************************************************
*/

#ifndef LCD_STM32_H_
#define LCD_STM32_H_

/* Includes ------------------------------------------------------------------*/
#include "mxconstants.h"
#include "stm32f4xx_hal.h"

uint8_t lcd_ioinit(void * iodata);

void lcd_ioset(enum enLCDControlPins pin, GPIO_PinState state);

void lcd_iowrite8(uint8_t data);

#endif /* LCD_STM32_H_ */
