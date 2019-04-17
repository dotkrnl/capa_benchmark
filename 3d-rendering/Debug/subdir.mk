################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../3d_rendering_host.cpp \
../check_result.cpp \
../rendering_sw.cpp \
../utils.cpp 

OBJS += \
./3d_rendering_host.o \
./check_result.o \
./rendering_sw.o \
./utils.o 

CPP_DEPS += \
./3d_rendering_host.d \
./check_result.d \
./rendering_sw.d \
./utils.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


