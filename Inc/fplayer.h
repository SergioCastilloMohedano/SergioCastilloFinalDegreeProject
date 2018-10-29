/*
 * fplayer.h
 *
 *  Created on: Aug 28, 2016
 *      Author: scastillom
 */

#ifndef FPLAYER_H_
#define FPLAYER_H_

					/************************************************
					 * ASYNCHRONOUS SERIAL COMMUNICATION FEATURES	*
					 * 			for FPlayer Mini Device				*
					 * -------------------------------------------- *
					 *												*
					 * 			9600 bauds per second				*
					 * 			Data Bits: 8						*
					 * 			Parity: none						*
					 * 			Stop Bits: 1						*
					 * 			Checkout: none						*
					 * 			Flow Control: none					*
					 ************************************************/

/************************************************************************************************
 * 								FORMAT: 10Bytes Word Data Lenght								*
 * 						$S VER Len CMD Feedback para1 para2 checksum $O							*
 * ___________________________________________________________________________________________	*
 *	$S			Start byte 0x7E				Each command feedback begins with $, which is 0x7E	*
 *	------------------------------------------------------------------------------------------	*
 *	VER			Version						Version Information(default 0xFF)					*
 *	------------------------------------------------------------------------------------------	*
 *	Length		Number of bytes from		Checksum not counted								*
 *				COMMAND through to																*
 *				Check_LSB (typically 0x06)														*
 *	------------------------------------------------------------------------------------------	*
 *	CMD 		Command byte				Means the specific operations, 						*
 *											such as play / pause, etc.							*
 *	------------------------------------------------------------------------------------------	*
 *	Feedback	Command feedback			0x01: Feedback-send confirmation back to MCU;		*
 *											0x00: No feedback									*
 *	------------------------------------------------------------------------------------------	*
 *	Param_MSB	Parameter					Most significant byte of parameter					*
 *	------------------------------------------------------------------------------------------	*
 *	Param_LSB	Parameter					Least significant byte of parameter					*
 *	------------------------------------------------------------------------------------------	*
 *	Check_MSB	Checksum					Most significant byte of checksum					*
 *	------------------------------------------------------------------------------------------	*
 *	Check_LSB	Checksum					Least significant byte of checksum					*
 *	------------------------------------------------------------------------------------------	*
 *	$O 			End byte					0xEF												*
 ************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Defines -------------------------------------------------------------------*/
#define LENGTH					10		//Data length to be sent.

#define STARTBYTE 				0x7E	//StartByte, '$S' by default.
#define VERSIONBYTE				0xFF	//Version Information.
#define LENGTHBYTE				0x06	//Number of bytes from CMD to Check_LSB,
#define FEEDBACKBYTE			0x00	//0x00 when transmitting.
#define ENDBYTE					0xEF	//End Byte, '$O' by default.

/****************
 *   Commands   *
 ****************/

