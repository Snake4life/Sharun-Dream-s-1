################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/DEBUG.cpp \
../src/Fixed_Thread.cpp \
../src/Plugins.cpp \
../src/World.cpp \
../src/item_internal.cpp \
../src/main.cpp \
../src/mount_internal.cpp \
../src/npc_internal.cpp \
../src/player_internal.cpp \
../src/regen_internal.cpp \
../src/settings.cpp \
../src/spawn_internal.cpp \
../src/thread.cpp \
../src/win32_IconSysTray.cpp 

OBJS += \
./src/DEBUG.o \
./src/Fixed_Thread.o \
./src/Plugins.o \
./src/World.o \
./src/item_internal.o \
./src/main.o \
./src/mount_internal.o \
./src/npc_internal.o \
./src/player_internal.o \
./src/regen_internal.o \
./src/settings.o \
./src/spawn_internal.o \
./src/thread.o \
./src/win32_IconSysTray.o 

CPP_DEPS += \
./src/DEBUG.d \
./src/Fixed_Thread.d \
./src/Plugins.d \
./src/World.d \
./src/item_internal.d \
./src/main.d \
./src/mount_internal.d \
./src/npc_internal.d \
./src/player_internal.d \
./src/regen_internal.d \
./src/settings.d \
./src/spawn_internal.d \
./src/thread.d \
./src/win32_IconSysTray.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -DNO_ERROR_FILE -I/usr/include/mysql -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/Sharun_Dream/include" -I"/mnt/Data/Programmations/My_Apps/Sharun_Dream/libSharun/include" -O0 -g3 -Wall -c -fmessage-length=0 $(mysql_config --cflags) -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


