################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KEYPAD_programming.c \
../HAL/LCD_Programme.c \
../HAL/srevo_motor.c 

OBJS += \
./HAL/KEYPAD_programming.o \
./HAL/LCD_Programme.o \
./HAL/srevo_motor.o 

C_DEPS += \
./HAL/KEYPAD_programming.d \
./HAL/LCD_Programme.d \
./HAL/srevo_motor.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/KEYPAD_programming.o: ../HAL/KEYPAD_programming.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Embedded Systems/Keroles projects/SPI_test/Stm32F103C6_Drivers/inc" -I"D:/Embedded Systems/Keroles projects/SPI_test/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/KEYPAD_programming.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/LCD_Programme.o: ../HAL/LCD_Programme.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Embedded Systems/Keroles projects/SPI_test/Stm32F103C6_Drivers/inc" -I"D:/Embedded Systems/Keroles projects/SPI_test/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/LCD_Programme.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
HAL/srevo_motor.o: ../HAL/srevo_motor.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I../Inc -I"D:/Embedded Systems/Keroles projects/SPI_test/Stm32F103C6_Drivers/inc" -I"D:/Embedded Systems/Keroles projects/SPI_test/HAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/srevo_motor.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

