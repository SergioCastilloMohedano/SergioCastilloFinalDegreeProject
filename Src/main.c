/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  *   Created on: Aug 28, 2016
  *       Author: scastillom
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include "stm32f4xx_hal.h"
#include "steppermotors.h"
#include "fplayer.h"

#define MAXPOINTS 70
volatile uint16_t RxDataRF_Cnt;


/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart6;

uint8_t FPlayer_Buffer[LENGTH];
uint8_t RF_Buffer[LENGTH];
uint8_t character = '\0';
uint8_t nplayers = 0;
uint8_t players[4][16] =	{
							{"               \0"},
							{"               \0"},
							{"               \0"},
							{"               \0"}
					   };
uint8_t i;
uint8_t j;
uint8_t characters[4][16] = {
							{"Personaje 1    \0"},
							{"Personaje 2    \0"},
							{"Personaje 3    \0"},
							{"Personaje 4    \0"}
						};
uint8_t player_Cnt = 0;
uint8_t pointPlayers[4] = {0,0,0,0};
int16_t max = -10;
uint8_t flag_Ended = 0;
uint8_t musicOn = 0;
uint8_t done = 0;


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART6_UART_Init(void);

/* sendMotorsToStart
 */
void sendMotorsToStart();

/* deInitVariables
 */
void deInitVariables();

int main(void)
{
  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART6_UART_Init();

  while (1)
  {
	  HAL_UART_Receive_IT(&huart6, RF_Buffer, LENGTH);

	  if (musicOn == 1)
	  {
		  buildCommand(PLAYMP3SONG_CMD, 17, FPlayer_Buffer);
		  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
		  musicOn = 0;
	  }

	  if (musicOn == 2)
	  {
		  buildCommand(STOP_CMD, 0, FPlayer_Buffer);
		  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
		  musicOn = 0;
	  }

	  if (RxDataRF_Cnt == LENGTH)
	  {
		  RxDataRF_Cnt = 0;
		  character = RF_Buffer[7];

		  //A = 1 jugador,
		  //B = 2 jugadores,
		  //C = 3 jugadores,
		  //D = 4 jugadores
		  if (character == 'A' || character == 'B' || character == 'C' || character == 'D')
		  {
			  switch (character)
			  {
			  case 'A':
				  nplayers = 1;
				  buildCommand(PLAYMP3SONG_CMD, 01, FPlayer_Buffer);
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  break;
			  case 'B':
				  nplayers = 2;
				  buildCommand(PLAYMP3SONG_CMD, 02, FPlayer_Buffer);
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  break;
			  case 'C':
				  nplayers = 3;
				  buildCommand(PLAYMP3SONG_CMD, 03, FPlayer_Buffer);
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  break;
			  case 'D':
				  nplayers = 4;
				  buildCommand(PLAYMP3SONG_CMD, 04, FPlayer_Buffer);
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  break;
			  }
		  }

		  //E = Personaje 1 (caballo),
		  //F = Personaje 2 (dinosaurio),
		  //G = Personaje 3 (coche),
		  //H = Personaje 4 (moto)
		  if (character == 'E' || character == 'F' || character == 'G' || character == 'H')
		  {
			  switch (character)
			  {
			  case 'E':
				  strncpy(players[player_Cnt], characters[0], 16);
				  buildCommand(PLAYMP3SONG_CMD, 5, FPlayer_Buffer);
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  break;
			  case 'F':
				  strncpy(players[player_Cnt], characters[1], 16);
				  buildCommand(PLAYMP3SONG_CMD, 6, FPlayer_Buffer);
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  break;
			  case 'G':
				  strncpy(players[player_Cnt], characters[2], 16);
				  buildCommand(PLAYMP3SONG_CMD, 7, FPlayer_Buffer);
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  break;
			  case 'H':
				  strncpy(players[player_Cnt], characters[3], 16);
				  buildCommand(PLAYMP3SONG_CMD, 8, FPlayer_Buffer);
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  break;
			  }
			  player_Cnt++;
			  if (player_Cnt == nplayers)
			  {
				  musicOn = 1;
				  player_Cnt = 0;
				  HAL_Delay(3000);
			  }
		  }

		  //I = 10 puntos,
		  //J = 15 puntos,
		  //K = 20 puntos
		  if(character == 'I' || character == 'J' || character == 'K')
		  {
			  player_Cnt++;

			  if (players[player_Cnt - 1][10] == '1')
			  {
				  buildCommand(PLAYMP3SONG_CMD, 9, FPlayer_Buffer);
			  }

			  if (players[player_Cnt - 1][10] == '2')
			  {
				  buildCommand(PLAYMP3SONG_CMD, 10, FPlayer_Buffer);
			  }

			  if (players[player_Cnt - 1][10] == '3')
			  {
				  buildCommand(PLAYMP3SONG_CMD, 11, FPlayer_Buffer);
			  }

			  if (players[player_Cnt - 1][10] == '4')
			  {
				  buildCommand(PLAYMP3SONG_CMD, 12, FPlayer_Buffer);
			  }

			  switch (character)
			  {
			  case 'I':
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  moveMotorDistance(player_Cnt, 10);
				  pointPlayers[player_Cnt-1] = pointPlayers[player_Cnt-1] + 10;
				  HAL_Delay(4000);
				  buildCommand(PLAYMP3SONG_CMD, 18, FPlayer_Buffer);
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  HAL_Delay(4000);
				  break;

			  case 'J':
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  moveMotorDistance(player_Cnt, 15);
				  pointPlayers[player_Cnt-1] = pointPlayers[player_Cnt-1] + 15;
				  HAL_Delay(4000);
				  buildCommand(PLAYMP3SONG_CMD, 19, FPlayer_Buffer);
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  HAL_Delay(4000);
				  break;

			  case 'K':
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  moveMotorDistance(player_Cnt, 20);
				  pointPlayers[player_Cnt-1] = pointPlayers[player_Cnt-1] + 20;
				  HAL_Delay(4000);
				  buildCommand(PLAYMP3SONG_CMD, 20, FPlayer_Buffer);
				  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
				  HAL_Delay(4000);
				  break;
			  }

			  if (player_Cnt >= nplayers)
			  {
				  player_Cnt = 0;
			  }

			  musicOn = 1;
		  }

		  //L = reset variables. Se reinicia el juego.
		  if(character == 'L')
		  {
			  if (done == 0)
			  {
				  sendMotorsToStart();
				  done = 1;
			  }
			  deInitVariables();
			  musicOn = 2;
		  }

		  //M = Fin del juego, puntuación máxima alcanzada por uno de los jugadores.
		  if(character == 'M')
		  {
			  flag_Ended = 1;
			  for (i=0 ; i<nplayers ; i++)
			  {
				  if (pointPlayers[i] >= max)
				  {
					  max = pointPlayers[i];
				  }
			  }
		  }
	  }

	  // chequea qué jugador consiguió mayor puntuación
	  // y manda a posición inicial los motores.
	  if (flag_Ended == 1)
	  {
		  if (max == pointPlayers[3])
		  {
			  buildCommand(PLAYMP3SONG_CMD, 16, FPlayer_Buffer);
			  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
		  }
		  else if (max == pointPlayers[2])
		  {
			  buildCommand(PLAYMP3SONG_CMD, 15, FPlayer_Buffer);
			  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
		  }
		  else if (max == pointPlayers[1])
		  {
			  buildCommand(PLAYMP3SONG_CMD, 14, FPlayer_Buffer);
			  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
		  }
		  else if (max == pointPlayers[0])
		  {
			  buildCommand(PLAYMP3SONG_CMD, 13, FPlayer_Buffer);
			  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
		  }

		  HAL_Delay(3000);
		  buildCommand(PLAYMP3SONG_CMD, 21, FPlayer_Buffer);
		  HAL_UART_Transmit_IT(&huart1, FPlayer_Buffer, LENGTH);
		  sendMotorsToStart();
		  done = 1;
		  flag_Ended = 0;
	  }
  }

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}