#define PLAYNEXT_CMD 			0x01	//Play next track
#define PLAYPREV_CMD 			0x02	//Play previous track
#define PLAYSONG_CMD			0x03 	//Specify playback of a track 1-3000
#define TURNUPVOL_CMD 			0x04	//Turn Up Volume
#define TURNDWNVOL_CMD 			0x05	//Turn Down Volume
#define SETVOL_CMD				0x06	//Specify volume Volume level:0-30
#define SETEQ_CMD				0x07 	//Specify EQ(0/1/2/3/4/5) 0:Normal/1:Pop/2:Rock/3:Jazz/4:Classic/5:Bass
#define SINGLRPT_CMD			0x08 	//Specify single repeat playback Tracks 0001-3000
#define PLAYDEVICE_CMD			0x09 	//Specify playback of a device(0/1) 0:USB/1:SD // Specify playback source(0/1/2/3/4): U/TF/AUX/SLEEP/FLASH
#define SETSLEEP_CMD			0x0A 	//Set Sleep
//#define NA_CMD				0x0B 	//N/A(Reserved Normal working)
#define RESET_CMD				0x0C 	//Reset
#define PLAY_CMD				0x0D 	//Play
#define PAUSE_CMD				0x0E 	//Pause
#define PLAYSNGFLDR_CMD			0x0F 	//Specify playback a track in a folder Folders 01-99
#define SETAMP_CMD				0x10 	//Audio amplification setting MSB=1:amplifying on, LSB:set gain 0-31
#define REPEATALL_CMD			0x11 	//Set all repeat playback 1:start all repeat playback; 0:stop playback
#define PLAYMP3SONG_CMD			0x12 	//Specify playback of folder named "MP3"
#define ADVERTCUT_CMD			0x13 	//Inter cut an advertisement
#define PLYTRCKFLDR_CMD			0x14 	//Specify playback a track in a folder that supports 3000 tracks Supports 15 folders only(01-15)
#define STOPADVERT_CMD			0x15 	//Stop playing inter-cut advertisement and go back to play the music interrupted
#define STOP_CMD				0x16 	//Stop
#define REPEATFLDR_CMD			0x17 	//Specify repeat playback of a folder
#define RNDMPLAY				0x18 	//Set random playback
#define REPEAT_CMD				0x19 	//Set repeat playback of current track
#define SETDAC_CMD				0x1A 	//Set DAC

/*********************
 *   Query Commands  *
 *********************/

//#define NA_CMD				0x3C 	//N/A(Reserved)
//#define NA_CMD				0x3D 	//N/A(Reserved)
//#define NA_CMD				0x3E 	//N/A(Reserved)
#define QRYDEVIDE_CMD			0x3F 	//Query current online storage device
#define QRYERROR_CMD			0x40 	//Module returns an error data with this command
#define QRYFDBCKDBG_CMD			0x41 	//Module reports a feedback with this command // "debug mode"
#define QRYSTATUS_CMD			0x42 	//Query current status
#define QRYVOL_CMD				0x43 	//Query current volume
#define QRYEQ_CMD				0x44 	//Query current EQ
#define QRYPLAYBACK_CMD			0x45 	//Query the current playback mode
#define QRYVERSION_CMD			0x46 	//Query the current software version
#define QRYQTYUSB_CMD			0x47 	//Query total file numbers of USB flash disk
#define QRYQTYSD_CMD			0x48 	//Query total file numbers of micro SD Card
#define QRYQTYFLSH_CMD			0x49 	//Query the total number of flash files
//#define NA_CMD				0x4A 	//N/A(Reserved)
#define QRYTRCKUSB_CMD			0x4B 	//Query current track of USB flash disk
#define QRYTRCKSD_CMD			0x4C 	//Query current track of micro SD Card
#define QRYTRCKFLSH_CMD			0x4D 	//Queries the current track of Flash
#define QRYFILESINFOLDER_CMD	0x4E 	//Query total file numbers of a folder
#define QRYFOLDERLNMBR_CMD		0x4F 	//Query total folder numbers of the storage device


/* Function Prototypes -------------------------------------------------------*/

/* putChr
 */
void putChr (uint8_t Word, uint8_t Indx, uint8_t Buff[]);

/* buildCommand
 */
void buildCommand (uint8_t Word, uint16_t Param, uint8_t Buff[]);


/*****************************************************
 *   EXAMPLES Examples of Sending Serial Commands	 *
 *****************************************************/

