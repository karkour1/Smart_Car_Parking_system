/*
*	KEYPAD_Config.h
*  	Created on: Dec 10, 2023
*   Author: Adbullah Karkour
*/


#ifndef KEYPAD_KEYPAD_CONFIG_H_
#define KEYPAD_KEYPAD_CONFIG_H_

// INCLUDES
#include "Stm32_F103X6.h"
#include "Stm32_F103C6_gpio_driver.h"

/* KETPAD Configuration port */
#define KEYPAD_PORT    GPIOB

/* KEYPAD PINS */
#define  KEYPAD_R0   GPIO_PIN_0
#define  KEYPAD_R1   GPIO_PIN_1
#define  KEYPAD_R2   GPIO_PIN_3
#define  KEYPAD_R3   GPIO_PIN_4

#define  KEYPAD_C0   GPIO_PIN_5
#define  KEYPAD_C1   GPIO_PIN_6
#define  KEYPAD_C2   GPIO_PIN_7
#define  KEYPAD_C3   GPIO_PIN_2

/*NUMBER OF ROWS AND COLUMS*/
#define  KEYPAD_ROWS   4
#define  KEYPAD_COLUMS 3

/* KEYPAD KEYS */
#define  KEYPAD_keys  {'*','0','#','7','8','9','4','5','6','1','2','3'}


#endif /* KEYPAD_KEYPAD_CONFIG_H_ */
