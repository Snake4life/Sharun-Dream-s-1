################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/network/teraCrypt/Cryptor.cpp \
../src/network/teraCrypt/CryptorKey.cpp \
../src/network/teraCrypt/Session.cpp \
../src/network/teraCrypt/Sha.cpp 

OBJS += \
./src/network/teraCrypt/Cryptor.o \
./src/network/teraCrypt/CryptorKey.o \
./src/network/teraCrypt/Session.o \
./src/network/teraCrypt/Sha.o 

CPP_DEPS += \
./src/network/teraCrypt/Cryptor.d \
./src/network/teraCrypt/CryptorKey.d \
./src/network/teraCrypt/Session.d \
./src/network/teraCrypt/Sha.d 


# Each subdirectory must supply rules for building sources it contributes
src/network/teraCrypt/%.o: ../src/network/teraCrypt/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DNO_ERROR_FILE -I/usr/include/mysql -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/Sharun_Dream/include" -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/libSharun/include" -O0 -g3 -Wall -c -fmessage-length=0 $(mysql_config --cflags) -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


