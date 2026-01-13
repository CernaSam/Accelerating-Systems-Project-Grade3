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
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O0 -g3 -I"C:\Users\Samo\Desktop\tutorial-1\tutorial-1.sdk\project-emenist-on-ps\src" -I"C:\Users\Samo\Desktop\tutorial-1\tutorial-1.sdk\project-emenist-on-ps\src\Include" -I"C:\Users\Samo\Desktop\tutorial-1\tutorial-1.sdk\project-emenist-on-ps\src\TinyEngine\include" -I"C:\Users\Samo\Desktop\tutorial-1\tutorial-1.sdk\project-emenist-on-ps\src\TinyEngine\third_party\CMSIS_NN\Include" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../project-emenist-on-ps_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


