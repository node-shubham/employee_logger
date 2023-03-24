################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../24c256/src/24c256.c 

OBJS += \
./24c256/src/24c256.o 

C_DEPS += \
./24c256/src/24c256.d 


# Each subdirectory must supply rules for building sources it contributes
24c256/src/%.o 24c256/src/%.su: ../24c256/src/%.c 24c256/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"E:/STM WORKSPACE/WORK/AMS/24c256/inc" -I"E:/STM WORKSPACE/WORK/AMS/r307/inc" -I"E:/STM WORKSPACE/WORK/AMS/ThirdParty/SEGGER/Config" -I"E:/STM WORKSPACE/WORK/AMS/ThirdParty/SEGGER/OS" -I"E:/STM WORKSPACE/WORK/AMS/ThirdParty/SEGGER/SEGGER" -I"E:/STM WORKSPACE/WORK/AMS/ThirdParty/FreeRTOS" -I"E:/STM WORKSPACE/WORK/AMS/ThirdParty/FreeRTOS/include" -I"E:/STM WORKSPACE/WORK/AMS/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"E:/STM WORKSPACE/WORK/AMS/mrfc522/inc" -I"E:/STM WORKSPACE/WORK/AMS/mrfc522/src" -I"E:/STM WORKSPACE/WORK/AMS/ssd1963/inc" -I"E:/STM WORKSPACE/WORK/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-24c256-2f-src

clean-24c256-2f-src:
	-$(RM) ./24c256/src/24c256.d ./24c256/src/24c256.o ./24c256/src/24c256.su

.PHONY: clean-24c256-2f-src

