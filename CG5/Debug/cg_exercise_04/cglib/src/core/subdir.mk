################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cg_exercise_04/cglib/src/core/camera.cpp \
../cg_exercise_04/cglib/src/core/gui.cpp \
../cg_exercise_04/cglib/src/core/image.cpp \
../cg_exercise_04/cglib/src/core/obj_mesh.cpp \
../cg_exercise_04/cglib/src/core/parameters.cpp \
../cg_exercise_04/cglib/src/core/stb.cpp \
../cg_exercise_04/cglib/src/core/thread_pool.cpp \
../cg_exercise_04/cglib/src/core/timer.cpp 

OBJS += \
./cg_exercise_04/cglib/src/core/camera.o \
./cg_exercise_04/cglib/src/core/gui.o \
./cg_exercise_04/cglib/src/core/image.o \
./cg_exercise_04/cglib/src/core/obj_mesh.o \
./cg_exercise_04/cglib/src/core/parameters.o \
./cg_exercise_04/cglib/src/core/stb.o \
./cg_exercise_04/cglib/src/core/thread_pool.o \
./cg_exercise_04/cglib/src/core/timer.o 

CPP_DEPS += \
./cg_exercise_04/cglib/src/core/camera.d \
./cg_exercise_04/cglib/src/core/gui.d \
./cg_exercise_04/cglib/src/core/image.d \
./cg_exercise_04/cglib/src/core/obj_mesh.d \
./cg_exercise_04/cglib/src/core/parameters.d \
./cg_exercise_04/cglib/src/core/stb.d \
./cg_exercise_04/cglib/src/core/thread_pool.d \
./cg_exercise_04/cglib/src/core/timer.d 


# Each subdirectory must supply rules for building sources it contributes
cg_exercise_04/cglib/src/core/%.o: ../cg_exercise_04/cglib/src/core/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


