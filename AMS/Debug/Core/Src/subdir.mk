################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/it.c \
../Core/Src/main.c \
../Core/Src/msp.c \
../Core/Src/stm32f4xx_hal_timebase_tim.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/user_global.c 

OBJS += \
./Core/Src/it.o \
./Core/Src/main.o \
./Core/Src/msp.o \
./Core/Src/stm32f4xx_hal_timebase_tim.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/user_global.o 

C_DEPS += \
./Core/Src/it.d \
./Core/Src/main.d \
./Core/Src/msp.d \
./Core/Src/stm32f4xx_hal_timebase_tim.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/user_global.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"E:/RTOS_AMS1/AMS/ThirdParty/SEGGER/Config" -I"E:/RTOS_AMS1/AMS/ThirdParty/SEGGER/OS" -I"E:/RTOS_AMS1/AMS/ThirdParty/SEGGER/SEGGER" -I"E:/RTOS_AMS1/AMS/ThirdParty/FreeRTOS" -I"E:/RTOS_AMS1/AMS/ThirdParty/FreeRTOS/include" -I"E:/RTOS_AMS1/AMS/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"E:/RTOS_AMS1/AMS/mrfc522/inc" -I"E:/RTOS_AMS1/AMS/mrfc522/src" -I"E:/RTOS_AMS1/AMS/ssd1963/inc" -I"E:/RTOS_AMS1/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/it.d ./Core/Src/it.o ./Core/Src/it.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/msp.d ./Core/Src/msp.o ./Core/Src/msp.su ./Core/Src/stm32f4xx_hal_timebase_tim.d ./Core/Src/stm32f4xx_hal_timebase_tim.o ./Core/Src/stm32f4xx_hal_timebase_tim.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/user_global.d ./Core/Src/user_global.o ./Core/Src/user_global.su

.PHONY: clean-Core-2f-Src

