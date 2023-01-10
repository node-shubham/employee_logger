################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../thirdparty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c 

OBJS += \
./thirdparty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o 

C_DEPS += \
./thirdparty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
thirdparty/SEGGER/Config/%.o thirdparty/SEGGER/Config/%.su: ../thirdparty/SEGGER/Config/%.c thirdparty/SEGGER/Config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/FreeRTOS" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/SEGGER/Config" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/SEGGER/OS" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/SEGGER/SEGGER" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/FreeRTOS/include" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Core/Inc -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/mrfc522/inc" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/mrfc522/src" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/ssd1963/inc" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-thirdparty-2f-SEGGER-2f-Config

clean-thirdparty-2f-SEGGER-2f-Config:
	-$(RM) ./thirdparty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d ./thirdparty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o ./thirdparty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.su

.PHONY: clean-thirdparty-2f-SEGGER-2f-Config

