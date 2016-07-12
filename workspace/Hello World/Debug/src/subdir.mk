################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Hello\ World.cpp 

OBJS += \
./src/Hello\ World.o 

CPP_DEPS += \
./src/Hello\ World.d 


# Each subdirectory must supply rules for building sources it contributes
src/Hello\ World.o: ../src/Hello\ World.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Hello World.d" -MT"src/Hello\ World.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


