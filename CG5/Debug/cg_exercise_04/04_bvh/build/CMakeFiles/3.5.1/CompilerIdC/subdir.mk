################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cg_exercise_04/04_bvh/build/CMakeFiles/3.5.1/CompilerIdC/CMakeCCompilerId.c 

OBJS += \
./cg_exercise_04/04_bvh/build/CMakeFiles/3.5.1/CompilerIdC/CMakeCCompilerId.o 

C_DEPS += \
./cg_exercise_04/04_bvh/build/CMakeFiles/3.5.1/CompilerIdC/CMakeCCompilerId.d 


# Each subdirectory must supply rules for building sources it contributes
cg_exercise_04/04_bvh/build/CMakeFiles/3.5.1/CompilerIdC/%.o: ../cg_exercise_04/04_bvh/build/CMakeFiles/3.5.1/CompilerIdC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


