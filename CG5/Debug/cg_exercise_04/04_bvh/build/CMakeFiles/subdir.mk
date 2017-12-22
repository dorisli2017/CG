################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CXX_SRCS += \
../cg_exercise_04/04_bvh/build/CMakeFiles/feature_tests.cxx 

C_SRCS += \
../cg_exercise_04/04_bvh/build/CMakeFiles/feature_tests.c 

OBJS += \
./cg_exercise_04/04_bvh/build/CMakeFiles/feature_tests.o 

CXX_DEPS += \
./cg_exercise_04/04_bvh/build/CMakeFiles/feature_tests.d 

C_DEPS += \
./cg_exercise_04/04_bvh/build/CMakeFiles/feature_tests.d 


# Each subdirectory must supply rules for building sources it contributes
cg_exercise_04/04_bvh/build/CMakeFiles/%.o: ../cg_exercise_04/04_bvh/build/CMakeFiles/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cg_exercise_04/04_bvh/build/CMakeFiles/%.o: ../cg_exercise_04/04_bvh/build/CMakeFiles/%.cxx
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


