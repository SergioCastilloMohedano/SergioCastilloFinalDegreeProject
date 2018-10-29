/*
* LCD_STM32.c
*
*      fuente: https://github.com/geekfactory/LCD/blob/master/LCD-PIC16.c
*      		http://www.geekfactory.mx/tutoriales/tutoriales-pic/pantalla-lcd-16x2-con-pic-libreria/
*
*   Created on: Aug 16, 2016
*       Author: scastillom
******************************************************************************
*/

#include "LCD.h"
#include "LCD_STM32.h"


uint8_t lcd_ioinit(void * iodata)
{
	uint8_t i = 0;
	// Set all the pins to "low" state
	for (i = 0; i < 11; i++)
	{
		lcd_ioset(i, GPIO_PIN_RESET);
	}
	// Return bus lenght
	return 8;
}

void lcd_ioset(enum enLCDControlPins pin, GPIO_PinState state)
{
	switch (pin) {
	case E_D0_PIN:
		HAL_GPIO_WritePin(D0_GPIO_Port, D0_Pin, state);
		break;
	case E_D1_PIN:
		HAL_GPIO_WritePin(D1_GPIO_Port, D1_Pin, state);
		break;
	case E_D2_PIN:
		HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, state);
		break;
	case E_D3_PIN:
		HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, state);
		break;
	case E_D4_PIN:
		HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, state);
		break;
	case E_D5_PIN:
		HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, state);
		break;
	case E_D6_PIN:
		HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, state);
		break;
	case E_D7_PIN:
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, state);
		break;
	case E_RS_PIN:
		HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, state);
		break;
	case E_EN_PIN:
		HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, state);
		break;
	case E_RW_PIN:
		HAL_GPIO_WritePin(RW_GPIO_Port, RW_Pin, state);
		break;
	default:
		break;
	}
}

void lcd_iowrite8(uint8_t data)
{
	uint8_t i;

	for (i = 0; i < 8; i++)
	{
		uint8_t check = (( data & (1 << i)) >> i);
		if ( check == 1)
		{
			lcd_ioset(i, GPIO_PIN_SET);
		}
		else
		{
			lcd_ioset(i, GPIO_PIN_RESET);
		}
	}

	lcd_iohigh(E_EN_PIN);
	HAL_Delay(1);
	lcd_iolow(E_EN_PIN);
}
