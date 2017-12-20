################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cg_exercise_04/cglib/src/imgui/imgui.cpp \
../cg_exercise_04/cglib/src/imgui/imgui_draw.cpp \
../cg_exercise_04/cglib/src/imgui/imgui_impl_glfw_gl2.cpp \
../cg_exercise_04/cglib/src/imgui/imgui_impl_glfw_gl3.cpp \
../cg_exercise_04/cglib/src/imgui/imgui_orient.cpp 

OBJS += \
./cg_exercise_04/cglib/src/imgui/imgui.o \
./cg_exercise_04/cglib/src/imgui/imgui_draw.o \
./cg_exercise_04/cglib/src/imgui/imgui_impl_glfw_gl2.o \
./cg_exercise_04/cglib/src/imgui/imgui_impl_glfw_gl3.o \
./cg_exercise_04/cglib/src/imgui/imgui_orient.o 

CPP_DEPS += \
./cg_exercise_04/cglib/src/imgui/imgui.d \
./cg_exercise_04/cglib/src/imgui/imgui_draw.d \
./cg_exercise_04/cglib/src/imgui/imgui_impl_glfw_gl2.d \
./cg_exercise_04/cglib/src/imgui/imgui_impl_glfw_gl3.d \
./cg_exercise_04/cglib/src/imgui/imgui_orient.d 


# Each subdirectory must supply rules for building sources it contributes
cg_exercise_04/cglib/src/imgui/%.o: ../cg_exercise_04/cglib/src/imgui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/home/ping/Documents/CG/CG4/cg_exercise_04/cglib/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


