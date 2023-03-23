################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c 

OBJS += \
./ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o 

C_DEPS += \
./ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
ThirdParty/SEGGER/Config/%.o ThirdParty/SEGGER/Config/%.su ThirdParty/SEGGER/Config/%.cyclo: ../ThirdParty/SEGGER/Config/%.c ThirdParty/SEGGER/Config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/24c256/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/r307/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/SEGGER/Config" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/SEGGER/OS" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/SEGGER/SEGGER" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/FreeRTOS" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/FreeRTOS/include" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/mrfc522/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/mrfc522/src" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ssd1963/inc" -I"C:/Users/shubh/OneDrive/Desktop/Workspace/FINGERPRINT/AMS v1.4.5/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O3 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-ThirdParty-2f-SEGGER-2f-Config

clean-ThirdParty-2f-SEGGER-2f-Config:
	-$(RM) ./ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.cyclo ./ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d ./ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o ./ThirdParty/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.su

.PHONY: clean-ThirdParty-2f-SEGGER-2f-Config

