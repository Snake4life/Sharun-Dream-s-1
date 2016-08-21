################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DB/DB_internal.cpp \
../src/DB/MySQL.cpp 

OBJS += \
./src/DB/DB_internal.o \
./src/DB/MySQL.o 

CPP_DEPS += \
./src/DB/DB_internal.d \
./src/DB/MySQL.d 


# Each subdirectory must supply rules for building sources it contributes
src/DB/%.o: ../src/DB/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DNO_ERROR_FILE -I/usr/include/mysql -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/Sharun_Dream/include" -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/libSharun/include" -O0 -g3 -Wall -c -fmessage-length=0 $(mysql_config --cflags) -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


