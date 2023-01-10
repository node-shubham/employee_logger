################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mrfc522/src/mfrc522.c \
../mrfc522/src/mfrc522_config.c 

OBJS += \
./mrfc522/src/mfrc522.o \
./mrfc522/src/mfrc522_config.o 

C_DEPS += \
./mrfc522/src/mfrc522.d \
./mrfc522/src/mfrc522_config.d 


# Each subdirectory must supply rules for building sources it contributes
mrfc522/src/%.o mrfc522/src/%.su: ../mrfc522/src/%.c mrfc522/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/mrfc522/inc" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/mrfc522/src" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/ssd1963/inc" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-mrfc522-2f-src

clean-mrfc522-2f-src:
	-$(RM) ./mrfc522/src/mfrc522.d ./mrfc522/src/mfrc522.o ./mrfc522/src/mfrc522.su ./mrfc522/src/mfrc522_config.d ./mrfc522/src/mfrc522_config.o ./mrfc522/src/mfrc522_config.su

.PHONY: clean-mrfc522-2f-src

