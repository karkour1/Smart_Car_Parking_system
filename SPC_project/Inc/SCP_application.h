/*
 * SCP_application.h
 *
 *  Created on: Oct 18, 2024
 *  Author: ABDULLAH KARKOUR
 */

#ifndef SCP_APPLICATION_H_
#define SCP_APPLICATION_H_

/*******************		...INCLUDES...		*******************/
#include "Stm32_F103X6.h"
#include "Stm32_F103C6_RCC_driver.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_UART_driver.h"
#include "Timer.h"


#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "servo_motor.h"


/*******************		...Global variables...		*******************/


/*******************		...APIs...		*******************/
void SCP_Init();
void SCP_Options();
void SCP_Add_ID();
void SCP_Remove_ID();
void SCP_Entry_Process(uint32_t id);
void SCP_Exit_Process(uint32_t id);

#endif /* SCP_APPLICATION_H_ */
