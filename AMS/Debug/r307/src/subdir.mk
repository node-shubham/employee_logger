################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../r307/src/fpm.c \
../r307/src/r307_config.c \
../r307/src/uart_drv.c 

OBJS += \
./r307/src/fpm.o \
./r307/src/r307_config.o \
./r307/src/uart_drv.o 

C_DEPS += \
./r307/src/fpm.d \
./r307/src/r307_config.d \
./r307/src/uart_drv.d 


# Each subdirectory must supply rules for building sources it contributes
r307/src/%.o r307/src/%.su: ../r307/src/%.c r307/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"E:/STM WORKSPACE/WORK/AMS/24c256/inc" -I"E:/STM WORKSPACE/WORK/AMS/r307/inc" -I"E:/STM WORKSPACE/WORK/AMS/ThirdParty/SEGGER/Config" -I"E:/STM WORKSPACE/WORK/AMS/ThirdParty/SEGGER/OS" -I"E:/STM WORKSPACE/WORK/AMS/ThirdParty/SEGGER/SEGGER" -I"E:/STM WORKSPACE/WORK/AMS/ThirdParty/FreeRTOS" -I"E:/STM WORKSPACE/WORK/AMS/ThirdParty/FreeRTOS/include" -I"E:/STM WORKSPACE/WORK/AMS/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"E:/STM WORKSPACE/WORK/AMS/mrfc522/inc" -I"E:/STM WORKSPACE/WORK/AMS/mrfc522/src" -I"E:/STM WORKSPACE/WORK/AMS/ssd1963/inc" -I"E:/STM WORKSPACE/WORK/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-r307-2f-src

clean-r307-2f-src:
	-$(RM) ./r307/src/fpm.d ./r307/src/fpm.o ./r307/src/fpm.su ./r307/src/r307_config.d ./r307/src/r307_config.o ./r307/src/r307_config.su ./r307/src/uart_drv.d ./r307/src/uart_drv.o ./r307/src/uart_drv.su

.PHONY: clean-r307-2f-src

