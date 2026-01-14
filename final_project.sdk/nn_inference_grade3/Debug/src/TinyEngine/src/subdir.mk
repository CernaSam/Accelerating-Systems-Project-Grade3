################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/TinyEngine/src/convolve_1x1_s8.c \
../src/TinyEngine/src/convolve_s8_kernel3_stride1_pad1.c \
../src/TinyEngine/src/convolve_s8_kernel3_stride2_padoffset1_oddch.c \
../src/TinyEngine/src/mat_mult_kernels.c \
../src/TinyEngine/src/reduce.c \
../src/TinyEngine/src/requantize.c \
../src/TinyEngine/src/softmax_int8.c 

OBJS += \
./src/TinyEngine/src/convolve_1x1_s8.o \
./src/TinyEngine/src/convolve_s8_kernel3_stride1_pad1.o \
./src/TinyEngine/src/convolve_s8_kernel3_stride2_padoffset1_oddch.o \
./src/TinyEngine/src/mat_mult_kernels.o \
./src/TinyEngine/src/reduce.o \
./src/TinyEngine/src/requantize.o \
./src/TinyEngine/src/softmax_int8.o 

C_DEPS += \
./src/TinyEngine/src/convolve_1x1_s8.d \
./src/TinyEngine/src/convolve_s8_kernel3_stride1_pad1.d \
./src/TinyEngine/src/convolve_s8_kernel3_stride2_padoffset1_oddch.d \
./src/TinyEngine/src/mat_mult_kernels.d \
./src/TinyEngine/src/reduce.d \
./src/TinyEngine/src/requantize.d \
./src/TinyEngine/src/softmax_int8.d 


# Each subdirectory must supply rules for building sources it contributes
src/TinyEngine/src/%.o: ../src/TinyEngine/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O3 -g3 -I"/home/deazon/final_project/final_project.sdk/nn_inference_grade3/src/TinyEngine/include" -I"/home/deazon/final_project/final_project.sdk/nn_inference_grade3/src/test_inputs" -I"/home/deazon/final_project/final_project.sdk/nn_inference_grade3/src/TinyEngine/third_party/CMSIS_NN/Include" -I"/home/deazon/final_project/final_project.sdk/nn_inference_grade3/src/Include" -I"/home/deazon/final_project/final_project.sdk/nn_inference_grade3/src/Source" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../nn_inference_grade3_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


