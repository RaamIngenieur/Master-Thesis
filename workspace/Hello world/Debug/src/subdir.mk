################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Hello\ world.cpp 

OBJS += \
./src/Hello\ world.o 

CPP_DEPS += \
./src/Hello\ world.d 


# Each subdirectory must supply rules for building sources it contributes
src/Hello\ world.o: ../src/Hello\ world.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Hello world.d" -MT"src/Hello\ world.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


