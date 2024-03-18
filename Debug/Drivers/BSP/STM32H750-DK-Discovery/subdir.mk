################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery.c \
../Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_audio.c \
../Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_bus.c \
../Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_lcd.c \
../Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_qspi.c \
../Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_sdram.c \
../Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_ts.c 

C_DEPS += \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery.d \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_audio.d \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_bus.d \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_lcd.d \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_qspi.d \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_sdram.d \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_ts.d 

OBJS += \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery.o \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_audio.o \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_bus.o \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_lcd.o \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_qspi.o \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_sdram.o \
./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_ts.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32H750-DK-Discovery/%.o Drivers/BSP/STM32H750-DK-Discovery/%.su Drivers/BSP/STM32H750-DK-Discovery/%.cyclo: ../Drivers/BSP/STM32H750-DK-Discovery/%.c Drivers/BSP/STM32H750-DK-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -D__PV_LANGUAGE_ENGLISH__ -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../TouchGFX/App -I../TouchGFX/target/generated -I../TouchGFX/target -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/Drivers/BSP/STM32H750-DK-Discovery" -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/Drivers/BSP/Components/Common" -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/Drivers/BSP/Components/rk043fn48h" -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/Drivers/BSP/Components/wm8994" -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/Drivers/BSP/Components/mt25tl01g" -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/sdk/mcu/include" -I../LIBJPEG/App -I../LIBJPEG/Target -I../Utilities/JPEG -I../Middlewares/Third_Party/LibJPEG/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32H750-2d-DK-2d-Discovery

clean-Drivers-2f-BSP-2f-STM32H750-2d-DK-2d-Discovery:
	-$(RM) ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery.cyclo ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery.d ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery.o ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery.su ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_audio.cyclo ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_audio.d ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_audio.o ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_audio.su ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_bus.cyclo ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_bus.d ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_bus.o ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_bus.su ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_lcd.cyclo ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_lcd.d ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_lcd.o ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_lcd.su ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_qspi.cyclo ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_qspi.d ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_qspi.o ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_qspi.su ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_sdram.cyclo ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_sdram.d ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_sdram.o ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_sdram.su ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_ts.cyclo ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_ts.d ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_ts.o ./Drivers/BSP/STM32H750-DK-Discovery/stm32h750b_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32H750-2d-DK-2d-Discovery

