################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cg_exercise_04/cglib/src/rt/bvh.cpp \
../cg_exercise_04/cglib/src/rt/host_render.cpp \
../cg_exercise_04/cglib/src/rt/light.cpp \
../cg_exercise_04/cglib/src/rt/material.cpp \
../cg_exercise_04/cglib/src/rt/object.cpp \
../cg_exercise_04/cglib/src/rt/raytracing_context.cpp \
../cg_exercise_04/cglib/src/rt/raytracing_parameters.cpp \
../cg_exercise_04/cglib/src/rt/renderer.cpp \
../cg_exercise_04/cglib/src/rt/sampling_patterns.cpp \
../cg_exercise_04/cglib/src/rt/scene.cpp \
../cg_exercise_04/cglib/src/rt/texture.cpp \
../cg_exercise_04/cglib/src/rt/texture_mapping.cpp \
../cg_exercise_04/cglib/src/rt/transform.cpp \
../cg_exercise_04/cglib/src/rt/triangle_soup.cpp 

OBJS += \
./cg_exercise_04/cglib/src/rt/bvh.o \
./cg_exercise_04/cglib/src/rt/host_render.o \
./cg_exercise_04/cglib/src/rt/light.o \
./cg_exercise_04/cglib/src/rt/material.o \
./cg_exercise_04/cglib/src/rt/object.o \
./cg_exercise_04/cglib/src/rt/raytracing_context.o \
./cg_exercise_04/cglib/src/rt/raytracing_parameters.o \
./cg_exercise_04/cglib/src/rt/renderer.o \
./cg_exercise_04/cglib/src/rt/sampling_patterns.o \
./cg_exercise_04/cglib/src/rt/scene.o \
./cg_exercise_04/cglib/src/rt/texture.o \
./cg_exercise_04/cglib/src/rt/texture_mapping.o \
./cg_exercise_04/cglib/src/rt/transform.o \
./cg_exercise_04/cglib/src/rt/triangle_soup.o 

CPP_DEPS += \
./cg_exercise_04/cglib/src/rt/bvh.d \
./cg_exercise_04/cglib/src/rt/host_render.d \
./cg_exercise_04/cglib/src/rt/light.d \
./cg_exercise_04/cglib/src/rt/material.d \
./cg_exercise_04/cglib/src/rt/object.d \
./cg_exercise_04/cglib/src/rt/raytracing_context.d \
./cg_exercise_04/cglib/src/rt/raytracing_parameters.d \
./cg_exercise_04/cglib/src/rt/renderer.d \
./cg_exercise_04/cglib/src/rt/sampling_patterns.d \
./cg_exercise_04/cglib/src/rt/scene.d \
./cg_exercise_04/cglib/src/rt/texture.d \
./cg_exercise_04/cglib/src/rt/texture_mapping.d \
./cg_exercise_04/cglib/src/rt/transform.d \
./cg_exercise_04/cglib/src/rt/triangle_soup.d 


# Each subdirectory must supply rules for building sources it contributes
cg_exercise_04/cglib/src/rt/%.o: ../cg_exercise_04/cglib/src/rt/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/ping/Documents/CG/CG4/cg_exercise_04/cglib/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


