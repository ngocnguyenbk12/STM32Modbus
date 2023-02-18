################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Modbus/Src/Modbus.c \
../Middlewares/Modbus/Src/Modbus_GuiHanlder.c \
../Middlewares/Modbus/Src/Modbus_Master.c \
../Middlewares/Modbus/Src/UARTCallback.c 

C_DEPS += \
./Middlewares/Modbus/Src/Modbus.d \
./Middlewares/Modbus/Src/Modbus_GuiHanlder.d \
./Middlewares/Modbus/Src/Modbus_Master.d \
./Middlewares/Modbus/Src/UARTCallback.d 

OBJS += \
./Middlewares/Modbus/Src/Modbus.o \
./Middlewares/Modbus/Src/Modbus_GuiHanlder.o \
./Middlewares/Modbus/Src/Modbus_Master.o \
./Middlewares/Modbus/Src/UARTCallback.o 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Modbus/Src/%.o: ../Middlewares/Modbus/Src/%.c Middlewares/Modbus/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../../Core/Inc -I"D:/LV_Modbus/Project/Git_Master_Implementation/Modbus_Bedside_Controller/STM32CubeIDE/Middlewares/Usr_Type" -I"D:/LV_Modbus/Project/Git_Master_Implementation/Modbus_Bedside_Controller/STM32CubeIDE/Middlewares/Modbus/Config" -I"D:/LV_Modbus/Project/Git_Master_Implementation/Modbus_Bedside_Controller/STM32CubeIDE/Middlewares/Modbus/Inc" -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32F7xx_HAL_Driver/Inc -I../../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../Drivers/BSP/Components/ft5336 -I../../Drivers/BSP/STM32746G-Discovery -I../../LIBJPEG/App -I../../LIBJPEG/Target -I../../Middlewares/Third_Party/LibJPEG/include -I../../TouchGFX/generated/videos/include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Modbus-2f-Src

clean-Middlewares-2f-Modbus-2f-Src:
	-$(RM) ./Middlewares/Modbus/Src/Modbus.d ./Middlewares/Modbus/Src/Modbus.o ./Middlewares/Modbus/Src/Modbus_GuiHanlder.d ./Middlewares/Modbus/Src/Modbus_GuiHanlder.o ./Middlewares/Modbus/Src/Modbus_Master.d ./Middlewares/Modbus/Src/Modbus_Master.o ./Middlewares/Modbus/Src/UARTCallback.d ./Middlewares/Modbus/Src/UARTCallback.o

.PHONY: clean-Middlewares-2f-Modbus-2f-Src

