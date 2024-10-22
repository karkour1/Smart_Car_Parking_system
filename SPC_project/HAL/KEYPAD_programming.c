/*
*	KEYPAD_programming.c
*  	Created on: Dec 10, 2023
*   Author: Adbullah Karkour
*/

#include "KEYPAD_Config.h"
#include "KEYPAD_interface.h"

// GLOBAL VARIABLES
GPIO_PinConfig_t pinconfg  ;

uint8_t KEYPAD_ROW[KEYPAD_ROWS] = {KEYPAD_R0,KEYPAD_R1,KEYPAD_R2,KEYPAD_R3};
uint8_t KEYPAD_COLUM[KEYPAD_COLUMS] = {KEYPAD_C0,KEYPAD_C1,KEYPAD_C2,KEYPAD_C3};
uint8_t keys[KEYPAD_ROWS][KEYPAD_COLUMS]= KEYPAD_keys ;

void KEYPAD_init(void)
{
	/* Set the ROWS pins  input */
	pinconfg.GPIO_PinNumber = KEYPAD_R0;
	pinconfg.GPIO_Mode = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfg);

	pinconfg.GPIO_PinNumber = KEYPAD_R1;
	pinconfg.GPIO_Mode = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfg);

	pinconfg.GPIO_PinNumber = KEYPAD_R2;
	pinconfg.GPIO_Mode = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfg);

	pinconfg.GPIO_PinNumber = KEYPAD_R3;
	pinconfg.GPIO_Mode = GPIO_MODE_INPUT_PU;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfg);

	/* Set The COLUMS pins Output */
	pinconfg.GPIO_PinNumber = KEYPAD_C0;
	pinconfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinconfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfg);

	pinconfg.GPIO_PinNumber = KEYPAD_C1;
	pinconfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinconfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfg);

	pinconfg.GPIO_PinNumber = KEYPAD_C2;
	pinconfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinconfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfg);

	pinconfg.GPIO_PinNumber = KEYPAD_C3;
	pinconfg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinconfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(KEYPAD_PORT, &pinconfg);

	/* Set the port of data */
	MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_R0, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_R1, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_R2, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_R3, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C0, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C1, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C2, GPIO_PIN_SET);
	MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C3, GPIO_PIN_SET);
}
char KEYPAD_GetKey(void)
{
	uint8_t i , j ;

	for (i=0 ; i<KEYPAD_COLUMS ; i++)
	{
		MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C0, GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C1, GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C2, GPIO_PIN_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C3, GPIO_PIN_SET);

		/* clear COLUM number i to check the low voltage when click key */
		MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_COLUM[i], GPIO_PIN_RESET);

		/* loop for ROWs */
		for(j= 0 ; j<KEYPAD_ROWS ; j++ )
		{
			if (!(MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_ROW[j])))
			{
				while(!(MCAL_GPIO_ReadPin(KEYPAD_PORT, KEYPAD_ROW[j])));
				return keys[j][i];
			}
		}
	}

	return 0 ;
}
