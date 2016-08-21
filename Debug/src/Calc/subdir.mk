################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Calc/Equipment.cpp \
../src/Calc/HP_Mod.cpp \
../src/Calc/Stamina.cpp \
../src/Calc/getDistance.cpp 

OBJS += \
./src/Calc/Equipment.o \
./src/Calc/HP_Mod.o \
./src/Calc/Stamina.o \
./src/Calc/getDistance.o 

CPP_DEPS += \
./src/Calc/Equipment.d \
./src/Calc/HP_Mod.d \
./src/Calc/Stamina.d \
./src/Calc/getDistance.d 


# Each subdirectory must supply rules for building sources it contributes
src/Calc/%.o: ../src/Calc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DNO_ERROR_FILE -I/usr/include/mysql -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/Sharun_Dream/include" -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/libSharun/include" -O0 -g3 -Wall -c -fmessage-length=0 $(mysql_config --cflags) -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


