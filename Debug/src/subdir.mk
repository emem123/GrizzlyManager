################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GrizzlyHandler.cpp \
../src/GrizzlyModule.cpp \
../src/GrizzlyServer.cpp \
../src/main.cpp 

OBJS += \
./src/GrizzlyHandler.o \
./src/GrizzlyModule.o \
./src/GrizzlyServer.o \
./src/main.o 

CPP_DEPS += \
./src/GrizzlyHandler.d \
./src/GrizzlyModule.d \
./src/GrizzlyServer.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


