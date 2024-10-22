################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32F103C6_Drivers/Stm32F103C8_SPI_Driver.c \
../Stm32F103C6_Drivers/Stm32_F103C6_RCC_driver.c \
../Stm32F103C6_Drivers/Stm32_F103C6_UART_driver.c \
../Stm32F103C6_Drivers/Stm32_F103C6_gpio_driver.c \
../Stm32F103C6_Drivers/Timer.c 

OBJS += \
./Stm32F103C6_Drivers/Stm32F103C8_SPI_Driver.o \
./Stm32F103C6_Drivers/Stm32_F103C6_RCC_driver.o \
./Stm32F103C6_Drivers/Stm32_F103C6_UART_driver.o \
./Stm32F103C6_Drivers/Stm32_F103C6_gpio_driver.o \
./Stm32F103C6_Drivers/Timer.o 

C_DEPS += \
./Stm32F103C6_Drivers/Stm32F103C8_SPI_Driver.d \
./Stm32F103C6_Drivers/Stm32_F103C6_RCC_driver.d \
./Stm32F103C6_Drivers/Stm32_F103C6_UART_driver.d \
./Stm32F103C6_Drivers/Stm32_F103C6_gpio_driver.d \
./Stm32F103C6_Drivers/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32F103C6_Drivers/Stm32F103C8_SPI_Driver.o: ../Stm32F103C6_Drivers/Stm32F103C8_SPI_Driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Embedded Systems/Keroles projects/SPI_test/Stm32F103C6_Drivers/inc" -I"D:/Embedded Systems/Keroles projects/SPI_test/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32F103C6_Drivers/Stm32F103C8_SPI_Driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Stm32F103C6_Drivers/Stm32_F103C6_RCC_driver.o: ../Stm32F103C6_Drivers/Stm32_F103C6_RCC_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Embedded Systems/Keroles projects/SPI_test/Stm32F103C6_Drivers/inc" -I"D:/Embedded Systems/Keroles projects/SPI_test/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32F103C6_Drivers/Stm32_F103C6_RCC_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Stm32F103C6_Drivers/Stm32_F103C6_UART_driver.o: ../Stm32F103C6_Drivers/Stm32_F103C6_UART_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Embedded Systems/Keroles projects/SPI_test/Stm32F103C6_Drivers/inc" -I"D:/Embedded Systems/Keroles projects/SPI_test/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32F103C6_Drivers/Stm32_F103C6_UART_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Stm32F103C6_Drivers/Stm32_F103C6_gpio_driver.o: ../Stm32F103C6_Drivers/Stm32_F103C6_gpio_driver.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Embedded Systems/Keroles projects/SPI_test/Stm32F103C6_Drivers/inc" -I"D:/Embedded Systems/Keroles projects/SPI_test/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32F103C6_Drivers/Stm32_F103C6_gpio_driver.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Stm32F103C6_Drivers/Timer.o: ../Stm32F103C6_Drivers/Timer.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Embedded Systems/Keroles projects/SPI_test/Stm32F103C6_Drivers/inc" -I"D:/Embedded Systems/Keroles projects/SPI_test/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32F103C6_Drivers/Timer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

