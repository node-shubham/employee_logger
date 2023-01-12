################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ssd1963/src/display_config.c \
../ssd1963/src/fonts.c \
../ssd1963/src/ssd1963.c \
../ssd1963/src/xpt2046.c 

OBJS += \
./ssd1963/src/display_config.o \
./ssd1963/src/fonts.o \
./ssd1963/src/ssd1963.o \
./ssd1963/src/xpt2046.o 

C_DEPS += \
./ssd1963/src/display_config.d \
./ssd1963/src/fonts.d \
./ssd1963/src/ssd1963.d \
./ssd1963/src/xpt2046.d 


# Each subdirectory must supply rules for building sources it contributes
ssd1963/src/%.o ssd1963/src/%.su: ../ssd1963/src/%.c ssd1963/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"E:/GIT_AMS_FREERTOS/AMS/ThirdParty/SEGGER/Config" -I"E:/GIT_AMS_FREERTOS/AMS/ThirdParty/SEGGER/OS" -I"E:/GIT_AMS_FREERTOS/AMS/ThirdParty/SEGGER/SEGGER" -I"E:/GIT_AMS_FREERTOS/AMS/ThirdParty/FreeRTOS" -I"E:/GIT_AMS_FREERTOS/AMS/ThirdParty/FreeRTOS/include" -I"E:/GIT_AMS_FREERTOS/AMS/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"E:/GIT_AMS_FREERTOS/AMS/mrfc522/inc" -I"E:/GIT_AMS_FREERTOS/AMS/mrfc522/src" -I"E:/GIT_AMS_FREERTOS/AMS/ssd1963/inc" -I"E:/GIT_AMS_FREERTOS/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ssd1963-2f-src

clean-ssd1963-2f-src:
	-$(RM) ./ssd1963/src/display_config.d ./ssd1963/src/display_config.o ./ssd1963/src/display_config.su ./ssd1963/src/fonts.d ./ssd1963/src/fonts.o ./ssd1963/src/fonts.su ./ssd1963/src/ssd1963.d ./ssd1963/src/ssd1963.o ./ssd1963/src/ssd1963.su ./ssd1963/src/xpt2046.d ./ssd1963/src/xpt2046.o ./ssd1963/src/xpt2046.su

.PHONY: clean-ssd1963-2f-src

