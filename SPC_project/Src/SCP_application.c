/*
 * SCP_application.c
 *
 *  Created on: Oct 18, 2024
 *  Author: ABDULLAH KARKOUR
 */
/*******************		...INCLUDES...		*******************/
#include "SCP_application.h"


/*******************		...Global variables...		*******************/
uint8_t slots_number;
uint8_t avalible_slots;
uint32_t IDs_Container[50];
uint8_t last_id_index;

uint16_t enter_RX , exit_RX ;
uint32_t Entry_id , Exit_id ;

Servo_Typedef_t servo1 ={GPIOB,GPIO_PIN_8} , servo2= {GPIOB,GPIO_PIN_9} ;
LCD_Config_t lcd1 ={GPIOB , GPIOB ,GPIO_PIN_11,GPIO_PIN_2,GPIO_PIN_10 } , lcd2={GPIOA , GPIOA ,GPIO_PIN_5,GPIO_PIN_8,GPIO_PIN_6 } ;
/*******************		...Global Functions...		*******************/
uint8_t Search_ID(uint32_t id)
{
	uint8_t i;
	for(i=0; i<last_id_index ; i++)
	{
		if(id == IDs_Container[i])
			return i ;
	}
	return last_id_index;
}

void usart1_IRQ(void)
{
	MCAL_UART_ReceiveData(USART1, &enter_RX, disable);
	if(enter_RX != '#')
		Entry_id = (Entry_id == 0)? (enter_RX-'0') : ((Entry_id*10) + (enter_RX-'0'));
	else
	{
		SCP_Entry_Process(Entry_id);
		Entry_id = 0;
	}
}

void usart2_IRQ(void)
{
	MCAL_UART_ReceiveData(USART2, &exit_RX, disable);
	if(exit_RX != '#')
		Exit_id = (Exit_id == 0)? (exit_RX-'0') : ((Exit_id*10) + (exit_RX-'0'));
	else
	{
		SCP_Exit_Process(Exit_id);
		Exit_id = 0;
	}
}

/*******************		...APIs...		*******************/
void SCP_Init()
{
	/* Initiate system drivers. */
	KEYPAD_init();
	lcd1.LCD_D4_PIN = GPIO_PIN_12;
	lcd1.LCD_D5_PIN = GPIO_PIN_13;
	lcd1.LCD_D6_PIN = GPIO_PIN_14;
	lcd1.LCD_D7_PIN = GPIO_PIN_15;

	lcd2.LCD_D4_PIN = GPIO_PIN_12;
	lcd2.LCD_D5_PIN = GPIO_PIN_13;
	lcd2.LCD_D6_PIN = GPIO_PIN_14;
	lcd2.LCD_D7_PIN = GPIO_PIN_15;

	LCD_init(&lcd1);
	LCD_init(&lcd2);

	/* Welcome massage */
	LCD_Send_string(&lcd1 ,"Welcome to SCP:)");

	do
	{
		/* Instructions massage */
		uint8_t ch=0;
		LCD_Clear_Screen(&lcd1);
		LCD_Send_string(&lcd1 ,"slots number :");
		slots_number = 0 ;
		while((ch = KEYPAD_GetKey())!='#')
		{
			if(ch != 0)
			{
				LCD_Send_Character(&lcd1 ,ch);
				slots_number = (slots_number==0)? (ch -'0') : ((slots_number*10)+(ch - '0')) ;
			}
		}

		if(slots_number >50 || slots_number<=0)
		{
			LCD_Clear_Screen(&lcd1);
			LCD_Send_string(&lcd1 ,"not valid , try again");
		}
	}while(slots_number>50 || slots_number <=0);
	avalible_slots = slots_number ;
	LCD_Clear_Screen(&lcd1);
	/* Default massage */
	LCD_Send_string(&lcd1 ,"For options '*'");

	/* Led and PIR Pins config*/
	GPIO_PinConfig_t pinConfig;

	//green led
	pinConfig.GPIO_PinNumber = GPIO_PIN_11 ;
	pinConfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinConfig);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	//red led
	pinConfig.GPIO_PinNumber = GPIO_PIN_0 ;
	pinConfig.GPIO_Mode = GPIO_MODE_OUTPUT_PP;
	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinConfig);
	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);

	//PIR1
	pinConfig.GPIO_PinNumber = GPIO_PIN_7 ;
	pinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;
	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinConfig);
	//PIR2
	pinConfig.GPIO_PinNumber = GPIO_PIN_1 ;
	pinConfig.GPIO_Mode = GPIO_MODE_INPUT_FLO;
	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOA, &pinConfig);

	/* UART Configratons */
	UART_PinConfig_t uart_config ;
	uart_config.BaudRate 		= UART_BaudRate_9600 ;
	uart_config.HwFlowCtl 		= UART_HwFlowCtl_NONE;
	uart_config.IRQ_Enable 		= UART_IRQ_Enable_RXNEIE;
	uart_config.P_IRQ_CallBack	= usart1_IRQ ;
	uart_config.Mode       		= UART_Mode_RX;
	uart_config.Parity	   		= UART_Parity__NONE;
	uart_config.Payload_Length 	= UART_Payload_Length_8B;
	uart_config.StopBits	   	= UART_StopBits__1;
	MCAL_UART_Init(USART1, &uart_config);
	MCAL_UART_GPIO_Set_Pins(USART1);

	uart_config.BaudRate 		= UART_BaudRate_9600 ;
	uart_config.HwFlowCtl 		= UART_HwFlowCtl_NONE;
	uart_config.IRQ_Enable 		= UART_IRQ_Enable_RXNEIE;
	uart_config.P_IRQ_CallBack 	= usart2_IRQ ;
	uart_config.Mode       		= UART_Mode_RX;
	uart_config.Parity	   		= UART_Parity__NONE;
	uart_config.Payload_Length 	= UART_Payload_Length_8B;
	uart_config.StopBits	   	= UART_StopBits__1;
	MCAL_UART_Init(USART2, &uart_config);
	MCAL_UART_GPIO_Set_Pins(USART2);

	/* Servo Initiate */
	Timer2_init();
	Servo_Motor_init(&servo1);
	Servo_Motor_init(&servo2);
	Servo_Motor(&servo1, Down_angle);
	Servo_Motor(&servo2, Down_angle);

}

