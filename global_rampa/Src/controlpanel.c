/*
 * controlpanel.c
 *
 *  Created on: Aug 18, 2016
 *      Author: scast
 */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "controlpanel.h"

/* Extern Variables ----------------------------------------------------------*/
volatile uint8_t boton_Flag = 0;
volatile uint8_t debounce_Cnt = 0;


void init_PanelConfig(void)
{
  	// Initialize lcd driver
  	lcd_init(0, 16, 2);
	// Clear screen to end write to character generator
	lcd_clear();
	// Turn on display
	lcd_on();
	// Display message on the first row
	lcd_puts("Bienvenido!");
	// Move cursor to the fourth column on second line
	lcd_goto(0, 1);
	// Print a message there
	lcd_puts("Pulse OK o MOVER");

	while ((boton_Flag != 3) && (boton_Flag != 2));
	HAL_Delay(200);
	boton_Flag = 0;
	debounce_Cnt = 0;
}

uint8_t numeroJugadores(void)
{
	uint8_t players = 4;
	uint8_t refresh = 0;		//para evitar que el lcd se refresque continuamente.

	lcd_clear();
	lcd_goto(0,0);
	lcd_on();
	lcd_puts("Seleccione nume-");
	lcd_goto(0,1);
	lcd_puts("ro de jugadores.");

	HAL_Delay(3000);

	lcd_clear();
	lcd_goto(0,0);
	lcd_on();
	lcd_puts("Numero de");
	lcd_goto(0,1);
	lcd_puts("jugadores: 4");

	while (boton_Flag != 3)
	{
		if ((boton_Flag == 2))
		{
			HAL_Delay(200);
			boton_Flag = 0;
			debounce_Cnt = 0;
			refresh = 0;
			players++;
			if ( (players > 4) || (players < 1) ) {players = 1;}
			switch (players)
					{
					case 1:
						if (refresh == 0)
						{
							lcd_clear();
							lcd_goto(0,0);
							lcd_on();
							lcd_puts("Numero de");
							lcd_goto(0,1);
							lcd_puts("jugadores: 1");
						}
						refresh = 1;
						break;
					case 2:
						if (refresh == 0)
						{
							lcd_clear();
							lcd_goto(0,0);
							lcd_on();
							lcd_puts("Numero de");
							lcd_goto(0,1);
							lcd_puts("jugadores: 2");
						}
						refresh = 1;
						break;
					case 3:
						if (refresh == 0)
						{
							lcd_clear();
							lcd_goto(0,0);
							lcd_on();
							lcd_puts("Numero de");
							lcd_goto(0,1);
							lcd_puts("jugadores: 3");
						}
						refresh = 1;
						break;
					case 4:
						if (refresh == 0)
						{
							lcd_clear();
							lcd_goto(0,0);
							lcd_on();
							lcd_puts("Numero de");
							lcd_goto(0,1);
							lcd_puts("jugadores: 4");
						}
						refresh = 1;
						break;
					}
		}

	}
	return players;
}

uint8_t seleccionPersonaje(uint8_t jugador)
{
	HAL_Delay(200);
	boton_Flag = 0;
	debounce_Cnt = 0;
	uint8_t personajes [4][16] =
	                       {
							{"Caballo        \0"},
							{"Dinosaurio     \0"},
							{"Coche          \0"},
							{"Moto           \0"}
	                       };
	uint8_t charLCD[16] = "                ";
	uint8_t personaje = 0;
	uint8_t refresh = 0;

	if (jugador == 1)
	{
		lcd_clear();
		lcd_goto(0,0);
		lcd_on();
		lcd_puts("Seleccione ");
		lcd_goto(0,1);
		lcd_puts("personajes.");

		HAL_Delay(2000);
		boton_Flag = 0;
		debounce_Cnt = 0;
	}

	lcd_clear();
	lcd_on();
	lcd_goto(0,1);
	lcd_puts("Presione MOVER");
	lcd_goto(0,0);
	lcd_puts("Jugador  :");
	lcd_goto(8,0);
	lcd_send( (jugador + 48) , 1);

	while (boton_Flag !=2)
	{
		if (boton_Flag == 3)
		{
			HAL_Delay(200);
			boton_Flag = 0;
			debounce_Cnt = 0;
		}
	}

	while (boton_Flag != 3)
	{
		if ((boton_Flag == 2))
		{
			HAL_Delay(200);
			boton_Flag = 0;
			debounce_Cnt = 0;
			refresh = 0;

			personaje = checkPersonajes(personaje);
			strncpy(charLCD, personajes[personaje - 1], 16);

			if (refresh == 0)
			{
					lcd_clear();
					lcd_on();
					lcd_goto(0,1);
					lcd_puts(&charLCD);
					lcd_goto(0,0);
					lcd_puts("Jugador  :");
					lcd_goto(8,0);
					lcd_send( (jugador + 48) , 1);
			}
			refresh = 1;
		}
	}

	usedFlag |= (1 << (personaje-1));
	return personaje;
}

