################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ssd1963/src/fonts.c \
../ssd1963/src/ssd1963.c \
../ssd1963/src/ssd1963_config.c \
../ssd1963/src/xpt2046.c 

OBJS += \
./ssd1963/src/fonts.o \
./ssd1963/src/ssd1963.o \
./ssd1963/src/ssd1963_config.o \
./ssd1963/src/xpt2046.o 

C_DEPS += \
./ssd1963/src/fonts.d \
./ssd1963/src/ssd1963.d \
./ssd1963/src/ssd1963_config.d \
./ssd1963/src/xpt2046.d 


# Each subdirectory must supply rules for building sources it contributes
ssd1963/src/%.o ssd1963/src/%.su ssd1963/src/%.cyclo: ../ssd1963/src/%.c ssd1963/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/24c256/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/r307/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/SEGGER/Config" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/SEGGER/OS" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/SEGGER/SEGGER" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/FreeRTOS" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/FreeRTOS/include" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/mrfc522/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/mrfc522/src" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ssd1963/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ssd1963-2f-src

clean-ssd1963-2f-src:
	-$(RM) ./ssd1963/src/fonts.cyclo ./ssd1963/src/fonts.d ./ssd1963/src/fonts.o ./ssd1963/src/fonts.su ./ssd1963/src/ssd1963.cyclo ./ssd1963/src/ssd1963.d ./ssd1963/src/ssd1963.o ./ssd1963/src/ssd1963.su ./ssd1963/src/ssd1963_config.cyclo ./ssd1963/src/ssd1963_config.d ./ssd1963/src/ssd1963_config.o ./ssd1963/src/ssd1963_config.su ./ssd1963/src/xpt2046.cyclo ./ssd1963/src/xpt2046.d ./ssd1963/src/xpt2046.o ./ssd1963/src/xpt2046.su

.PHONY: clean-ssd1963-2f-src

