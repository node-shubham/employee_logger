################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../thirdparty/SEGGER/SEGGER/SEGGER_RTT.c \
../thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.c \
../thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.c 

S_UPPER_SRCS += \
../thirdparty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./thirdparty/SEGGER/SEGGER/SEGGER_RTT.o \
./thirdparty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o \
./thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.o \
./thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.o 

S_UPPER_DEPS += \
./thirdparty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./thirdparty/SEGGER/SEGGER/SEGGER_RTT.d \
./thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.d \
./thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.d 


# Each subdirectory must supply rules for building sources it contributes
thirdparty/SEGGER/SEGGER/%.o thirdparty/SEGGER/SEGGER/%.su: ../thirdparty/SEGGER/SEGGER/%.c thirdparty/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/FreeRTOS" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/SEGGER/Config" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/SEGGER/OS" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/SEGGER/SEGGER" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/FreeRTOS/include" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/FreeRTOS/portable/GCC/ARM_CM4F" -I../Core/Inc -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/mrfc522/inc" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/mrfc522/src" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/ssd1963/inc" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
thirdparty/SEGGER/SEGGER/%.o: ../thirdparty/SEGGER/SEGGER/%.S thirdparty/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/SEGGER/Config" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/thirdparty/SEGGER/SEGGER" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-thirdparty-2f-SEGGER-2f-SEGGER

clean-thirdparty-2f-SEGGER-2f-SEGGER:
	-$(RM) ./thirdparty/SEGGER/SEGGER/SEGGER_RTT.d ./thirdparty/SEGGER/SEGGER/SEGGER_RTT.o ./thirdparty/SEGGER/SEGGER/SEGGER_RTT.su ./thirdparty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d ./thirdparty/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o ./thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.d ./thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.o ./thirdparty/SEGGER/SEGGER/SEGGER_RTT_printf.su ./thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.d ./thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.o ./thirdparty/SEGGER/SEGGER/SEGGER_SYSVIEW.su

.PHONY: clean-thirdparty-2f-SEGGER-2f-SEGGER

