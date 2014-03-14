################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mongoose/MGHandler.cpp 

C_SRCS += \
../src/mongoose/mongoose.c 

OBJS += \
./src/mongoose/MGHandler.o \
./src/mongoose/mongoose.o 

C_DEPS += \
./src/mongoose/mongoose.d 

CPP_DEPS += \
./src/mongoose/MGHandler.d 


# Each subdirectory must supply rules for building sources it contributes
src/mongoose/%.o: ../src/mongoose/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/lib/mongoose-5.2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/mongoose/%.o: ../src/mongoose/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/lib/mongoose-5.2" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


