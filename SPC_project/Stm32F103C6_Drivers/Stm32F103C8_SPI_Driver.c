/*
 * Stm32F103C8_SPI_Driver.c
 *
 *  Created on: Apr 2, 2024
 *  Author: ABDULLAH KARKOUR
 */

/*
* ===============================================
* Includes
* ===============================================
*/
#include "Stm32F103C8_SPI_Driver.h"

/*
* ===============================================
* 			Generic Variables
* ===============================================
*/
SPI_Config_t* G_SPI_Cfg[2] ;

/*
* ===============================================
* 			Generic Macros
* ===============================================
*/





/*
* ===============================================
* APIs Supported by "MCAL SPI DRIVER"
* ===============================================
*/

/**================================================================
 * @Fn			-MCAL_SPI_Init
 * @brief 		-Initializes the SPI according to the specified parameters in the PinConfig
 * @param [in] 	-SPIx: where x can be (1...3 depending on SPI used) to select the SPI peripheral
 * @param [in] 	-SPI_Cfg pointer to a SPI_Config_t structure that contains
 *         		 the configuration information for the specified SPI.
 * @retval 		-none
 * Note			-Support for SPI Full duplex
 	 	 	 	-NSS  Controled by HW/SW .
 */
void MCAL_SPI_Init         (SPI_TypeDef* SPIx , SPI_Config_t* SPI_Cfg )
{
	// CLock Enable to SPI and Keep SPI configuration
	if (SPIx == SPI1)
	{
		G_SPI_Cfg[0] = SPI_Cfg ;
		RCC_SPI1_CLK_EN();
	}else if(SPIx == SPI2)
	{
		G_SPI_Cfg[1] = SPI_Cfg ;
		RCC_SPI2_CLK_EN();
	}

	// define the serial clock baud rate SPI_CR1 Bits 5:3 BR[2:0]: Baud rate control
	SPIx->SPI_CR1 |= SPI_Cfg->baud_rate_prescalers ;

	// Data Size SPI_CR1 Bit 11 DFF: Data frame format
	SPIx->SPI_CR1 |= SPI_Cfg->Data_Size ;

	// Frame Fromat SPI_CR1 Bit 7 LSBFIRST: Frame format
	SPIx->SPI_CR1 |= SPI_Cfg->Frame_Format ;

	// Clock polarity SPI_CR1 Bit1 CPOL: Clock polarity
	SPIx->SPI_CR1 |= SPI_Cfg->clock_polarity ;

	// Clock phase SPI_CR1 Bit 0 CPHA: Clock phase
	SPIx->SPI_CR1 |= SPI_Cfg->clock_phase;

	// NSS Specifies Hardware or software slave select management
	// HW : SPI_CR2 Bit 2 SSOE: SS output enable
	if((SPI_Cfg->NSS == SPI_NSS_HW_Master_SS_output_disabled) ||(SPI_Cfg->NSS == SPI_NSS_HW_Master_SS_output_enabled))
	{
		SPIx->SPI_CR2 |= SPI_Cfg->NSS ;
	}else // SW : SPI_CR1 Bit 9 SSM: Software slave management Bit 8 SSI: Internal slave select
	{
		SPIx->SPI_CR1 |= SPI_Cfg->NSS ;
	}

	// IRQ Enable SPI_CR2 (Bit 5 ERRIE: Error interrupt enable , Bit 6 RXNEIE: RX buffer not empty interrupt enable , Bit 7 TXEIE: Tx buffer empty interrupt enable )
	if (SPI_Cfg->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		SPIx->SPI_CR2 |= SPI_Cfg->IRQ_Enable;

		// Enable NVIC
		if (SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_ENABLE;

		}else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_ENABLE;
		}
	}

	// Communication Mode SPI_CR1 (Bit 10 RXONLY: Receive only , Bit 14 BIDIOE: Output enable in bidirectional mode , Bit 15 BIDIMODE: Bidirectional data mode enable)
	SPIx->SPI_CR1 |= SPI_Cfg->Communication_Mode ;

	// Master or Slave SPI_CR1 Bit 2 MSTR: Master selection
	SPIx->SPI_CR1 |= SPI_Cfg->Dvice_Mode ;

	// Enable SPI Bit 6 SPE: SPI enable
	SPIx->SPI_CR1 |=(1<<6);

}

