################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include cg_exercise_04/cglib/src/rt/subdir.mk
-include cg_exercise_04/cglib/src/imgui/subdir.mk
-include cg_exercise_04/cglib/src/core/subdir.mk
-include cg_exercise_04/cglib/lib/glm/glm/detail/subdir.mk
-include cg_exercise_04/cglib/lib/glfw/src/subdir.mk
-include cg_exercise_04/cglib/lib/glfw/examples/subdir.mk
-include cg_exercise_04/cglib/lib/glfw/deps/subdir.mk
-include cg_exercise_04/cglib/lib/glew/src/subdir.mk
-include cg_exercise_04/cglib/lib/glew/build/cmake/testbuild/subdir.mk
-include cg_exercise_04/cglib/lib/glew/auto/src/subdir.mk
-include cg_exercise_04/cglib/build/cglib/CMakeFiles/cglib_cg_4.dir/src/rt/subdir.mk
-include cg_exercise_04/cglib/build/cglib/CMakeFiles/cglib_cg_4.dir/src/imgui/subdir.mk
-include cg_exercise_04/cglib/build/cglib/CMakeFiles/cglib_cg_4.dir/src/core/subdir.mk
-include cg_exercise_04/04_bvh/src/subdir.mk
-include cg_exercise_04/04_bvh/build/CMakeFiles/cg.dir/src/subdir.mk
-include cg_exercise_04/04_bvh/build/CMakeFiles/3.5.1/CompilerIdCXX/subdir.mk
-include cg_exercise_04/04_bvh/build/CMakeFiles/3.5.1/CompilerIdC/subdir.mk
-include cg_exercise_04/04_bvh/build/CMakeFiles/subdir.mk
-include cg_exercise_04/04_bvh/assets/crytek-sponza/subdir.mk
-include cg_exercise_04/04_bvh/assets/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: CG4

# Tool invocations
CG4: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++  -o "CG4" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) CG4
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
