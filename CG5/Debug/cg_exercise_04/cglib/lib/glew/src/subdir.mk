################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cg_exercise_04/cglib/lib/glew/src/glew.c \
../cg_exercise_04/cglib/lib/glew/src/glewinfo.c \
../cg_exercise_04/cglib/lib/glew/src/visualinfo.c 

OBJS += \
./cg_exercise_04/cglib/lib/glew/src/glew.o \
./cg_exercise_04/cglib/lib/glew/src/glewinfo.o \
./cg_exercise_04/cglib/lib/glew/src/visualinfo.o 

C_DEPS += \
./cg_exercise_04/cglib/lib/glew/src/glew.d \
./cg_exercise_04/cglib/lib/glew/src/glewinfo.d \
./cg_exercise_04/cglib/lib/glew/src/visualinfo.d 


# Each subdirectory must supply rules for building sources it contributes
cg_exercise_04/cglib/lib/glew/src/%.o: ../cg_exercise_04/cglib/lib/glew/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


