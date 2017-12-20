################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cg_exercise_04/cglib/lib/glfw/deps/getopt.c \
../cg_exercise_04/cglib/lib/glfw/deps/glad.c \
../cg_exercise_04/cglib/lib/glfw/deps/tinycthread.c 

OBJS += \
./cg_exercise_04/cglib/lib/glfw/deps/getopt.o \
./cg_exercise_04/cglib/lib/glfw/deps/glad.o \
./cg_exercise_04/cglib/lib/glfw/deps/tinycthread.o 

C_DEPS += \
./cg_exercise_04/cglib/lib/glfw/deps/getopt.d \
./cg_exercise_04/cglib/lib/glfw/deps/glad.d \
./cg_exercise_04/cglib/lib/glfw/deps/tinycthread.d 


# Each subdirectory must supply rules for building sources it contributes
cg_exercise_04/cglib/lib/glfw/deps/%.o: ../cg_exercise_04/cglib/lib/glfw/deps/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


