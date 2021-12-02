################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include gecko_sdk_3.2.1/platform/service/udelay/src/subdir.mk
-include gecko_sdk_3.2.1/platform/service/system/src/subdir.mk
-include gecko_sdk_3.2.1/platform/service/sleeptimer/src/subdir.mk
-include gecko_sdk_3.2.1/platform/service/power_manager/src/subdir.mk
-include gecko_sdk_3.2.1/platform/service/hfxo_manager/src/subdir.mk
-include gecko_sdk_3.2.1/platform/service/device_init/src/subdir.mk
-include gecko_sdk_3.2.1/platform/peripheral/src/subdir.mk
-include gecko_sdk_3.2.1/platform/micrium_os/ports/source/gnu/subdir.mk
-include gecko_sdk_3.2.1/platform/micrium_os/ports/source/generic/subdir.mk
-include gecko_sdk_3.2.1/platform/micrium_os/kernel/source/subdir.mk
-include gecko_sdk_3.2.1/platform/micrium_os/cpu/source/subdir.mk
-include gecko_sdk_3.2.1/platform/micrium_os/common/source/rtos/subdir.mk
-include gecko_sdk_3.2.1/platform/micrium_os/common/source/ring_buf/subdir.mk
-include gecko_sdk_3.2.1/platform/micrium_os/common/source/logging/subdir.mk
-include gecko_sdk_3.2.1/platform/micrium_os/common/source/lib/subdir.mk
-include gecko_sdk_3.2.1/platform/micrium_os/common/source/kal/subdir.mk
-include gecko_sdk_3.2.1/platform/emlib/src/subdir.mk
-include gecko_sdk_3.2.1/platform/emdrv/spidrv/src/subdir.mk
-include gecko_sdk_3.2.1/platform/emdrv/dmadrv/src/subdir.mk
-include gecko_sdk_3.2.1/platform/driver/leddrv/src/subdir.mk
-include gecko_sdk_3.2.1/platform/common/toolchain/src/subdir.mk
-include gecko_sdk_3.2.1/platform/common/src/subdir.mk
-include gecko_sdk_3.2.1/platform/Device/SiliconLabs/EFR32FG23/Source/GCC/subdir.mk
-include gecko_sdk_3.2.1/platform/Device/SiliconLabs/EFR32FG23/Source/subdir.mk
-include gecko_sdk_3.2.1/platform/CMSIS/RTOS2/Source/subdir.mk
-include gecko_sdk_3.2.1/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_eusart/subdir.mk
-include gecko_sdk_3.2.1/hardware/board/src/subdir.mk
-include autogen/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: blink_kernel_micriumos_fg23.axf

