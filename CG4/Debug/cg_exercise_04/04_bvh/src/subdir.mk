################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cg_exercise_04/04_bvh/src/exercise_04.cpp \
../cg_exercise_04/04_bvh/src/main.cpp 

OBJS += \
./cg_exercise_04/04_bvh/src/exercise_04.o \
./cg_exercise_04/04_bvh/src/main.o 

CPP_DEPS += \
./cg_exercise_04/04_bvh/src/exercise_04.d \
./cg_exercise_04/04_bvh/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
cg_exercise_04/04_bvh/src/%.o: ../cg_exercise_04/04_bvh/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/ping/Documents/CG/CG4/cg_exercise_04/cglib/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


