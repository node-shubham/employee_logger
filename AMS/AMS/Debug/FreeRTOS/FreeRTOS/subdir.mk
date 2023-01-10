################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/FreeRTOS/croutine.c \
../FreeRTOS/FreeRTOS/event_groups.c \
../FreeRTOS/FreeRTOS/list.c \
../FreeRTOS/FreeRTOS/queue.c \
../FreeRTOS/FreeRTOS/stream_buffer.c \
../FreeRTOS/FreeRTOS/tasks.c \
../FreeRTOS/FreeRTOS/timers.c 

OBJS += \
./FreeRTOS/FreeRTOS/croutine.o \
./FreeRTOS/FreeRTOS/event_groups.o \
./FreeRTOS/FreeRTOS/list.o \
./FreeRTOS/FreeRTOS/queue.o \
./FreeRTOS/FreeRTOS/stream_buffer.o \
./FreeRTOS/FreeRTOS/tasks.o \
./FreeRTOS/FreeRTOS/timers.o 

C_DEPS += \
./FreeRTOS/FreeRTOS/croutine.d \
./FreeRTOS/FreeRTOS/event_groups.d \
./FreeRTOS/FreeRTOS/list.d \
./FreeRTOS/FreeRTOS/queue.d \
./FreeRTOS/FreeRTOS/stream_buffer.d \
./FreeRTOS/FreeRTOS/tasks.d \
./FreeRTOS/FreeRTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/FreeRTOS/%.o FreeRTOS/FreeRTOS/%.su: ../FreeRTOS/FreeRTOS/%.c FreeRTOS/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/FreeRTOS" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/SEGGER/Config" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/SEGGER/SEGGER" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/SEGGER/OS" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/FreeRTOS/include" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/FreeRTOS/portable" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/FreeRTOS/FreeRTOS/portable/GCC/ARM_CM4F" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/mrfc522/inc" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/mrfc522/src" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/ssd1963/inc" -I"E:/UNDER DEVELOPMENT/ATTENDANCE MONITORING SYSTEM/AMS/AMS/ssd1963/src" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2f-FreeRTOS

clean-FreeRTOS-2f-FreeRTOS:
	-$(RM) ./FreeRTOS/FreeRTOS/croutine.d ./FreeRTOS/FreeRTOS/croutine.o ./FreeRTOS/FreeRTOS/croutine.su ./FreeRTOS/FreeRTOS/event_groups.d ./FreeRTOS/FreeRTOS/event_groups.o ./FreeRTOS/FreeRTOS/event_groups.su ./FreeRTOS/FreeRTOS/list.d ./FreeRTOS/FreeRTOS/list.o ./FreeRTOS/FreeRTOS/list.su ./FreeRTOS/FreeRTOS/queue.d ./FreeRTOS/FreeRTOS/queue.o ./FreeRTOS/FreeRTOS/queue.su ./FreeRTOS/FreeRTOS/stream_buffer.d ./FreeRTOS/FreeRTOS/stream_buffer.o ./FreeRTOS/FreeRTOS/stream_buffer.su ./FreeRTOS/FreeRTOS/tasks.d ./FreeRTOS/FreeRTOS/tasks.o ./FreeRTOS/FreeRTOS/tasks.su ./FreeRTOS/FreeRTOS/timers.d ./FreeRTOS/FreeRTOS/timers.o ./FreeRTOS/FreeRTOS/timers.su

.PHONY: clean-FreeRTOS-2f-FreeRTOS

