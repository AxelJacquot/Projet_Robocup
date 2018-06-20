################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/CAN.c" \
"../Sources/Events.c" \
"../Sources/RF.c" \
"../Sources/SPI_RF.c" \
"../Sources/UART.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/CAN.c \
../Sources/Events.c \
../Sources/RF.c \
../Sources/SPI_RF.c \
../Sources/UART.c \
../Sources/main.c \

OBJS += \
./Sources/CAN_c.obj \
./Sources/Events_c.obj \
./Sources/RF_c.obj \
./Sources/SPI_RF_c.obj \
./Sources/UART_c.obj \
./Sources/main_c.obj \

OBJS_QUOTED += \
"./Sources/CAN_c.obj" \
"./Sources/Events_c.obj" \
"./Sources/RF_c.obj" \
"./Sources/SPI_RF_c.obj" \
"./Sources/UART_c.obj" \
"./Sources/main_c.obj" \

C_DEPS += \
./Sources/CAN_c.d \
./Sources/Events_c.d \
./Sources/RF_c.d \
./Sources/SPI_RF_c.d \
./Sources/UART_c.d \
./Sources/main_c.d \

C_DEPS_QUOTED += \
"./Sources/CAN_c.d" \
"./Sources/Events_c.d" \
"./Sources/RF_c.d" \
"./Sources/SPI_RF_c.d" \
"./Sources/UART_c.d" \
"./Sources/main_c.d" \

OBJS_OS_FORMAT += \
./Sources/CAN_c.obj \
./Sources/Events_c.obj \
./Sources/RF_c.obj \
./Sources/SPI_RF_c.obj \
./Sources/UART_c.obj \
./Sources/main_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/CAN_c.obj: ../Sources/CAN.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/CAN.args" -ObjN="Sources/CAN_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/Events_c.obj: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/Events.args" -ObjN="Sources/Events_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/RF_c.obj: ../Sources/RF.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/RF.args" -ObjN="Sources/RF_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/SPI_RF_c.obj: ../Sources/SPI_RF.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SPI_RF.args" -ObjN="Sources/SPI_RF_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/UART_c.obj: ../Sources/UART.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/UART.args" -ObjN="Sources/UART_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


