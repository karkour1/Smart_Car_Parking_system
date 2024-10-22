/**
 ******************************************************************************
 * @file           : main.c
 * @author         : ABDULLAH KARKOUR
 * @brief          : Main program body
 ******************************************************************************
 **/

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include "SCP_application.h"

extern LCD_Config_t lcd1;

void clock_init()
{
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();

	RCC_USART1_CLK_EN();
	RCC_USART2_CLK_EN();
}
int main(void)
{
	clock_init();
	SCP_Init();

	uint8_t operation_ch = 0 ;
    /* Loop forever */
	while(1)
	{
		if((operation_ch= KEYPAD_GetKey())=='*')
		{
			//	Gates system stop till Admin updates.
			NVIC_IRQ37_USART1_DISABLE;
			NVIC_IRQ38_USART2_DISABLE;

			LCD_Clear_Screen(&lcd1);
			SCP_Options();
			operation_ch =0 ;
			while((operation_ch = KEYPAD_GetKey())== 0);

			switch(operation_ch)
			{
			case '1':
				SCP_Add_ID();
				break;
			case '2':
				SCP_Remove_ID();
				break;
			default:
				break;
			}

			LCD_Clear_Screen(&lcd1);
			LCD_Send_string(&lcd1 ,"For options '*'");

			NVIC_IRQ37_USART1_ENABLE;
			NVIC_IRQ38_USART2_ENABLE;
		}
	}
}
