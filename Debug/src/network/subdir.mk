################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/network/BroadcastD.cpp \
../src/network/GameD.cpp \
../src/network/HttpD.cpp \
../src/network/RegenD.cpp \
../src/network/connexion.cpp \
../src/network/http.cpp \
../src/network/network.cpp \
../src/network/packet_internal.cpp 

OBJS += \
./src/network/BroadcastD.o \
./src/network/GameD.o \
./src/network/HttpD.o \
./src/network/RegenD.o \
./src/network/connexion.o \
./src/network/http.o \
./src/network/network.o \
./src/network/packet_internal.o 

CPP_DEPS += \
./src/network/BroadcastD.d \
./src/network/GameD.d \
./src/network/HttpD.d \
./src/network/RegenD.d \
./src/network/connexion.d \
./src/network/http.d \
./src/network/network.d \
./src/network/packet_internal.d 


# Each subdirectory must supply rules for building sources it contributes
src/network/%.o: ../src/network/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DNO_ERROR_FILE -I/usr/include/mysql -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/Sharun_Dream/include" -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/libSharun/include" -O0 -g3 -Wall -c -fmessage-length=0 $(mysql_config --cflags) -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


