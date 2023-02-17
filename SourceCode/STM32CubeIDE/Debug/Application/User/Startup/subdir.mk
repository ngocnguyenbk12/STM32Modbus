################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Application/User/Startup/startup_stm32f746nghx.s 

S_DEPS += \
./Application/User/Startup/startup_stm32f746nghx.d 

OBJS += \
./Application/User/Startup/startup_stm32f746nghx.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Startup/%.o: ../Application/User/Startup/%.s Application/User/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/ModbusIf/Inc" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/ModbusPlatformIf/Inc" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/ModbusService/Inc" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/RingBuffer/Inc" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/Standard" -I"D:/Job/ModbusBedsideController/FinalProject/Modbus_Bedside_Controller_Dualport/STM32CubeIDE/Middlewares/Modbus/Standard/Inc" -I"C:/TouchGFX/4.18.1/touchgfx/lib/core/cortex_m7/gcc" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Application-2f-User-2f-Startup

clean-Application-2f-User-2f-Startup:
	-$(RM) ./Application/User/Startup/startup_stm32f746nghx.d ./Application/User/Startup/startup_stm32f746nghx.o

.PHONY: clean-Application-2f-User-2f-Startup

