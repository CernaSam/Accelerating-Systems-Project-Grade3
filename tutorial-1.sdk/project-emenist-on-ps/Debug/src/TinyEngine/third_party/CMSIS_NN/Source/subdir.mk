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
	@echo 'Invoking: ARM v7 g++ compiler'
	arm-none-eabi-g++ -Wall -O0 -g3 -I"C:\Users\Samo\Desktop\tutorial-1\tutorial-1.sdk\project-emenist-on-ps\src" -I"C:\Users\Samo\Desktop\tutorial-1\tutorial-1.sdk\project-emenist-on-ps\src\Include" -I"C:\Users\Samo\Desktop\tutorial-1\tutorial-1.sdk\project-emenist-on-ps\src\TinyEngine\include" -I"C:\Users\Samo\Desktop\tutorial-1\tutorial-1.sdk\project-emenist-on-ps\src\TinyEngine\third_party\CMSIS_NN\Include" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../project-emenist-on-ps_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


