################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Modbus/ModbusIf/Src/Modbus2Gpio.c \
../Middlewares/Modbus/ModbusIf/Src/ModbusIf_Gpio.c \
../Middlewares/Modbus/ModbusIf/Src/ModbusIf_Memory.c \
../Middlewares/Modbus/ModbusIf/Src/ModbusIf_Serial.c \
../Middlewares/Modbus/ModbusIf/Src/UARTCallback.c 

C_DEPS += \
./Middlewares/Modbus/ModbusIf/Src/Modbus2Gpio.d \
./Middlewares/Modbus/ModbusIf/Src/ModbusIf_Gpio.d \
./Middlewares/Modbus/ModbusIf/Src/ModbusIf_Memory.d \
./Middlewares/Modbus/ModbusIf/Src/ModbusIf_Serial.d \
./Middlewares/Modbus/ModbusIf/Src/UARTCallback.d 

OBJS += \
./Middlewares/Modbus/ModbusIf/Src/Modbus2Gpio.o \
./Middlewares/Modbus/ModbusIf/Src/ModbusIf_Gpio.o \
./Middlewares/Modbus/ModbusIf/Src/ModbusIf_Memory.o \
./Middlewares/Modbus/ModbusIf/Src/ModbusIf_Serial.o \
./Middlewares/Modbus/ModbusIf/Src/UARTCallback.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Modbus/ModbusIf/Src/%.o: ../Middlewares/Modbus/ModbusIf/Src/%.c Middlewares/Modbus/ModbusIf/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DDEBUG -c -I../../Core/Inc -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/Config" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../Drivers/BSP/STM32746G-Discovery -I../../Drivers/BSP/Components/ft5336 -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I../../TouchGFX/generated/videos/include -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/ModbusIf/Inc" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/ModbusPlatformIf/Inc" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/ModbusService/Inc" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/RingBuffer/Inc" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/Standard" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/Standard/Inc" -I"C:/TouchGFX/4.18.1/touchgfx/lib/core/cortex_m7/gcc" -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Modbus-2f-ModbusIf-2f-Src

clean-Middlewares-2f-Modbus-2f-ModbusIf-2f-Src:
	-$(RM) ./Middlewares/Modbus/ModbusIf/Src/Modbus2Gpio.d ./Middlewares/Modbus/ModbusIf/Src/Modbus2Gpio.o ./Middlewares/Modbus/ModbusIf/Src/ModbusIf_Gpio.d ./Middlewares/Modbus/ModbusIf/Src/ModbusIf_Gpio.o ./Middlewares/Modbus/ModbusIf/Src/ModbusIf_Memory.d ./Middlewares/Modbus/ModbusIf/Src/ModbusIf_Memory.o ./Middlewares/Modbus/ModbusIf/Src/ModbusIf_Serial.d ./Middlewares/Modbus/ModbusIf/Src/ModbusIf_Serial.o ./Middlewares/Modbus/ModbusIf/Src/UARTCallback.d ./Middlewares/Modbus/ModbusIf/Src/UARTCallback.o

.PHONY: clean-Middlewares-2f-Modbus-2f-ModbusIf-2f-Src

