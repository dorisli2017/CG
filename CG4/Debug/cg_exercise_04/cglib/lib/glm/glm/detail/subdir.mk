################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cg_exercise_04/cglib/lib/glm/glm/detail/dummy.cpp \
../cg_exercise_04/cglib/lib/glm/glm/detail/glm.cpp 

OBJS += \
./cg_exercise_04/cglib/lib/glm/glm/detail/dummy.o \
./cg_exercise_04/cglib/lib/glm/glm/detail/glm.o 

CPP_DEPS += \
./cg_exercise_04/cglib/lib/glm/glm/detail/dummy.d \
./cg_exercise_04/cglib/lib/glm/glm/detail/glm.d 


# Each subdirectory must supply rules for building sources it contributes
cg_exercise_04/cglib/lib/glm/glm/detail/%.o: ../cg_exercise_04/cglib/lib/glm/glm/detail/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/ping/Documents/CG/CG4/cg_exercise_04/cglib/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


