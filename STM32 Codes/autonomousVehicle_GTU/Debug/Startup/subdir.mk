################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f407vgtx.s 

OBJS += \
./Startup/startup_stm32f407vgtx.o 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -I../ -I"C:/Users/Ahmet.Alperen.BULUT/STM32CubeIDE/workspace_1.0.1/autonomousVehicle_GTU/Middlewares/Third_Party/FreeRTOS" -I"C:/Users/Ahmet.Alperen.BULUT/STM32CubeIDE/workspace_1.0.1/autonomousVehicle_GTU/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/Ahmet.Alperen.BULUT/STM32CubeIDE/workspace_1.0.1/autonomousVehicle_GTU/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -x assembler-with-cpp --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

