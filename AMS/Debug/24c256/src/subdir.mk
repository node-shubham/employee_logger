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
24c256/src/%.o 24c256/src/%.su 24c256/src/%.cyclo: ../24c256/src/%.c 24c256/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/24c256/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/r307/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/SEGGER/Config" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/SEGGER/OS" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/SEGGER/SEGGER" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/FreeRTOS" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/FreeRTOS/include" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/mrfc522/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/mrfc522/src" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ssd1963/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-24c256-2f-src

clean-24c256-2f-src:
	-$(RM) ./24c256/src/24c256.cyclo ./24c256/src/24c256.d ./24c256/src/24c256.o ./24c256/src/24c256.su

.PHONY: clean-24c256-2f-src

