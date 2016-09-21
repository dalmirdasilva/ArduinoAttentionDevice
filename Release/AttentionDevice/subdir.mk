################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AttentionDevice/AttentionDevice.cpp 

OBJS += \
./AttentionDevice/AttentionDevice.o 

CPP_DEPS += \
./AttentionDevice/AttentionDevice.d 


# Each subdirectory must supply rules for building sources it contributes
AttentionDevice/%.o: ../AttentionDevice/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/work/opensource/personal/microcontroller/arduino/ArduinoLibraries/ArduinoCore" -I"/work/opensource/personal/microcontroller/arduino/ArduinoLibraries/ArduinoCore/variants/standard" -I"/work/opensource/personal/microcontroller/arduino/ArduinoLibraries/ArduinoCore/libraries/SoftwareSerial/src" -I"/work/opensource/personal/microcontroller/arduino/ArduinoLibraries/ArduinoAttentionDevice/AttentionDevice" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


