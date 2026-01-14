################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/TinyEngine/third_party/CMSIS_NN/Source/arm_softmax_s8.c 

OBJS += \
./src/TinyEngine/third_party/CMSIS_NN/Source/arm_softmax_s8.o 

C_DEPS += \
./src/TinyEngine/third_party/CMSIS_NN/Source/arm_softmax_s8.d 


# Each subdirectory must supply rules for building sources it contributes
src/TinyEngine/third_party/CMSIS_NN/Source/%.o: ../src/TinyEngine/third_party/CMSIS_NN/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O3 -g3 -I"/home/deazon/final_project/final_project.sdk/nn_inference_grade3/src/TinyEngine/include" -I"/home/deazon/final_project/final_project.sdk/nn_inference_grade3/src/test_inputs" -I"/home/deazon/final_project/final_project.sdk/nn_inference_grade3/src/TinyEngine/third_party/CMSIS_NN/Include" -I"/home/deazon/final_project/final_project.sdk/nn_inference_grade3/src/Include" -I"/home/deazon/final_project/final_project.sdk/nn_inference_grade3/src/Source" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../nn_inference_grade3_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


