################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
SYSCFG_SRCS += \
../empty.syscfg 

C_SRCS += \
../LED_control.c \
./ti_msp_dl_config.c \
/Applications/ti/mspm0_sdk_2_09_00_01/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c \
../frequency_measurement.c \
../other_oscillators.c \
../rc_oscillator.c 

GEN_CMDS += \
./device_linker.cmd 

GEN_FILES += \
./device_linker.cmd \
./device.opt \
./ti_msp_dl_config.c 

C_DEPS += \
./LED_control.d \
./ti_msp_dl_config.d \
./startup_mspm0g350x_ticlang.d \
./frequency_measurement.d \
./other_oscillators.d \
./rc_oscillator.d 

GEN_OPTS += \
./device.opt 

OBJS += \
./LED_control.o \
./ti_msp_dl_config.o \
./startup_mspm0g350x_ticlang.o \
./frequency_measurement.o \
./other_oscillators.o \
./rc_oscillator.o 

GEN_MISC_FILES += \
./device.cmd.genlibs \
./ti_msp_dl_config.h 

OBJS__QUOTED += \
"LED_control.o" \
"ti_msp_dl_config.o" \
"startup_mspm0g350x_ticlang.o" \
"frequency_measurement.o" \
"other_oscillators.o" \
"rc_oscillator.o" 

GEN_MISC_FILES__QUOTED += \
"device.cmd.genlibs" \
"ti_msp_dl_config.h" 

C_DEPS__QUOTED += \
"LED_control.d" \
"ti_msp_dl_config.d" \
"startup_mspm0g350x_ticlang.d" \
"frequency_measurement.d" \
"other_oscillators.d" \
"rc_oscillator.d" 

GEN_FILES__QUOTED += \
"device_linker.cmd" \
"device.opt" \
"ti_msp_dl_config.c" 

C_SRCS__QUOTED += \
"../LED_control.c" \
"./ti_msp_dl_config.c" \
"/Applications/ti/mspm0_sdk_2_09_00_01/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c" \
"../frequency_measurement.c" \
"../other_oscillators.c" \
"../rc_oscillator.c" 

SYSCFG_SRCS__QUOTED += \
"../empty.syscfg" 


