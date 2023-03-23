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
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/24c256/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/r307/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/SEGGER/Config" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/SEGGER/OS" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/SEGGER/SEGGER" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/FreeRTOS" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/FreeRTOS/include" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/mrfc522/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/mrfc522/src" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ssd1963/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/it.cyclo ./Core/Src/it.d ./Core/Src/it.o ./Core/Src/it.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/msp.cyclo ./Core/Src/msp.d ./Core/Src/msp.o ./Core/Src/msp.su ./Core/Src/stm32f4xx_hal_timebase_tim.cyclo ./Core/Src/stm32f4xx_hal_timebase_tim.d ./Core/Src/stm32f4xx_hal_timebase_tim.o ./Core/Src/stm32f4xx_hal_timebase_tim.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/user_global.cyclo ./Core/Src/user_global.d ./Core/Src/user_global.o ./Core/Src/user_global.su

.PHONY: clean-Core-2f-Src

