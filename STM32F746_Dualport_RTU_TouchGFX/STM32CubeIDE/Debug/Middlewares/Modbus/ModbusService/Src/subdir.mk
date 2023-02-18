################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Modbus/ModbusService/Src/Gui2Mb.c \
../Middlewares/Modbus/ModbusService/Src/Modbus2Gui.c \
../Middlewares/Modbus/ModbusService/Src/ModbusSync.c \
../Middlewares/Modbus/ModbusService/Src/Modbus_DeviceTrace.c \
../Middlewares/Modbus/ModbusService/Src/Modbus_Func.c \
../Middlewares/Modbus/ModbusService/Src/RTU_Master_Function.c \
../Middlewares/Modbus/ModbusService/Src/TCP_Slave_Function.c 

C_DEPS += \
./Middlewares/Modbus/ModbusService/Src/Gui2Mb.d \
./Middlewares/Modbus/ModbusService/Src/Modbus2Gui.d \
./Middlewares/Modbus/ModbusService/Src/ModbusSync.d \
./Middlewares/Modbus/ModbusService/Src/Modbus_DeviceTrace.d \
./Middlewares/Modbus/ModbusService/Src/Modbus_Func.d \
./Middlewares/Modbus/ModbusService/Src/RTU_Master_Function.d \
./Middlewares/Modbus/ModbusService/Src/TCP_Slave_Function.d 

OBJS += \
./Middlewares/Modbus/ModbusService/Src/Gui2Mb.o \
./Middlewares/Modbus/ModbusService/Src/Modbus2Gui.o \
./Middlewares/Modbus/ModbusService/Src/ModbusSync.o \
./Middlewares/Modbus/ModbusService/Src/Modbus_DeviceTrace.o \
./Middlewares/Modbus/ModbusService/Src/Modbus_Func.o \
./Middlewares/Modbus/ModbusService/Src/RTU_Master_Function.o \
./Middlewares/Modbus/ModbusService/Src/TCP_Slave_Function.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Modbus/ModbusService/Src/%.o: ../Middlewares/Modbus/ModbusService/Src/%.c Middlewares/Modbus/ModbusService/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F746xx -DDEBUG -c -I../../Core/Inc -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/Config" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../Drivers/BSP/STM32746G-Discovery -I../../Drivers/BSP/Components/ft5336 -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I../../TouchGFX/generated/videos/include -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/ModbusIf/Inc" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/ModbusPlatformIf/Inc" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/ModbusService/Inc" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/RingBuffer/Inc" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/Standard" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/Standard/Inc" -I"C:/TouchGFX/4.18.1/touchgfx/lib/core/cortex_m7/gcc" -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Modbus-2f-ModbusService-2f-Src

clean-Middlewares-2f-Modbus-2f-ModbusService-2f-Src:
	-$(RM) ./Middlewares/Modbus/ModbusService/Src/Gui2Mb.d ./Middlewares/Modbus/ModbusService/Src/Gui2Mb.o ./Middlewares/Modbus/ModbusService/Src/Modbus2Gui.d ./Middlewares/Modbus/ModbusService/Src/Modbus2Gui.o ./Middlewares/Modbus/ModbusService/Src/ModbusSync.d ./Middlewares/Modbus/ModbusService/Src/ModbusSync.o ./Middlewares/Modbus/ModbusService/Src/Modbus_DeviceTrace.d ./Middlewares/Modbus/ModbusService/Src/Modbus_DeviceTrace.o ./Middlewares/Modbus/ModbusService/Src/Modbus_Func.d ./Middlewares/Modbus/ModbusService/Src/Modbus_Func.o ./Middlewares/Modbus/ModbusService/Src/RTU_Master_Function.d ./Middlewares/Modbus/ModbusService/Src/RTU_Master_Function.o ./Middlewares/Modbus/ModbusService/Src/TCP_Slave_Function.d ./Middlewares/Modbus/ModbusService/Src/TCP_Slave_Function.o

.PHONY: clean-Middlewares-2f-Modbus-2f-ModbusService-2f-Src

