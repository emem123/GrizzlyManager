################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/tools/ArrayList.cpp \
../src/tools/CSVWriter.cpp \
../src/tools/ConfigReader.cpp \
../src/tools/file.cpp 

OBJS += \
./src/tools/ArrayList.o \
./src/tools/CSVWriter.o \
./src/tools/ConfigReader.o \
./src/tools/file.o 

CPP_DEPS += \
./src/tools/ArrayList.d \
./src/tools/CSVWriter.d \
./src/tools/ConfigReader.d \
./src/tools/file.d 


# Each subdirectory must supply rules for building sources it contributes
src/tools/%.o: ../src/tools/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


