################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32h750xbhx.s 

S_DEPS += \
./Core/Startup/startup_stm32h750xbhx.d 

OBJS += \
./Core/Startup/startup_stm32h750xbhx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/Drivers/BSP/STM32H750-DK-Discovery" -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/Drivers/BSP/Components/Common" -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/Drivers/BSP/Components/rk043fn48h" -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/Drivers/BSP/Components/wm8994" -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/Middlewares/ST/STM32_Audio/Addons/PDM/Inc" -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/Drivers/BSP/Components/mt25tl01g" -I"C:/Users/Martin/STM32CubeIDE/workspace_1.14.0/project/sdk/mcu/include" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32h750xbhx.d ./Core/Startup/startup_stm32h750xbhx.o

.PHONY: clean-Core-2f-Startup