/* USART6 init function */
static void MX_USART6_UART_Init(void)
{

  huart6.Instance = USART6;
  huart6.Init.BaudRate = 9600;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
     PA2   ------> USART2_TX
     PA3   ------> USART2_RX
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MAAux_Pin MA0_Pin MA1_Pin MA2_Pin */
  GPIO_InitStruct.Pin = MAAux_Pin|MA0_Pin|MA1_Pin|MA2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : USART_TX_Pin USART_RX_Pin */
  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DIR_M2_Pin STEP_M2_Pin DIR_M4_Pin RESET_M2_Pin 
                           STEP_M1_Pin DIR_M1_Pin */
  GPIO_InitStruct.Pin = DIR_M2_Pin|STEP_M2_Pin|DIR_M4_Pin|RESET_M2_Pin 
                          |STEP_M1_Pin|DIR_M1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : STEP_M4_Pin RESET_M1_Pin RESET_M3_Pin STEP_M3_Pin 
                           DIR_M3_Pin RESET_M4_Pin */
  GPIO_InitStruct.Pin = STEP_M4_Pin|RESET_M1_Pin|RESET_M3_Pin|STEP_M3_Pin 
                          |DIR_M3_Pin|RESET_M4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|DIR_M2_Pin|STEP_M2_Pin|DIR_M4_Pin 
                          |RESET_M2_Pin|STEP_M1_Pin|DIR_M1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, STEP_M4_Pin|RESET_M1_Pin|RESET_M3_Pin|STEP_M3_Pin 
                          |DIR_M3_Pin|RESET_M4_Pin, GPIO_PIN_RESET);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

}

/** @sendMotorsToStart
  * @brief  Manda todos los motores a su posición inicial
  * @param  none
  * @retval none
  */
void sendMotorsToStart()
{
	for (i=0; i<nplayers ; i++)
	{
		if (pointPlayers[i] > MAXPOINTS )
		{
			pointPlayers[i] = MAXPOINTS;
		}
		changeDir(i+1);
		moveMotorDistance((i+1), pointPlayers[i]);
	}
}//sendMotorsToStart

void deInitVariables()
{
	  for (i=0 ; i< LENGTH ; i++)
	  {
		  FPlayer_Buffer[i] = ' ';
		  RF_Buffer[i] = ' ';
	  }

	  character = '\0';
	  nplayers = 0;
	  for (i=0 ; i<4 ; i++)
	  {
		  pointPlayers[i] = 0;
		  for (j=0 ; j<16 ; j++)
		  {
			  players[i][j] = ' ';
			  if (j == 15)
			  {
				  players[i][j] = '\0';
			  }
		  }
	  }
	  player_Cnt = 0;
	  max = -10;
	  flag_Ended = 0;
	  done = 0;

	  HAL_GPIO_WritePin(DIR_M1_GPIO_Port, DIR_M1_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(DIR_M2_GPIO_Port, DIR_M2_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(DIR_M3_GPIO_Port, DIR_M3_Pin, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(DIR_M4_GPIO_Port, DIR_M4_Pin, GPIO_PIN_RESET);
}


/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
