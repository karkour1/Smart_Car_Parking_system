/*
 * srevo_motor.c
 *
 *  Created on: Oct 15, 2024
 *  Author: ABDULLAH KARKOUR
 */

#include "servo_motor.h"


/* Servo Motor APIs */
void Servo_Motor_init(Servo_Typedef_t* sm)
{
	GPIO_PinConfig_t pinCinfg;
	pinCinfg.GPIO_PinNumber = sm->GPIO_PIN_x;
	pinCinfg.GPIO_Mode		= GPIO_MODE_OUTPUT_PP;
	pinCinfg.GPIO_Output_Speed = GPIO_SPEED_10M;

	MCAL_GPIO_Init(sm->GPIOx, &pinCinfg);
}
void Servo_Motor(Servo_Typedef_t* sm , uint32_t angle)
{
	uint32_t angle_time_us=0;

	angle_time_us = ((angle*1000)/90) + 486 ;
//	angle_time_us = (angle < 180)? (((angle*1000)/90) + 500) : (((360-angle)*1000)/90) + 500 ;

	MCAL_GPIO_WritePin(sm->GPIOx, sm->GPIO_PIN_x, GPIO_PIN_SET);
	dus(angle_time_us);
	MCAL_GPIO_WritePin(sm->GPIOx, sm->GPIO_PIN_x, GPIO_PIN_RESET);
	dus(20000-angle_time_us);

}
