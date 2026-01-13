################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Source/depthwise_kernel3x3_stride1_pad1_padoffset0_inplace_CHW.c \
../src/Source/depthwise_kernel3x3_stride2_pad0_padoffset1_inplace_CHW.c \
../src/Source/genModel.c 

OBJS += \
./src/Source/depthwise_kernel3x3_stride1_pad1_padoffset0_inplace_CHW.o \
./src/Source/depthwise_kernel3x3_stride2_pad0_padoffset1_inplace_CHW.o \
./src/Source/genModel.o 

C_DEPS += \
./src/Source/depthwise_kernel3x3_stride1_pad1_padoffset0_inplace_CHW.d \
./src/Source/depthwise_kernel3x3_stride2_pad0_padoffset1_inplace_CHW.d \
./src/Source/genModel.d 


# Each subdirectory must supply rules for building sources it contributes
src/Source/%.o: ../src/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O0 -g3 -I"C:\Users\Samo\Desktop\tutorial-1\tutorial-1.sdk\project-emenist-on-ps\src" -I"C:\Users\Samo\Desktop\tutorial-1\tutorial-1.sdk\project-emenist-on-ps\src\Include" -I"C:\Users\Samo\Desktop\tutorial-1\tutorial-1.sdk\project-emenist-on-ps\src\TinyEngine\include" -I"C:\Users\Samo\Desktop\tutorial-1\tutorial-1.sdk\project-emenist-on-ps\src\TinyEngine\third_party\CMSIS_NN\Include" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../project-emenist-on-ps_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