uint8_t checkPersonajes (uint8_t personaje)
{
	personaje++;

	if (usedFlag == 0x00)
	{
		if (personaje > 4)
		{
			personaje = 1;
		}
	}

	if (usedFlag == 0x01)
	{
		if (personaje > 4 || personaje == 1)
		{
			personaje = 2;
		}
	}

	if (usedFlag == 0x02)
	{
		if (personaje == 2)
		{
			personaje++;
		}

		if (personaje > 4)
		{
			personaje = 1;
		}
	}

	if (usedFlag == 0x03)
	{
		if (personaje > 4 || personaje == 1 || personaje == 2)
		{
			personaje = 3;
		}
	}

	if (usedFlag == 0x04)
	{
		if (personaje == 3)
		{
			personaje++;
		}
		else

		if (personaje > 4)
		{
			personaje = 1;
		}
	}

	if (usedFlag == 0x05)
	{
		if (personaje == 1 || personaje == 3)
		{
			personaje++;
		}

		if (personaje > 4)
		{
			personaje = 2;
		}
	}

	if (usedFlag == 0x06)
	{
		if (personaje == 2 || personaje == 3)
		{
			personaje = 4;
		}

		if (personaje > 4)
		{
			personaje = 1;
		}
	}

	if (usedFlag == 0x07)
	{
		personaje = 4;
	}

	if (usedFlag == 0x08)
	{
		if (personaje >= 4)
		{
			personaje = 1;
		}
	}

	if (usedFlag == 0x09)
	{
		if (personaje == 1 || personaje >= 4)
		{
			personaje = 2;
		}
	}

	if (usedFlag == 0x0A)
	{
		if (personaje == 2)
		{
			personaje++;
		}

		if (personaje >=4)
		{
			personaje = 1;
		}
	}

	if (usedFlag == 0x0B)
	{
		personaje = 3;
	}

	if (usedFlag == 0x0C)
	{
		if (personaje == 3 || personaje >= 4)
		{
			personaje = 1;
		}
	}

	if (usedFlag == 0x0D)
	{
		personaje = 2;
	}

	if (usedFlag == 0x0E)
	{
		personaje = 1;
	}

	return personaje;
}

void redButtonScreen (uint8_t jugador)
{
	HAL_Delay(200);
	boton_Flag = 0;
	debounce_Cnt = 0;
	uint8_t refresh = 0;

	while (boton_Flag != 4)
	{
		if (refresh == 0)
		{
			lcd_clear();
			lcd_on();
			lcd_goto(0,1);
			lcd_puts("Pulse BOTON ROJO");
			lcd_goto(0,0);
			lcd_puts("Jugador  :");
			lcd_goto(8,0);
			lcd_send( (jugador + 48) , 1);
		}
		refresh = 1;
	}

	refresh = 0;
	if (refresh == 0)
	{
		lcd_clear();
		lcd_on();
		lcd_goto(0,0);
		lcd_puts("BOLA CAYENDO,");
		lcd_goto(0,1);
		lcd_puts("BUENA SUERTE.");
	}

	HAL_Delay(200);
	refresh = 1;
	boton_Flag = 0;
	debounce_Cnt = 0;
}

void endScreen (uint8_t *puntuaciones)
{
	uint8_t i;
	uint8_t max = 0;
	uint8_t max1 = 0;
	uint8_t max2 = 0;
	uint8_t jugador = 0;

	for (i=0 ; i<4 ; i++)
	{
		if (puntuaciones[i] >= max)
		{
			max=puntuaciones[i];
			jugador = i+1;
		}
	}

	max1 = max % 10;
	max = max / 10;
	max2 = max % 10;

	HAL_Delay(2000);

	lcd_clear();
	lcd_on();
	lcd_goto(0,0);
	lcd_puts("JUGADOR   GANA");
	lcd_goto(0,1);
	lcd_puts("CON    PUNTOS!");
	lcd_goto(8,0);
	lcd_send( (jugador + 48) , 1);
	lcd_goto(5,1);
	lcd_send( (max1 + 48) , 1);
	lcd_goto(4,1);
	lcd_send( (max2 + 48) , 1);

	HAL_Delay(2000);

	lcd_clear();
	lcd_on();
	lcd_goto(0,0);
	lcd_puts("PULSE RESET PARA");
	lcd_goto(0,1);
	lcd_puts("NUEVA PARTIDA.");

}

void pointPlayersScreen ( uint8_t puntuacion, uint8_t jugador)
{
	uint8_t puntuacion1 = 0;
	uint8_t puntuacion2 = 0;

	puntuacion1 = puntuacion % 10;
	puntuacion = puntuacion / 10;
	puntuacion2 = puntuacion % 10;

	HAL_Delay(500);

	lcd_clear();
	lcd_on();
	lcd_goto(0,0);
	lcd_puts("JUGADOR   LOGRA");
	lcd_goto(0,1);
	lcd_puts("   PUNTOS!!");
	lcd_goto(8,0);
	lcd_send( (jugador + 48) , 1);
	lcd_goto(1,1);
	lcd_send( (puntuacion1 + 48) , 1);
	lcd_goto(0,1);
	lcd_send( (puntuacion2 + 48) , 1);

	HAL_Delay(2000);
}

void waitOkButton(void)
{
	debounce_Cnt = 0;
	boton_Flag = 0;
	while (boton_Flag != 3)
	{
	  if (boton_Flag == 2)
	  {
		  HAL_Delay(200);
		  boton_Flag = 0;
		  debounce_Cnt = 0;
	  }
	}

	  HAL_Delay(200);
	  boton_Flag = 0;
	  debounce_Cnt = 0;
}

