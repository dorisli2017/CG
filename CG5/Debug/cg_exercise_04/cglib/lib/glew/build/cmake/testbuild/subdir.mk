################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cg_exercise_04/cglib/lib/glew/build/cmake/testbuild/main.c 

OBJS += \
./cg_exercise_04/cglib/lib/glew/build/cmake/testbuild/main.o 

C_DEPS += \
./cg_exercise_04/cglib/lib/glew/build/cmake/testbuild/main.d 


# Each subdirectory must supply rules for building sources it contributes
cg_exercise_04/cglib/lib/glew/build/cmake/testbuild/%.o: ../cg_exercise_04/cglib/lib/glew/build/cmake/testbuild/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


