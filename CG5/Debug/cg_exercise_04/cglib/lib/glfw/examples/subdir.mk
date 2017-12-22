################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cg_exercise_04/cglib/lib/glfw/examples/boing.c \
../cg_exercise_04/cglib/lib/glfw/examples/gears.c \
../cg_exercise_04/cglib/lib/glfw/examples/heightmap.c \
../cg_exercise_04/cglib/lib/glfw/examples/particles.c \
../cg_exercise_04/cglib/lib/glfw/examples/simple.c \
../cg_exercise_04/cglib/lib/glfw/examples/splitview.c \
../cg_exercise_04/cglib/lib/glfw/examples/wave.c 

OBJS += \
./cg_exercise_04/cglib/lib/glfw/examples/boing.o \
./cg_exercise_04/cglib/lib/glfw/examples/gears.o \
./cg_exercise_04/cglib/lib/glfw/examples/heightmap.o \
./cg_exercise_04/cglib/lib/glfw/examples/particles.o \
./cg_exercise_04/cglib/lib/glfw/examples/simple.o \
./cg_exercise_04/cglib/lib/glfw/examples/splitview.o \
./cg_exercise_04/cglib/lib/glfw/examples/wave.o 

C_DEPS += \
./cg_exercise_04/cglib/lib/glfw/examples/boing.d \
./cg_exercise_04/cglib/lib/glfw/examples/gears.d \
./cg_exercise_04/cglib/lib/glfw/examples/heightmap.d \
./cg_exercise_04/cglib/lib/glfw/examples/particles.d \
./cg_exercise_04/cglib/lib/glfw/examples/simple.d \
./cg_exercise_04/cglib/lib/glfw/examples/splitview.d \
./cg_exercise_04/cglib/lib/glfw/examples/wave.d 


# Each subdirectory must supply rules for building sources it contributes
cg_exercise_04/cglib/lib/glfw/examples/%.o: ../cg_exercise_04/cglib/lib/glfw/examples/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


