/*
* RF.h
*
*
*   Created on: Aug 9, 2016
*       Author: scastillom
******************************************************************************
*/

#ifndef RF_H_
#define RF_H_


/* Includes ------------------------------------------------------------------*/
#include "mxconstants.h"
#include "stm32f4xx_hal.h"

/* Defines ----------------**DECODER OUTPUT**---------------------------------*/
#define DEFAULT		0x00		//	-
#define PLAYER1		0x01		//	A
#define PLAYER2		0x02		//	B
#define PLAYER3		0x03		//	C
#define PLAYER4		0x04		//	D
#define CHARACTER1	0x05		//	E
#define CHARACTER2	0x06		//	F
#define CHARACTER3	0x07		//	G
#define CHARACTER4	0x08		//	H
#define POINTS10	0x09		//	I
#define POINTS15	0x0A		//	J
#define POINTS20	0x0B		//	K
#define	RESTART		0x0C		//	L
#define	ENDGAME		0x0D		//	M
#define INITPOS		0x0E		//	N
//		NOTUSED	0x0F			//	O

/* Global variables ----------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/* RF_Command
 */
void RF_Command (uint8_t RF_Command);

	/********** TABLA DE COMANDOS RF ************
	 *  					S3	S2	S1	S0		*
	 *  0x00	Default		0	0	0	0		*
	 *  0x01	Player1		0	0	0	1		*
	 *  0x02	Player2		0	0	1	0		*
	 *  0x03	Player3		0	0	1	1		*
	 *  0x04	Player4		0	1	0	0		*
	 *  0x05	Character1	0	1	0	1		*
	 *  0x06	Character2	0	1	1	0		*
	 *  0x07	Character3	0	1	1	1		*
	 *  0x08	Character4	1	0	0	0		*
	 *  0x09	Points10	1	0	0	1		*
	 *  0x0A	Points15	1	0	1	0		*
	 *  0x0B	Points20	1	0	1	1		*
	 *  0x0C	Restart		1	1	0	0		*
	 *  0x0D	EndGame		1	1	0	1		*
	 *  0x0E	InitialPos	1	1	1	0		*
	 *  0x0F	NotUsed		1	1	1	1		*
	 ********************************************/


#endif /* RF_H_ */
