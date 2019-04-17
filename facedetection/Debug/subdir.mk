################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../check_result.cpp \
../face_detect_host.cpp \
../face_detect_sw.cpp \
../image.cpp \
../utils.cpp 

OBJS += \
./check_result.o \
./face_detect_host.o \
./face_detect_sw.o \
./image.o \
./utils.o 

CPP_DEPS += \
./check_result.d \
./face_detect_host.d \
./face_detect_sw.d \
./image.d \
./utils.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