void SCP_Options()
{
	LCD_Send_string(&lcd1 ,"1.Add ID        ");
	LCD_Send_string(&lcd1 ,"2.Remove ID     ");
	LCD_Send_string(&lcd1 ,"3.Exit");

}

void SCP_Add_ID()
{
	LCD_Clear_Screen(&lcd1);

	uint32_t IDs_number=0;
	uint8_t ch ;

	LCD_Send_string(&lcd1 ,"Enter ID Number :");
	while((ch= KEYPAD_GetKey())!='#')
	{
		if((ch != 0))
		{
			LCD_Send_Character(&lcd1,ch);
			IDs_number = (IDs_number==0)? (ch -'0') : ((IDs_number*10)+(ch - '0')) ;
		}
	}
	LCD_Clear_Screen(&lcd1);

	if(IDs_number> (3*(slots_number - (last_id_index))))
	{
		LCD_Send_string(&lcd1 ,"avalible number is : ");
		LCD_Display_Number(&lcd1 ,(3*slots_number - (last_id_index)));
	}
	else
	{
		while(IDs_number > 0)
		{
			LCD_Send_string(&lcd1 ,"Enter ID :");
			ch = 0 ;
			while((ch = KEYPAD_GetKey())!='#')
			{
				if(ch != 0)
				{
					LCD_Send_Character(&lcd1,ch);
					IDs_Container[last_id_index] = (IDs_Container[last_id_index]==0)? (ch -'0') : ((IDs_Container[last_id_index]*10)+(ch - '0')) ;
				}
			}
			LCD_Clear_Screen(&lcd1);

			if(Search_ID(IDs_Container[last_id_index]) != last_id_index)

			{
				LCD_Send_string(&lcd1 ,"ID is exist     ");
				LCD_Send_string(&lcd1 ,"ID was not added");
			}

			else
			{
				last_id_index++;
				LCD_Send_string(&lcd1 ,"ID was added:)");
			}


			IDs_number--;
			LCD_Clear_Screen(&lcd1);
		}
	}

}

void SCP_Remove_ID()
{
	LCD_Clear_Screen(&lcd1);
	uint8_t ch=0 ;

	LCD_Send_string(&lcd1 ,"1.Delete all IDs");
	LCD_Send_string(&lcd1 ,"2.Other");

	while((ch=KEYPAD_GetKey())== 0);
	LCD_Clear_Screen(&lcd1);

	if(ch == '1')
	{
		last_id_index = 0 ;
		LCD_Send_string(&lcd1 ,"All Ids were deleted!");
	}
	else if(ch == '2')
	{

		uint32_t IDs_number=0;

		LCD_Send_string(&lcd1 ,"Enter ID Number maximum (");
		LCD_Display_Number(&lcd1,last_id_index);
		LCD_Send_string(&lcd1 ,"):");
		while((ch= KEYPAD_GetKey())!='#')
		{
			if((ch != 0))
			{
				LCD_Send_Character(&lcd1,ch);
				IDs_number = (IDs_number==0)? (ch -'0') : ((IDs_number*10)+(ch - '0')) ;
			}
		}
		LCD_Clear_Screen(&lcd1);

		while(IDs_number > 0)
		{
			LCD_Send_string(&lcd1 ,"Enter ID :");
			ch = 0 ;
			uint32_t id = 0 ;
			while((ch = KEYPAD_GetKey())!='#')
			{
				if(ch != 0)
				{
					LCD_Send_Character(&lcd1,ch);
					id = (id==0)? (ch -'0') : ((id*10)+(ch - '0')) ;
				}
			}
			LCD_Clear_Screen(&lcd1);

			if(Search_ID(id) == last_id_index)

			{
				LCD_Send_string(&lcd1 ,"ID is not exist ");
			}

			else
			{
				uint8_t index ;
				index = Search_ID(id);

				last_id_index--;

				IDs_Container[index] = IDs_Container[last_id_index];
				IDs_Container[last_id_index]=0;
				LCD_Send_string(&lcd1 ,"ID was deleted:)");
			}


			IDs_number--;
			LCD_Clear_Screen(&lcd1);
		}
	}
}

void SCP_Entry_Process(uint32_t id)
{

	if(avalible_slots >0)
	{

		if(Search_ID(id) != last_id_index)
		{
			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
			avalible_slots-- ;
			LCD_Send_string(&lcd2 ,"valid ID ,you can enter :)");
			while(!(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)));
			Servo_Motor(&servo1,UP_angle);
			while(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7));
			Servo_Motor(&servo1, Down_angle);
			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
		}
		else
		{
			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
			LCD_Send_string(&lcd2 ,"not valid ID:)");
			dms(500);
			MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
		}
	}
	else
	{
		LCD_Send_string(&lcd2,"Parking is Full try again later:(");
	}
	LCD_Clear_Screen(&lcd2);
}

void SCP_Exit_Process(uint32_t id)
{
	if(Search_ID(id) != last_id_index)
	{
		avalible_slots++;
		while(!(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1)));
		Servo_Motor(&servo2,UP_angle);
		while(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1));
		Servo_Motor(&servo2, Down_angle);
	}
}
