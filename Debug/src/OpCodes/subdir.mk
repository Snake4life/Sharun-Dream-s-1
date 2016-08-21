################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/OpCodes/OpCode.cpp \
../src/OpCodes/OpCode_Gen.cpp 

OBJS += \
./src/OpCodes/OpCode.o \
./src/OpCodes/OpCode_Gen.o 

CPP_DEPS += \
./src/OpCodes/OpCode.d \
./src/OpCodes/OpCode_Gen.d 


# Each subdirectory must supply rules for building sources it contributes
src/OpCodes/%.o: ../src/OpCodes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DNO_ERROR_FILE -I/usr/include/mysql -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/Sharun_Dream/include" -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/libSharun/include" -O0 -g3 -Wall -c -fmessage-length=0 $(mysql_config --cflags) -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


