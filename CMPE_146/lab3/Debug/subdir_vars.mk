################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
SYSCFG_SRCS += \
../empty.syscfg 

C_SRCS += \
../control.c \
../data_corruption.c \
./ti_msp_dl_config.c \
/Applications/ti/mspm0_sdk_2_09_00_01/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c \
../measurement.c \
../simple_checksum.c \
../speedup.c \
../time_management.c 

GEN_CMDS += \
./device_linker.cmd 

GEN_FILES += \
./device_linker.cmd \
./device.opt \
./ti_msp_dl_config.c 

C_DEPS += \
./control.d \
./data_corruption.d \
./ti_msp_dl_config.d \
./startup_mspm0g350x_ticlang.d \
./measurement.d \
./simple_checksum.d \
./speedup.d \
./time_management.d 

GEN_OPTS += \
./device.opt 

OBJS += \
./control.o \
./data_corruption.o \
./ti_msp_dl_config.o \
./startup_mspm0g350x_ticlang.o \
./measurement.o \
./simple_checksum.o \
./speedup.o \
./time_management.o 

GEN_MISC_FILES += \
./device.cmd.genlibs \
./ti_msp_dl_config.h 

OBJS__QUOTED += \
"control.o" \
"data_corruption.o" \
"ti_msp_dl_config.o" \
"startup_mspm0g350x_ticlang.o" \
"measurement.o" \
"simple_checksum.o" \
"speedup.o" \
"time_management.o" 

GEN_MISC_FILES__QUOTED += \
"device.cmd.genlibs" \
"ti_msp_dl_config.h" 

C_DEPS__QUOTED += \
"control.d" \
"data_corruption.d" \
"ti_msp_dl_config.d" \
"startup_mspm0g350x_ticlang.d" \
"measurement.d" \
"simple_checksum.d" \
"speedup.d" \
"time_management.d" 

GEN_FILES__QUOTED += \
"device_linker.cmd" \
"device.opt" \
"ti_msp_dl_config.c" 

C_SRCS__QUOTED += \
"../control.c" \
"../data_corruption.c" \
"./ti_msp_dl_config.c" \
"/Applications/ti/mspm0_sdk_2_09_00_01/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c" \
"../measurement.c" \
"../simple_checksum.c" \
"../speedup.c" \
"../time_management.c" 

SYSCFG_SRCS__QUOTED += \
"../empty.syscfg" 