//El dispositivo DFPlayer tiene varias formas de funcionamiento, puede
//acceder a datos almacenados a un dispositivo USB o a una SD, y también puede
//reproducir una canción en una carpeta específica o seleccionar una canción
//directamente del directorio raíz del USB o tarjeta uSD.
//
//En función de cómo se quiera emplear el dispositivo habrá que mandar unos comandos u otros.
//Particularmente para nuestro proyecto, se utilizará una uSD y será suficiente con
//guardar las canciones en el directorio raíz sin la necesidad de crear subcarpetas
//y acceder directamente a ellas. Por ello, muchos de los comando que hay arriba no
//se van a utilizar, pero se dejan puestos por si en un futuro se quisiera utilizar
//el DFPlayer para otra aplicación.

 /* Commands Description Serial Commands
[with checksum]						[without checksum] 			Notes

Play Next
7E FF 06 01 00 00 00 FE FA EF 		7E FF 06 01 00 00 00 EF

Play Previous
7E FF 06 02 00 00 00 FE F9 EF 		7E FF 06 02 00 00 00 EF

Specify playback of a track under the root directory
7E FF 06 03 00 00 01 FE F7 EF 		7E FF 06 03 00 00 01 EF 	Specify playback of the 1st track
7E FF 06 03 00 00 02 FE F6 EF 		7E FF 06 03 00 00 02 EF 	Specify playback of the 2nd track
7E FF 06 03 00 00 0A FE EE EF 		7E FF 06 03 00 00 0A EF 	Specify playback of the 10th track

Specify volume
7E FF 06 06 00 00 1E FE D7 EF 		7E FF 06 06 00 00 1E EF 	Specified volume is level 30

Specify EQ
7E FF 06 07 00 00 01 FE F3 EF 		7E FF 06 07 00 00 01 EF 	Specified EQ mode is POP

Specify single repeat playback
7E FF 06 08 00 00 01 FE F2 EF 		7E FF 06 08 00 00 01 EF 	Repeatedly play the 1st track
7E FF 06 08 00 00 02 FE F1 EF 		7E FF 06 08 00 00 02 EF 	Repeatedly play the 2nd track
7E FF 06 08 00 00 0A FE E9 EF 		7E FF 06 08 00 00 0A EF 	Repeatedly play the 10th track

Specify playback of a device
7E FF 06 09 00 00 01 FE F1 EF 		7E FF 06 09 00 00 01 EF 	Specified device is USB flash disk
7E FF 06 09 00 00 02 FE F0 EF 		7E FF 06 09 00 00 02 EF 	Specified device is micro SD

Set sleep mode
7E FF 06 0A 00 00 00 FE F1 EF 		7E FF 06 0A 00 00 00 EF

Reset
7E FF 06 0C 00 00 00 FE EF EF 		7E FF 06 0C 00 00 00 EF

Play
7E FF 06 0D 00 00 00 FE EE EF 		7E FF 06 0D 00 00 00 EF

Pause
7E FF 06 0E 00 00 00 FE ED EF 		7E FF 06 0E 00 00 00 EF

Specify playback of a folder
7E FF 06 0F 00 01 01 FE EA EF 		7E FF 06 0F 00 01 01 EF 	Specify track "001" in the folder 01
7E FF 06 0F 00 01 02 FE E9 EF 		7E FF 06 0F 00 01 02 EF 	Specify track "002" in the folder 01

Set all repeat playback
7E FF 06 11 00 00 01 FE E9 EF 		7E FF 06 11 00 00 01 EF

Specify playback of folder named MP3
7E FF 06 12 00 00 01 FE E8 EF 		7E FF 06 12 00 00 01 EF 	Play track "0001" in the folder MP3
7E FF 06 12 00 00 02 FE E7 EF 		7E FF 06 12 00 00 02 EF 	Play track "0002" in the folder MP3
7E FF 06 12 00 00 FF FD EA EF 		7E FF 06 12 00 00 FF EF 	Play track "0255" in the folder MP3
7E FF 06 12 00 07 CF FE 13 EF 		7E FF 06 12 00 07 CF EF 	Play track "1999" in the folder MP3
7E FF 06 12 00 0B B8 FE 26 EF 		7E FF 06 12 00 0B B8 EF 	Play track "3000" in the folder MP3

Inter cut an advertisement
7E FF 06 13 00 00 01 FE E7 EF 		7E FF 06 13 00 00 01 EF 	Inter cut track "0001"in the folder ADVERT
7E FF 06 13 00 00 02 FE E6 EF 		7E FF 06 13 00 00 02 EF 	Inter cut track "0002"in the folder ADVERT
7E FF 06 13 00 00 FF FD E9 EF 		7E FF 06 13 00 00 FF EF 	Inter cut track "0255"in the folder ADVERT

Specify playback of a track in a folder that supports 3000 tracks
7E FF 06 14 00 10 FF FD D8 EF 		7E FF 06 14 00 10 FF EF 	Play track "0255" in the specified folder 01
7E FF 06 14 00 17 CF FE 01 EF 		7E FF 06 14 00 17 CF EF 	Play track "1999" in the specified folder 01
7E FF 06 14 00 C0 01 FE 26 EF 		7E FF 06 14 00 C0 01 EF 	Play track "0001" in the specified folder 12
7E FF 06 14 00 C0 FF FD 28 EF 		7E FF 06 14 00 C0 FF EF 	Play track "0255" in the specified folder 12
7E FF 06 14 00 C7 CF FD 51 EF 		7E FF 06 14 00 C7 CF EF 	Play track "1999" in the specified folder 12

Stop playing inter-cut ad
7E FF 06 15 00 00 00 FE E6 EF Go back and continue to play themusic interrupted

Stop playback
7E FF 06 16 00 00 00 FE E5 EF 		Stop software decoding

Specify repeat playback of a folder
7E FF 06 17 00 00 02 FE E2 EF 		7E FF 06 17 00 00 02 EF Specify repeat playback of the folder 02
7E FF 06 17 00 00 01 FE E3 EF 		7E FF 06 17 00 00 01 EF Specify repeat playback of the folder 01

Set random playback
7E FF 06 18 00 00 00 FE E3 EF 		7E FF 06 18 00 00 00 EF

Set single repeat playback
7E FF 06 19 00 00 00 FE E2 EF 		7E FF 06 19 00 00 00 EF Turn on single repeat playback
7E FF 06 19 00 00 01 FE E1 EF 		7E FF 06 19 00 00 01 EF Turn off single repeat playback

Set DAC
7E FF 06 1A 00 00 00 FE E1 EF 		7E FF 06 1A 00 00 00 EF Turn on DAC
7E FF 06 1A 00 00 01 FE E0 EF 		7E FF 06 1A 00 00 01 EF Turn off DAC

Query current status
7E FF 06 42 00 00 00 FE B9 EF 		7E FF 06 42 00 00 00 EF

Query current volume
7E FF 06 43 00 00 00 FE B8 EF 		7E FF 06 43 00 00 00 EF

Query current EQ
7E FF 06 44 00 00 00 FE B7 EF 		7E FF 06 44 00 00 00 EF

Query total file numbers of USB flash disk
7E FF 06 47 00 00 00 FE B4 EF 		7E FF 06 47 00 00 00 EF Total file numbers of current device

Query total file numbers of micro SD card
7E FF 06 48 00 00 00 FE B3 EF 		7E FF 06 48 00 00 00 EF Total file numbers of current device

Query current track of USB flash disk
7E FF 06 4B 00 00 00 FE B0 EF 		7E FF 06 4B 00 00 00 EF Query the track being played

Query current track of micro SD card
7E FF 06 4C 00 00 00 FE AF EF 		7E FF 06 4C 00 00 00 EF Query the track being played

Query total file numbers of a folder
7E FF 06 4E 00 00 01 FE AC EF 		7E FF 06 4E 00 00 01 EF Query the total file numbers of the folder 01.
7E FF 06 4E 00 00 0B FE A2 EF 		7E FF 06 4E 00 00 0B EF Query the total file numbers of the folder 11.
*/


#endif /* FPLAYER_H_ */
