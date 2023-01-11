################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mfrc522/src/mfrc522.c \
../mfrc522/src/mfrc522_config.c 

OBJS += \
./mfrc522/src/mfrc522.o \
./mfrc522/src/mfrc522_config.o 

C_DEPS += \
./mfrc522/src/mfrc522.d \
./mfrc522/src/mfrc522_config.d 


# Each subdirectory must supply rules for building sources it contributes
mfrc522/src/%.o mfrc522/src/%.su: ../mfrc522/src/%.c mfrc522/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/ThirdParty/SEGGER/Config" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/ThirdParty/SEGGER/OS" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/ThirdParty/SEGGER/SEGGER" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/ThirdParty/FreeRTOS" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/ThirdParty/FreeRTOS/include" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/ssd1963/inc" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-mfrc522-2f-src

clean-mfrc522-2f-src:
	-$(RM) ./mfrc522/src/mfrc522.d ./mfrc522/src/mfrc522.o ./mfrc522/src/mfrc522.su ./mfrc522/src/mfrc522_config.d ./mfrc522/src/mfrc522_config.o ./mfrc522/src/mfrc522_config.su

.PHONY: clean-mfrc522-2f-src

