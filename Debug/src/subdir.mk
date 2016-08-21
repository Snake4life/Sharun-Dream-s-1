################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/char16_t.cpp \
../src/player.cpp \
../src/pthread_sub.cpp \
../src/utils.cpp 

OBJS += \
./src/char16_t.o \
./src/player.o \
./src/pthread_sub.o \
./src/utils.o 

CPP_DEPS += \
./src/char16_t.d \
./src/player.d \
./src/pthread_sub.d \
./src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/libSharun/include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


