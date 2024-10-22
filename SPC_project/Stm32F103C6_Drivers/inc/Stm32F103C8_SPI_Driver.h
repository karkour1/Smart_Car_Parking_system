/*
 * Stm32F103C8_SPI_Driver.h
 *
 *  Created on: Apr 2, 2024
 *  Author: ABDULLAH KARKOUR
 */

#ifndef INC_STM32F103C8_SPI_DRIVER_H_
#define INC_STM32F103C8_SPI_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "Stm32_F103X6.h"
#include "Stm32_F103C6_gpio_driver.h"

/*
* ===============================================
* 			Generic Variables
* ===============================================
*/
typedef struct{
	uint8_t TXE:1 ;
	uint8_t RXNE:1;
	uint8_t ERRI:1;
	uint8_t Res:5 ;
}S_IRQ_SRC;

typedef enum {
	SPI_enable ,
	SPI_disable
}polling_mechnisem_t;

//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef struct
{
	uint16_t Dvice_Mode ;      		  /* Specifies the Device is Master or Slave
							    		 This parameter must be set based on @ref SPI_Dvice_Mode_define
									  */

	uint16_t Communication_Mode ; 	  /* Specifies the mode of the communication (Full duplex , half duplex, unidirection data )
										 This parameter can be a value of @ref SPI_Communication_Mode_define
									  */

	uint16_t Data_Size ;           	  /* Specifies data frame Size is 8 or 16 bits long
								 	     This parameter can be a value of @ref SPI_Data_Size_define
								 	  */

	uint16_t Frame_Format ;     	  /* Data can be shifted out either MSB-first or LSB-first
								   	     This parameter can be a value of @ref SPI_Frame_Format_define
									  */

	uint16_t baud_rate_prescalers ;	  /* control Baud rate of Transmit and receive SCK Clock
										 the serial clock is received on the SCK pin from the master device
										 must configure the RCC to enter the CLock to SPI (APB2_CLK->SPI1)(APB1_CLK->SPI2)
								   	     This parameter can be a value of @ref SPI_baud_rate_prescalers_define
									  */

	uint16_t NSS ;					  /* Specifies Hardware or software slave select management
										software : The slave select information is driven internally by the status register.
												   The external NSS pin remains free for other application uses
										Hardware : Two configurations are possible depending on the NSS output configuration
												   The external NSS pin remains free for other application uses
													1.(NSS output enabled)This configuration is used only when the device operates in master mode
													2.(NSS output disabled)This configuration allows multimaster capability for devices operating in master mode
										This parameter can be a value of @ref NSS_define
									  */

	uint16_t clock_polarity ;		  /*Clock polarity  controls the steady state value of the clock when no data is being transferred
										This parameter can be a value of @ref clock_polarity_define
	 	 	 	 	 	 	 	 	  */

	uint16_t clock_phase;			  /* Clock phase selects the data capture clock edge
										 This parameter can be a value of @ref clock_phase_define
									  */

	uint16_t IRQ_Enable ;		  	  /* Specifies which interrupt will enable
										This parameter can be a value of @ref SPI_IRQ_Enable_define
									  */

	void(*P_IRQ_CallBack)(S_IRQ_SRC IRQ_src);

}SPI_Config_t;



//-----------------------------
//Macros Configuration References
//-----------------------------

// @ref SPI_Dvice_Mode_define
#define SPI_Dvice_Mode_Slave						(0x0000U)
#define SPI_Dvice_Mode_Master						(1<<2)

//@ref SPI_Communication_Mode_define
#define SPI_Communication_Mode_2line_Full_duplex	(0x0000U)
#define SPI_Communication_Mode_2line_Receive_only	(1<<10)			 //Output disabled (Receive-only mode)
#define SPI_Communication_Mode_1line_transmit_only	((1<<15)|(1<<14))//Bit 14 BIDIOE: Output enable in bidirectional mode (1: Output enabled (transmit-only mode))
#define SPI_Communication_Mode_1line_Receive_only	(1<<15)			 //Bit 15 BIDIMODE: Bidirectional data mode enable(Bit 15 BIDIMODE: Bidirectional data mode enable)

//@ref SPI_Data_Size_define
#define SPI_Data_Size_8bits							(0x0000U)
#define SPI_Data_Size_16bits						(1<<11)

//  @ref SPI_Frame_Format_define
#define SPI_Frame_Format_MSB_First					(0x0000U)
#define SPI_Frame_Format_LSB_First					(1<<7)

//@ref SPI_baud_rate_prescalers_define
#define SPI_baud_rate_prescalers_2					(0x0000U)
#define SPI_baud_rate_prescalers_4					(1<<3)
#define SPI_baud_rate_prescalers_8					(2<<3)
#define SPI_baud_rate_prescalers_16					(3<<3)
#define SPI_baud_rate_prescalers_32					(4<<3)
#define SPI_baud_rate_prescalers_64					(5<<3)
#define SPI_baud_rate_prescalers_128				(6<<3)
#define SPI_baud_rate_prescalers_256				(7<<3)

//@ref SPI_NSS_define
#define SPI_NSS_SW_Internal_select_Reset			(1<<9) 			// SPI_CR1 Bit 9 SSM: Software slave management
#define SPI_NSS_SW_Internal_select_Set				((1<<9)|(1<<8)) // SPI_CR1 Bit 9 SSM: Software slave management Bit 8 SSI: Internal slave select

#define SPI_NSS_HW_Slave 							(0x0000U)		// SPI_CR1 Bit 9 SSM: Software slave management
#define SPI_NSS_HW_Master_SS_output_enabled			(1<<2)			// SPI_CR2 Bit 2 SSOE: SS output enable
#define SPI_NSS_HW_Master_SS_output_disabled		(0x0000U)		// SPI_CR2 Bit 2 SSOE: SS output enable

// @ref SPI_clock_polarity_define
#define SPI_clock_polarity_LOW						(0x0000U)
#define SPI_clock_polarity_HIGH						(1<<1)

//@ref SPI_clock_phase_define
#define SPI_clock_phase_First_Edge					(0x0000U)
#define SPI_clock_phase_Second_Edge					0x01

// @ref SPI_IRQ_Enable_define
#define SPI_IRQ_Enable_NONE 						(0x0000U)
#define SPI_IRQ_Enable_TXEIE 						(1<<7)
#define SPI_IRQ_Enable_RXNEIE 						(1<<6)
#define SPI_IRQ_Enable_ERRIE 						(1<<5)




/*
* ===============================================
* APIs Supported by "MCAL SPI DRIVER"
* ===============================================
*/

void MCAL_SPI_Init         (SPI_TypeDef* SPIx , SPI_Config_t* SPI_Cfg );
void MCAL_SPI_Deinit       (SPI_TypeDef* SPIx );
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx );

void MCAL_SPI_Send_Data   (SPI_TypeDef* SPIx  , uint16_t* PTxBuffer ,polling_mechnisem_t pollingEn );
void MCAL_SPI_Receive_Data(SPI_TypeDef* SPIx  , uint16_t* PRxBuffer ,polling_mechnisem_t pollingEn );
void MCAL_SPI_TX_RX       (SPI_TypeDef* SPIx  , uint16_t* PTxBuffer ,polling_mechnisem_t pollingEn );


#endif /* INC_STM32F103C8_SPI_DRIVER_H_ */