# Tool invocations
blink_kernel_micriumos_fg23.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -T "C:\Work\NGSA_DEMO\NGSA_FireAngel_Core/autogen/linkerfile.ld" -Xlinker --gc-sections -Xlinker -Map="blink_kernel_micriumos_fg23.map" -mfpu=fpv5-sp-d16 -mfloat-abi=hard --specs=nano.specs -o blink_kernel_micriumos_fg23.axf -Wl,--start-group "./ADC_interrupt.o" "./CODetection.o" "./HeartBeatTests.o" "./HeatDetection.o" "./NGSA_task.o" "./SleepTests.o" "./SmokeDetection.o" "./app.o" "./buzzer.o" "./main.o" "./us_delay_timer.o" "./autogen/sl_board_default_init.o" "./autogen/sl_device_init_clocks.o" "./autogen/sl_emlib_gpio_simple_init.o" "./autogen/sl_event_handler.o" "./autogen/sl_simple_led_instances.o" "./autogen/sl_spidrv_init.o" "./gecko_sdk_3.2.1/hardware/board/src/sl_board_control_gpio.o" "./gecko_sdk_3.2.1/hardware/board/src/sl_board_init.o" "./gecko_sdk_3.2.1/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_eusart/sl_mx25_flash_shutdown.o" "./gecko_sdk_3.2.1/platform/CMSIS/RTOS2/Source/os_systick.o" "./gecko_sdk_3.2.1/platform/Device/SiliconLabs/EFR32FG23/Source/GCC/startup_efr32fg23.o" "./gecko_sdk_3.2.1/platform/Device/SiliconLabs/EFR32FG23/Source/system_efr32fg23.o" "./gecko_sdk_3.2.1/platform/common/src/sl_slist.o" "./gecko_sdk_3.2.1/platform/common/toolchain/src/sl_memory.o" "./gecko_sdk_3.2.1/platform/driver/leddrv/src/sl_led.o" "./gecko_sdk_3.2.1/platform/driver/leddrv/src/sl_simple_led.o" "./gecko_sdk_3.2.1/platform/emdrv/dmadrv/src/dmadrv.o" "./gecko_sdk_3.2.1/platform/emdrv/spidrv/src/spidrv.o" "./gecko_sdk_3.2.1/platform/emlib/src/em_assert.o" "./gecko_sdk_3.2.1/platform/emlib/src/em_burtc.o" "./gecko_sdk_3.2.1/platform/emlib/src/em_cmu.o" "./gecko_sdk_3.2.1/platform/emlib/src/em_core.o" "./gecko_sdk_3.2.1/platform/emlib/src/em_emu.o" "./gecko_sdk_3.2.1/platform/emlib/src/em_eusart.o" "./gecko_sdk_3.2.1/platform/emlib/src/em_gpio.o" "./gecko_sdk_3.2.1/platform/emlib/src/em_iadc.o" "./gecko_sdk_3.2.1/platform/emlib/src/em_ldma.o" "./gecko_sdk_3.2.1/platform/emlib/src/em_system.o" "./gecko_sdk_3.2.1/platform/emlib/src/em_timer.o" "./gecko_sdk_3.2.1/platform/emlib/src/em_usart.o" "./gecko_sdk_3.2.1/platform/micrium_os/common/source/kal/kal_kernel.o" "./gecko_sdk_3.2.1/platform/micrium_os/common/source/lib/lib_ascii.o" "./gecko_sdk_3.2.1/platform/micrium_os/common/source/lib/lib_mem.o" "./gecko_sdk_3.2.1/platform/micrium_os/common/source/lib/lib_str.o" "./gecko_sdk_3.2.1/platform/micrium_os/common/source/logging/logging.o" "./gecko_sdk_3.2.1/platform/micrium_os/common/source/ring_buf/ring_buf.o" "./gecko_sdk_3.2.1/platform/micrium_os/common/source/rtos/rtos_err_str.o" "./gecko_sdk_3.2.1/platform/micrium_os/common/source/rtos/rtos_utils.o" "./gecko_sdk_3.2.1/platform/micrium_os/cpu/source/cpu_core.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/cmsis_os2.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_cfg_app.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_core.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_dbg.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_flag.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_mon.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_msg.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_mutex.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_prio.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_q.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_sem.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_stat.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_task.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_time.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_tmr.o" "./gecko_sdk_3.2.1/platform/micrium_os/kernel/source/os_var.o" "./gecko_sdk_3.2.1/platform/micrium_os/ports/source/generic/arm_cpu_dwt_ts.o" "./gecko_sdk_3.2.1/platform/micrium_os/ports/source/gnu/armv7m_cpu_c.o" "./gecko_sdk_3.2.1/platform/micrium_os/ports/source/gnu/armv7m_os_cpu_c.o" "./gecko_sdk_3.2.1/platform/micrium_os/ports/source/gnu/armv8m_cpu_a.o" "./gecko_sdk_3.2.1/platform/micrium_os/ports/source/gnu/armv8m_os_cpu_a.o" "./gecko_sdk_3.2.1/platform/peripheral/src/peripheral_sysrtc.o" "./gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_dcdc_s2.o" "./gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_emu_s2.o" "./gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_hfxo_s2.o" "./gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_lfxo_s2.o" "./gecko_sdk_3.2.1/platform/service/device_init/src/sl_device_init_nvic.o" "./gecko_sdk_3.2.1/platform/service/hfxo_manager/src/sl_hfxo_manager.o" "./gecko_sdk_3.2.1/platform/service/hfxo_manager/src/sl_hfxo_manager_hal_s2.o" "./gecko_sdk_3.2.1/platform/service/power_manager/src/sl_power_manager.o" "./gecko_sdk_3.2.1/platform/service/power_manager/src/sl_power_manager_debug.o" "./gecko_sdk_3.2.1/platform/service/power_manager/src/sl_power_manager_hal_s2.o" "./gecko_sdk_3.2.1/platform/service/sleeptimer/src/sl_sleeptimer.o" "./gecko_sdk_3.2.1/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.o" "./gecko_sdk_3.2.1/platform/service/sleeptimer/src/sl_sleeptimer_hal_sysrtc.o" "./gecko_sdk_3.2.1/platform/service/system/src/sl_system_init.o" "./gecko_sdk_3.2.1/platform/service/system/src/sl_system_kernel.o" "./gecko_sdk_3.2.1/platform/service/udelay/src/sl_udelay.o" "./gecko_sdk_3.2.1/platform/service/udelay/src/sl_udelay_armv6m_gcc.o" -lgcc -lc -lm -lnosys -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: blink_kernel_micriumos_fg23.hex'
	arm-none-eabi-objcopy -O ihex "blink_kernel_micriumos_fg23.axf" "blink_kernel_micriumos_fg23.hex"
	@echo ' '

	@echo 'Building bin file: blink_kernel_micriumos_fg23.bin'
	arm-none-eabi-objcopy -O binary "blink_kernel_micriumos_fg23.axf" "blink_kernel_micriumos_fg23.bin"
	@echo ' '

	@echo 'Building s37 file: blink_kernel_micriumos_fg23.s37'
	arm-none-eabi-objcopy -O srec "blink_kernel_micriumos_fg23.axf" "blink_kernel_micriumos_fg23.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "blink_kernel_micriumos_fg23.axf" -A
	@echo ' '

# Other Targets
clean:
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) blink_kernel_micriumos_fg23.axf
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
