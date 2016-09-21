################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SoftwareSerialAttentionDevice/SoftwareSerialAttentionDevice.cpp 

OBJS += \
./SoftwareSerialAttentionDevice/SoftwareSerialAttentionDevice.o 

CPP_DEPS += \
./SoftwareSerialAttentionDevice/SoftwareSerialAttentionDevice.d 


# Each subdirectory must supply rules for building sources it contributes
SoftwareSerialAttentionDevice/%.o: ../SoftwareSerialAttentionDevice/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -I"/work/opensource/personal/microcontroller/arduino/ArduinoLibraries/ArduinoCore" -I"/work/opensource/personal/microcontroller/arduino/ArduinoLibraries/ArduinoCore/variants/standard" -I"/work/opensource/personal/microcontroller/arduino/ArduinoLibraries/ArduinoCore/libraries/SoftwareSerial/src" -I"/work/opensource/personal/microcontroller/arduino/ArduinoLibraries/ArduinoAttentionDevice/AttentionDevice" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


