################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/SEGGER/Rec/segger_uart.c 

OBJS += \
./FreeRTOS/SEGGER/Rec/segger_uart.o 

C_DEPS += \
./FreeRTOS/SEGGER/Rec/segger_uart.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/SEGGER/Rec/%.o FreeRTOS/SEGGER/Rec/%.su: ../FreeRTOS/SEGGER/Rec/%.c FreeRTOS/SEGGER/Rec/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/FreeRTOS" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/SEGGER/Config" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/SEGGER/SEGGER" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/SEGGER/OS" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/FreeRTOS/include" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/FreeRTOS/portable" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/FreeRTOS/portable/GCC/ARM_CM4F" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/mrfc522/inc" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/mrfc522/src" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/ssd1963/inc" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2f-SEGGER-2f-Rec

clean-FreeRTOS-2f-SEGGER-2f-Rec:
	-$(RM) ./FreeRTOS/SEGGER/Rec/segger_uart.d ./FreeRTOS/SEGGER/Rec/segger_uart.o ./FreeRTOS/SEGGER/Rec/segger_uart.su

.PHONY: clean-FreeRTOS-2f-SEGGER-2f-Rec