/**================================================================
 * @Fn			-MCAL_SPI_Deinit
 * @brief 		-reset all the SPI Registers
 * @param [in] 	-SPIx: where x can be (1...3 depending on SPI used) to select the SPI peripheral
 * @retval 		-none
 * Note			-none
 */
void MCAL_SPI_Deinit       (SPI_TypeDef* SPIx )
{
	if (SPIx == SPI1)
	{
		// Disable NVIC
		NVIC_IRQ35_SPI1_DISABLE;

		// Reset all Registers
		RCC_SPI1_RESET();

	}else if(SPIx == SPI2)
	{
		// Disable NVIC
		NVIC_IRQ36_SPI2_DISABLE;

		// Reset all Registers
		RCC_SPI2_RESET();
	}
}

/**================================================================
 * @Fn				-MCAL_SPI_GPIO_Set_Pins
 * @brief 			- intialize GPIO Pins ,according the recomended GPIO configurations for STM32F103xx peripherals
 * @param [in] 		-SPIx: where x can be (1...3 depending on SPI used) to select the SPI peripheral
 * @retval 			-none
 * Note				-Should enable the corresponding ALT  & GPIO  in RCC clock Also called after MCAL_SPI_Init()
 */
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx )
{
	GPIO_PinConfig_t PinCfg ;
	if (SPIx == SPI1)
	{
		// NSS >>> PA4
		// SCK >>> PA5
		// MISO >> PA6
		// MOSI >> PA7

		// Master
		if (G_SPI_Cfg[0]->Dvice_Mode == SPI_Dvice_Mode_Master )
		{
			// NSS
			if(G_SPI_Cfg[0]->NSS == SPI_NSS_HW_Master_SS_output_disabled)
			{
				// NSS >> Input floating/ Input pull-up / Input pull-down
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);

			}else if(G_SPI_Cfg[0]->NSS == SPI_NSS_HW_Master_SS_output_enabled)
			{
				// NSS >> Alternate function push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}

			// SCK >> Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			// MISO , Full duplex / master Input floating / Input pull-up
			//		  Simplex bidirectional data wire / master Not used. Can be used as a GPIO
			if(G_SPI_Cfg[0]->Communication_Mode == SPI_Communication_Mode_2line_Full_duplex)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_6;
				PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}

			// MOSI , Full duplex / master Alternate function push-pull
			//		  Simplex bidirectional data wire / master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_7;
			PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
		// Slave
		else if (G_SPI_Cfg[0]->Dvice_Mode == SPI_Dvice_Mode_Slave )
		{
			//Hardware slave NSS >> Input floating/ Input pull-up / Input pull-down
			//Software Not used. Can be used as a GPIO
			if(G_SPI_Cfg[0]->NSS == SPI_NSS_HW_Slave)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}

			// Master , SCK >> Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			// MISO , Full duplex / slave (point to point) Alternate function push-pull
			//		  Simplex bidirectional data wire/ slave (point to point) Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_6;
			PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			// MOSI , Full duplex / slave Input floating / Input pull-up
			//		 Simplex bidirectional data wire/ slave Not used. Can be used as a GPIO
			if(G_SPI_Cfg[0]->Communication_Mode == SPI_Communication_Mode_2line_Full_duplex)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_7;
				PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}

		}

	}else if (SPIx == SPI2)
	{
		// NSS >>> PB12
		// SCK >>> PB13
		// MISO >> PB14
		// MOSI >> PB15

		// Master
		if (G_SPI_Cfg[1]->Dvice_Mode == SPI_Dvice_Mode_Master )
		{
			// NSS
			if(G_SPI_Cfg[1]->NSS == SPI_NSS_HW_Master_SS_output_disabled)
			{
				// NSS >> Input floating/ Input pull-up / Input pull-down
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);

			}else if(G_SPI_Cfg[1]->NSS == SPI_NSS_HW_Master_SS_output_enabled)
			{
				// NSS >> Alternate function push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}

			// SCK >> Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			// MISO , Full duplex / master Input floating / Input pull-up
			//		  Simplex bidirectional data wire / master Not used. Can be used as a GPIO
			if(G_SPI_Cfg[1]->Communication_Mode == SPI_Communication_Mode_2line_Full_duplex)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_14;
				PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}

			// MOSI , Full duplex / master Alternate function push-pull
			//		  Simplex bidirectional data wire / master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
		// Slave
		else if (G_SPI_Cfg[1]->Dvice_Mode == SPI_Dvice_Mode_Slave )
		{
			//Hardware slave NSS >> Input floating/ Input pull-up / Input pull-down
			//Software Not used. Can be used as a GPIO
			if(G_SPI_Cfg[0]->NSS == SPI_NSS_HW_Slave)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}

			// Master , SCK >> Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			// MISO , Full duplex / slave (point to point) Alternate function push-pull
			//		  Simplex bidirectional data wire/ slave (point to point) Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_Mode = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			// MOSI , Full duplex / slave Input floating / Input pull-up
			//		 Simplex bidirectional data wire/ slave Not used. Can be used as a GPIO
			if(G_SPI_Cfg[1]->Communication_Mode == SPI_Communication_Mode_2line_Full_duplex)
			{
				PinCfg.GPIO_PinNumber = GPIO_PIN_15;
				PinCfg.GPIO_Mode = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}

		}

	}
}


