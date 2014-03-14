################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/webtools/WebTabBuilder.cpp 

OBJS += \
./src/webtools/WebTabBuilder.o 

CPP_DEPS += \
./src/webtools/WebTabBuilder.d 


# Each subdirectory must supply rules for building sources it contributes
src/webtools/%.o: ../src/webtools/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/lib/mongoose-5.2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


