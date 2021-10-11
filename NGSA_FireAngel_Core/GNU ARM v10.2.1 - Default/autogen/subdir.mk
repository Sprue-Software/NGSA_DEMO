################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../autogen/sl_board_default_init.c \
../autogen/sl_device_init_clocks.c \
../autogen/sl_emlib_gpio_simple_init.c \
../autogen/sl_event_handler.c \
../autogen/sl_simple_led_instances.c \
../autogen/sl_spidrv_init.c 

OBJS += \
./autogen/sl_board_default_init.o \
./autogen/sl_device_init_clocks.o \
./autogen/sl_emlib_gpio_simple_init.o \
./autogen/sl_event_handler.o \
./autogen/sl_simple_led_instances.o \
./autogen/sl_spidrv_init.o 

C_DEPS += \
./autogen/sl_board_default_init.d \
./autogen/sl_device_init_clocks.d \
./autogen/sl_emlib_gpio_simple_init.d \
./autogen/sl_event_handler.d \
./autogen/sl_simple_led_instances.d \
./autogen/sl_spidrv_init.d 


# Each subdirectory must supply rules for building sources it contributes
autogen/sl_board_default_init.o: ../autogen/sl_board_default_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFR32FG23B010F512IM48=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/Device/SiliconLabs/EFR32FG23/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//hardware/board/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/CMSIS/RTOS2/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/device_init/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/dmadrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emlib/init/gpio_simple" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/hfxo_manager/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/driver/leddrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/common/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/common/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/cpu/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/ports/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/kernel/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/kernel/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_eusart" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/peripheral/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/power_manager/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/driver/pwm/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/common/toolchain/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/system/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/sleeptimer/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/spidrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/udelay/inc" -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC\autogen" -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC\config" -Os -Wall -Wextra -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_board_default_init.d" -MT"autogen/sl_board_default_init.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_device_init_clocks.o: ../autogen/sl_device_init_clocks.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFR32FG23B010F512IM48=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/Device/SiliconLabs/EFR32FG23/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//hardware/board/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/CMSIS/RTOS2/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/device_init/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/dmadrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emlib/init/gpio_simple" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/hfxo_manager/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/driver/leddrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/common/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/common/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/cpu/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/ports/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/kernel/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/kernel/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_eusart" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/peripheral/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/power_manager/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/driver/pwm/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/common/toolchain/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/system/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/sleeptimer/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/spidrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/udelay/inc" -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC\autogen" -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC\config" -Os -Wall -Wextra -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_device_init_clocks.d" -MT"autogen/sl_device_init_clocks.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_emlib_gpio_simple_init.o: ../autogen/sl_emlib_gpio_simple_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFR32FG23B010F512IM48=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/Device/SiliconLabs/EFR32FG23/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//hardware/board/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/CMSIS/RTOS2/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/device_init/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/dmadrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emlib/init/gpio_simple" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/hfxo_manager/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/driver/leddrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/common/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/common/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/cpu/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/ports/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/kernel/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/kernel/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_eusart" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/peripheral/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/power_manager/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/driver/pwm/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/common/toolchain/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/system/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/sleeptimer/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/spidrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/udelay/inc" -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC\autogen" -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC\config" -Os -Wall -Wextra -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_emlib_gpio_simple_init.d" -MT"autogen/sl_emlib_gpio_simple_init.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_event_handler.o: ../autogen/sl_event_handler.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFR32FG23B010F512IM48=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/Device/SiliconLabs/EFR32FG23/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//hardware/board/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/CMSIS/RTOS2/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/device_init/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/dmadrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emlib/init/gpio_simple" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/hfxo_manager/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/driver/leddrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/common/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/common/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/cpu/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/ports/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/kernel/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/kernel/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_eusart" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/peripheral/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/power_manager/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/driver/pwm/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/common/toolchain/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/system/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/sleeptimer/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/spidrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/udelay/inc" -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC\autogen" -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC\config" -Os -Wall -Wextra -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_event_handler.d" -MT"autogen/sl_event_handler.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_simple_led_instances.o: ../autogen/sl_simple_led_instances.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFR32FG23B010F512IM48=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/Device/SiliconLabs/EFR32FG23/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//hardware/board/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/CMSIS/RTOS2/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/device_init/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/dmadrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emlib/init/gpio_simple" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/hfxo_manager/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/driver/leddrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/common/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/common/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/cpu/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/ports/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/kernel/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/kernel/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_eusart" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/peripheral/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/power_manager/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/driver/pwm/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/common/toolchain/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/system/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/sleeptimer/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/spidrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/udelay/inc" -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC\autogen" -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC\config" -Os -Wall -Wextra -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_simple_led_instances.d" -MT"autogen/sl_simple_led_instances.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

autogen/sl_spidrv_init.o: ../autogen/sl_spidrv_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DDEBUG_EFM=1' '-DEFR32FG23B010F512IM48=1' '-DSL_COMPONENT_CATALOG_PRESENT=1' -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/Device/SiliconLabs/EFR32FG23/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//hardware/board/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/CMSIS/RTOS2/Include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/device_init/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/dmadrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/common/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emlib/init/gpio_simple" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/hfxo_manager/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/driver/leddrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/common/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/common/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/cpu/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/ports/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/kernel/source" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/micrium_os/kernel/include" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_eusart" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/peripheral/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/power_manager/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/driver/pwm/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/common/toolchain/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/system/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/sleeptimer/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/emdrv/spidrv/inc" -I"C:/SiliconLabs/SimplicityStudio/v5_3/developer/sdks/gecko_sdk_suite/v3.2//platform/service/udelay/inc" -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC\autogen" -I"C:\Users\ndiwathe\SimplicityStudio\v5_workspace1\NGSA_FireAngel_Core_ADC\config" -Os -Wall -Wextra -fno-builtin -ffunction-sections -fdata-sections -imacrossl_gcc_preinclude.h -mfpu=fpv5-sp-d16 -mfloat-abi=hard -c -fmessage-length=0 -MMD -MP -MF"autogen/sl_spidrv_init.d" -MT"autogen/sl_spidrv_init.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


