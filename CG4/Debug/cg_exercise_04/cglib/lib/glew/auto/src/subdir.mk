################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cg_exercise_04/cglib/lib/glew/auto/src/glew_head.c \
../cg_exercise_04/cglib/lib/glew/auto/src/glew_init_gl.c \
../cg_exercise_04/cglib/lib/glew/auto/src/glew_init_glx.c \
../cg_exercise_04/cglib/lib/glew/auto/src/glew_init_tail.c \
../cg_exercise_04/cglib/lib/glew/auto/src/glew_init_wgl.c \
../cg_exercise_04/cglib/lib/glew/auto/src/glew_str_glx.c \
../cg_exercise_04/cglib/lib/glew/auto/src/glew_str_head.c \
../cg_exercise_04/cglib/lib/glew/auto/src/glew_str_tail.c \
../cg_exercise_04/cglib/lib/glew/auto/src/glew_str_wgl.c \
../cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_gl.c \
../cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_glx.c \
../cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_head.c \
../cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_tail.c \
../cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_wgl.c 

OBJS += \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_head.o \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_init_gl.o \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_init_glx.o \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_init_tail.o \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_init_wgl.o \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_str_glx.o \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_str_head.o \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_str_tail.o \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_str_wgl.o \
./cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_gl.o \
./cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_glx.o \
./cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_head.o \
./cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_tail.o \
./cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_wgl.o 

C_DEPS += \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_head.d \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_init_gl.d \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_init_glx.d \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_init_tail.d \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_init_wgl.d \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_str_glx.d \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_str_head.d \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_str_tail.d \
./cg_exercise_04/cglib/lib/glew/auto/src/glew_str_wgl.d \
./cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_gl.d \
./cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_glx.d \
./cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_head.d \
./cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_tail.d \
./cg_exercise_04/cglib/lib/glew/auto/src/glewinfo_wgl.d 


# Each subdirectory must supply rules for building sources it contributes
cg_exercise_04/cglib/lib/glew/auto/src/%.o: ../cg_exercise_04/cglib/lib/glew/auto/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


