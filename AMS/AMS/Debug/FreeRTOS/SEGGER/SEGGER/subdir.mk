################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/SEGGER/SEGGER/SEGGER_RTT.c \
../FreeRTOS/SEGGER/SEGGER/SEGGER_RTT_printf.c \
../FreeRTOS/SEGGER/SEGGER/SEGGER_SYSVIEW.c 

S_UPPER_SRCS += \
../FreeRTOS/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT.o \
./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o \
./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT_printf.o \
./FreeRTOS/SEGGER/SEGGER/SEGGER_SYSVIEW.o 

S_UPPER_DEPS += \
./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT.d \
./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT_printf.d \
./FreeRTOS/SEGGER/SEGGER/SEGGER_SYSVIEW.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/SEGGER/SEGGER/%.o FreeRTOS/SEGGER/SEGGER/%.su: ../FreeRTOS/SEGGER/SEGGER/%.c FreeRTOS/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/FreeRTOS" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/SEGGER/Config" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/SEGGER/SEGGER" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/SEGGER/OS" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/FreeRTOS/include" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/FreeRTOS/portable" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/FreeRTOS/portable/GCC/ARM_CM4F" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/mrfc522/inc" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/mrfc522/src" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/ssd1963/inc" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
FreeRTOS/SEGGER/SEGGER/%.o: ../FreeRTOS/SEGGER/SEGGER/%.S FreeRTOS/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/SEGGER/Config" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/SEGGER/SEGGER" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-FreeRTOS-2f-SEGGER-2f-SEGGER

clean-FreeRTOS-2f-SEGGER-2f-SEGGER:
	-$(RM) ./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT.d ./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT.o ./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT.su ./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d ./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o ./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT_printf.d ./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT_printf.o ./FreeRTOS/SEGGER/SEGGER/SEGGER_RTT_printf.su ./FreeRTOS/SEGGER/SEGGER/SEGGER_SYSVIEW.d ./FreeRTOS/SEGGER/SEGGER/SEGGER_SYSVIEW.o ./FreeRTOS/SEGGER/SEGGER/SEGGER_SYSVIEW.su

.PHONY: clean-FreeRTOS-2f-SEGGER-2f-SEGGER

