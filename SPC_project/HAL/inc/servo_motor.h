/*
 * servo_motor1.h
 *
 *  Created on: Oct 18, 2024
 *      Author: Hello
 */

#ifndef SERVO_MOTOR1_H_
#define SERVO_MOTOR1_H_

#include "Stm32_F103X6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Timer.h"

// Servo Motor Positions
#define UP_angle		0
#define Down_angle		90

// Servo Strcture
typedef struct{
	GPIO_TypeDef* 	GPIOx ; 		// (x is the port (A,B,C,D)) .
	uint8_t 		GPIO_PIN_x ;	// (x is the pin number (0-->15) .
}Servo_Typedef_t;

/* Servo Motor APIs */
void Servo_Motor_init(Servo_Typedef_t* sm);
void Servo_Motor(Servo_Typedef_t* sm , uint32_t angle);


#endif /* SERVO_MOTOR1_H_ */
