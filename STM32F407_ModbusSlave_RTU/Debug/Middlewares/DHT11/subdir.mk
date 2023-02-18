################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/DHT11/dht.c 

OBJS += \
./Middlewares/DHT11/dht.o 

C_DEPS += \
./Middlewares/DHT11/dht.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/DHT11/%.o: ../Middlewares/DHT11/%.c Middlewares/DHT11/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"D:/LV_Modbus/Project/Example/STM32F407_RTU_SLAVE/Middlewares/Modbus/Config" -I"D:/LV_Modbus/Project/Example/STM32F407_RTU_SLAVE/Middlewares/Modbus/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/LV_Modbus/Project/Example/STM32F407_RTU_SLAVE/Middlewares/DHT11" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-DHT11

clean-Middlewares-2f-DHT11:
	-$(RM) ./Middlewares/DHT11/dht.d ./Middlewares/DHT11/dht.o

.PHONY: clean-Middlewares-2f-DHT11