/**================================================================
 * @Fn			-MCAL_SPI_Send_Data
 * @brief 		-Send data With SPI peripheral
 * @param [in] 	-SPIx: where x can be (1...3 depending on SPI used) to select the SPI peripheral
 * @param [in]  -pTxBuffer Buffer
 * @param [in]  -PollingEn   Enable pooling or disable it
 * @retval 		-none
 * Note			-none
 */
void MCAL_SPI_Send_Data   (SPI_TypeDef* SPIx  , uint16_t* PTxBuffer ,polling_mechnisem_t pollingEn )
{
	if (pollingEn == SPI_enable)
		while(!((SPIx->SPI_SR) &(1<<1))); // Tx buffer not empty

	SPIx->SPI_DR = *PTxBuffer ;
}

/**================================================================
 * @Fn			-MCAL_SPI_Receive_Data
 * @brief 		-Receive data With SPI peripheral
 * @param [in] 	-SPIx: where x can be (1...3 depending on SPI used) to select the SPI peripheral
 * @param [in]  -pRxBuffer Buffer
 * @param [in]  -PollingEn   Enable pooling or disable it
 * @retval 		-none
 * Note			-none
 */
void MCAL_SPI_Receive_Data(SPI_TypeDef* SPIx  , uint16_t* PRxBuffer ,polling_mechnisem_t pollingEn )
{
	if (pollingEn == SPI_enable)
		while(!((SPIx->SPI_SR) &(1))); //  Rx buffer empty

	*PRxBuffer = SPIx->SPI_DR ;
}

/**================================================================
 * @Fn			-MCAL_SPI_TX_RX
 * @brief 		-Send and Receive data With SPI peripheral
 * @param [in] 	-SPIx: where x can be (1...3 depending on SPI used) to select the SPI peripheral
 * @param [in]  -pTxBuffer Buffer
 * @param [in]  -PollingEn   Enable pooling or disable it
 * @retval 		-none
 * Note			-none
 */
void MCAL_SPI_TX_RX       (SPI_TypeDef* SPIx  , uint16_t* PTxBuffer ,polling_mechnisem_t pollingEn )
{
	// Send Data
	MCAL_SPI_Send_Data(SPIx, PTxBuffer, pollingEn);

	// Receive Data
	MCAL_SPI_Receive_Data(SPIx, PTxBuffer, pollingEn);
}



/*
* ===============================================
* 					IRQ
* ===============================================
*/

void SPI1_IRQHandler(void)
{
	S_IRQ_SRC IRQ_src ;

	IRQ_src.TXE =  (((SPI1->SPI_SR)>>1)&1);
	IRQ_src.RXNE = (((SPI1->SPI_SR)>>0)&1);
	IRQ_src.ERRI = (((SPI1->SPI_SR)>>4)&1);;

	G_SPI_Cfg[0]->P_IRQ_CallBack(IRQ_src);
}

void SPI2_IRQHandler(void)
{
	S_IRQ_SRC IRQ_src ;

	IRQ_src.TXE =  (((SPI2->SPI_SR)>>1)&1);
	IRQ_src.RXNE = (((SPI2->SPI_SR)>>0)&1);
	IRQ_src.ERRI = (((SPI2->SPI_SR)>>4)&1);

	G_SPI_Cfg[1]->P_IRQ_CallBack(IRQ_src);
}















