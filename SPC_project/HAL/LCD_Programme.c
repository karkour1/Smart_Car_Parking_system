/*
*	LCD_Programme.c
*  	Created on: Dec 10, 2023
*   Author: Adbullah Karkour
*/


#include "LCD_interface.h"

// global variables
GPIO_PinConfig_t pincofg  ;

// LCD global functions
void wait_ms(uint32_t time )
{
	uint32_t i,j;
	for(i=0 ; i<time ; i++)
		for(j=0 ; j<255 ; j++);
}
void LCD_EN_Pluse(LCD_Config_t* lcd)
{
	MCAL_GPIO_WritePin(lcd->LCD_CONTROL_PORT, lcd->LCD_EN_PIN, GPIO_PIN_RESET);
	wait_ms(50);
	MCAL_GPIO_WritePin(lcd->LCD_CONTROL_PORT, lcd->LCD_EN_PIN, GPIO_PIN_SET);
}

/* LCD APIS */
void LCD_init(LCD_Config_t* lcd)
{
	wait_ms(20);

	/* 8_BIT_MODE_INIT*/
#if LCD_MODE == LCD_8_BIT_MODE
	// Set LCD Data Port output
		pincofg.GPIO_PinNumber = lcd->LCD_D0_PIN;
		pincofg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
		pincofg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(lcd->LCD_DATA_PORT, &pincofg);

		pincofg.GPIO_PinNumber = lcd->LCD_D1_PIN;
		pincofg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
		pincofg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(lcd->LCD_DATA_PORT, &pincofg);

		pincofg.GPIO_PinNumber = lcd->LCD_D2_PIN;
		pincofg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
		pincofg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(lcd->LCD_DATA_PORT, &pincofg);

		pincofg.GPIO_PinNumber = lcd->LCD_D3_PIN;
		pincofg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
		pincofg.GPIO_Output_Speed = GPIO_SPEED_10M;
		MCAL_GPIO_Init(lcd->LCD_DATA_PORT, &pincofg);

#endif
	pincofg.GPIO_PinNumber = lcd->LCD_D4_PIN;
	pincofg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pincofg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(lcd->LCD_DATA_PORT, &pincofg);

	pincofg.GPIO_PinNumber = lcd->LCD_D5_PIN;
	pincofg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pincofg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(lcd->LCD_DATA_PORT, &pincofg);

	pincofg.GPIO_PinNumber = lcd->LCD_D6_PIN;
	pincofg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pincofg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(lcd->LCD_DATA_PORT, &pincofg);

	pincofg.GPIO_PinNumber = lcd->LCD_D7_PIN;
	pincofg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pincofg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(lcd->LCD_DATA_PORT, &pincofg);

	// SET control pins output (Rs , RW , EN)
	pincofg.GPIO_PinNumber = lcd->LCD_RS_PIN;
	pincofg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pincofg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(lcd->LCD_CONTROL_PORT, &pincofg);

	pincofg.GPIO_PinNumber = lcd->LCD_RW_PIN;
	pincofg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pincofg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(lcd->LCD_CONTROL_PORT, &pincofg);

	pincofg.GPIO_PinNumber = lcd->LCD_EN_PIN;
	pincofg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pincofg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(lcd->LCD_CONTROL_PORT, &pincofg);

	//put the LCD in command mode (RS =0 off)
	MCAL_GPIO_WritePin(lcd->LCD_CONTROL_PORT, lcd->LCD_RS_PIN, GPIO_PIN_RESET);

	// put the LCD in write mode (RW =0 off)
	MCAL_GPIO_WritePin(lcd->LCD_CONTROL_PORT, lcd->LCD_RW_PIN, GPIO_PIN_RESET);

	// EN off
	MCAL_GPIO_WritePin(lcd->LCD_CONTROL_PORT, lcd->LCD_EN_PIN, GPIO_PIN_RESET);

	wait_ms(15);
	LCD_Clear_Screen(lcd);

	/* 8_BIT_MODE_INIT*/
#if LCD_MODE == LCD_8_BIT_MODE
	LCD_Send_Command(lcd ,LCD_FUNCTION_8BIT_2LINE);

	/*4_BIT_MODE_INIT*/
#elif LCD_MODE == LCD_4_BIT_MODE

	LCD_Send_Command(lcd ,0x02);
	LCD_Send_Command(lcd ,LCD_FUNCTION_4BIT_2LINE);

#endif


	LCD_Send_Command(lcd ,LCD_ENTRY_MODE);
	LCD_Send_Command(lcd ,LCD_BEGIN_AT_FIRST_RAW);
	LCD_Send_Command(lcd ,LCD_DISP_ON_CURSOR_BLINK);

}
void LCD_Is_Busy(LCD_Config_t* lcd)
{
	// set pin connected to D7 to receive data (Data direction as input).
	pincofg.GPIO_PinNumber = lcd->LCD_D7_PIN;
	pincofg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(lcd->LCD_DATA_PORT, &pincofg);

	// put the LCD in read mode (RW =1 on)
	MCAL_GPIO_WritePin(lcd->LCD_CONTROL_PORT, lcd->LCD_RW_PIN, GPIO_PIN_SET);

	//put the LCD in command mode (RS =0 off)
	MCAL_GPIO_WritePin(lcd->LCD_CONTROL_PORT, lcd->LCD_RS_PIN, GPIO_PIN_RESET);

	while (((MCAL_GPIO_ReadPin(lcd->LCD_DATA_PORT, lcd->LCD_D7_PIN))&1));

	// set  D7 to receive data (Data direction as output).
	pincofg.GPIO_PinNumber = lcd->LCD_D7_PIN;
	pincofg.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pincofg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(lcd->LCD_DATA_PORT, &pincofg);

	// put the LCD in write mode (RW =0 off)
	MCAL_GPIO_WritePin(lcd->LCD_CONTROL_PORT, lcd->LCD_RW_PIN, GPIO_PIN_RESET);

}
void LCD_Send_Command(LCD_Config_t* lcd ,uint8_t command)
{
	// Check if LCD is busy
	LCD_Is_Busy(lcd);

	//put the LCD in command mode (RS =0 off)
	MCAL_GPIO_WritePin(lcd->LCD_CONTROL_PORT, lcd->LCD_RS_PIN, GPIO_PIN_RESET);

	// put the LCD in write mode (RW off)
	MCAL_GPIO_WritePin(lcd->LCD_CONTROL_PORT, lcd->LCD_RW_PIN, GPIO_PIN_RESET);

#if LCD_MODE == LCD_8_BIT_MODE
//  Write on the 8bit connected to LCD data 8 pins
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D0_PIN, ((command >>0) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D1_PIN, ((command >>1) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D2_PIN, ((command >>2) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D3_PIN, ((command >>3) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D4_PIN, ((command >>4) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D5_PIN, ((command >>5) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D6_PIN, ((command >>6) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D7_PIN, ((command >>7) & 1));
	LCD_EN_Pluse(lcd);

#elif LCD_MODE == LCD_4_BIT_MODE

	// Write The Most 4 bits Of command on Data Pins
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D4_PIN, ((command >>4) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D5_PIN, ((command >>5) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D6_PIN, ((command >>6) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D7_PIN, ((command >>7) & 1));
	LCD_EN_Pluse(lcd);

	// Write The Least 4 bits Of command on Data Pins
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D4_PIN, ((command) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D5_PIN, ((command >>1) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D6_PIN, ((command >>2) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D7_PIN, ((command >>3) & 1));
	LCD_EN_Pluse(lcd);

#endif


}
void LCD_Send_Character(LCD_Config_t* lcd ,uint8_t character)
{
	//put the LCD in Data mode (RS=1 on)
	MCAL_GPIO_WritePin(lcd->LCD_CONTROL_PORT, lcd->LCD_RS_PIN, GPIO_PIN_SET);

	// put the LCD in write mode (RW =0 off)
	MCAL_GPIO_WritePin(lcd->LCD_CONTROL_PORT, lcd->LCD_RW_PIN, GPIO_PIN_RESET);

	// to set cursor and count the characters
#if LCD_MODE == LCD_8_BIT_MODE

	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D0_PIN, ((character) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D1_PIN, ((character >>1) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D2_PIN, ((character >>2) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D3_PIN, ((character >>3) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D4_PIN, ((character >>4) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D5_PIN, ((character >>5) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D6_PIN, ((character >>6) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D7_PIN, ((character >>7) & 1));
	LCD_EN_Pluse(lcd);

#elif LCD_MODE == LCD_4_BIT_MODE

	// Write The Most 4 bits Of data on Data Pins
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D4_PIN, ((character >>4) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D5_PIN, ((character >>5) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D6_PIN, ((character >>6) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D7_PIN, ((character >>7) & 1));
	LCD_EN_Pluse(lcd);

	// Write The Least 4 bits Of data on Data Pins
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D4_PIN, (character & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D5_PIN, ((character>>1) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D6_PIN, ((character>>2) & 1));
	MCAL_GPIO_WritePin(lcd->LCD_DATA_PORT, lcd->LCD_D7_PIN, ((character>>3) & 1));
	LCD_EN_Pluse(lcd);

#endif

}
void LCD_Send_string(LCD_Config_t* lcd ,uint8_t* string)
{
	uint8_t counter = 0;
	while( *string > 0)
	{
		counter++;
		LCD_Send_Character(lcd ,*string);
		string++;

		if(counter == 16)
		{
			LCD_SET_Cursor(lcd,2, 0);
		}
		else if(counter == 32)
		{
			LCD_Clear_Screen(lcd);
			LCD_SET_Cursor(lcd,1, 0);
			counter =0 ;
		}
	}
}
void LCD_Clear_Screen(LCD_Config_t* lcd)
{
	LCD_Send_Command(lcd ,LCD_CLEAR_SCREEN);
}
void LCD_SET_Cursor(LCD_Config_t* lcd ,uint8_t line , uint8_t position )
{
	if (line == 1)
	{
		if(position<16)
		LCD_Send_Command(lcd,LCD_BEGIN_AT_FIRST_RAW + position);
	}
	else if (line == 2)
	{
		if(position<16)
		LCD_Send_Command(lcd,LCD_BEGIN_AT_SECOND_RAW + position);
	}
}
void LCD_Display_Number(LCD_Config_t* lcd,uint32_t number)
{
	uint8_t str[7];
	sprintf(str,"%d",number);
	LCD_Send_string(lcd,str);
}
void LCD_Display_Real_Number(LCD_Config_t* lcd,double number)
{
	uint8_t str[16];

	uint8_t sign = (number<0)? "-":"";
	float Temp = (number<0)? -number:number;

	uint32_t temp1 = Temp;
	uint32_t temp2 = (Temp - temp1) *10000 ;
	sprintf(str,"%s%d.%04d",sign , temp1, temp2);
	LCD_Send_string(lcd,str);
}
