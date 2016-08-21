################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DB/2_Ram/2R_Equipments.cpp \
../src/DB/2_Ram/2R_Friendly.cpp \
../src/DB/2_Ram/2R_Items.cpp \
../src/DB/2_Ram/2R_Monsters.cpp \
../src/DB/2_Ram/2R_Mounts.cpp \
../src/DB/2_Ram/2R_Zones.cpp 

OBJS += \
./src/DB/2_Ram/2R_Equipments.o \
./src/DB/2_Ram/2R_Friendly.o \
./src/DB/2_Ram/2R_Items.o \
./src/DB/2_Ram/2R_Monsters.o \
./src/DB/2_Ram/2R_Mounts.o \
./src/DB/2_Ram/2R_Zones.o 

CPP_DEPS += \
./src/DB/2_Ram/2R_Equipments.d \
./src/DB/2_Ram/2R_Friendly.d \
./src/DB/2_Ram/2R_Items.d \
./src/DB/2_Ram/2R_Monsters.d \
./src/DB/2_Ram/2R_Mounts.d \
./src/DB/2_Ram/2R_Zones.d 


# Each subdirectory must supply rules for building sources it contributes
src/DB/2_Ram/%.o: ../src/DB/2_Ram/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DNO_ERROR_FILE -I/usr/include/mysql -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/Sharun_Dream/include" -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/libSharun/include" -O0 -g3 -Wall -c -fmessage-length=0 $(mysql_config --cflags) -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


