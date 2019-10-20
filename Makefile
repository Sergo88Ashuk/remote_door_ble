PROJECT_NAME     := periph_dev_s130
TARGETS          := nrf51822_periph
OUTPUT_DIRECTORY := _build

SDK_ROOT := ../../..
PROJ_DIR := ./periph_dev_cproj

$(OUTPUT_DIRECTORY)/nrf51822_xxaa.out: \
  LINKER_SCRIPT  := periph_dev_gcc_nrf51.ld

# Source files common to all targets
SRC_FILES += \
  $(SDK_ROOT)/components/libraries/util/app_error.c \
  $(SDK_ROOT)/components/libraries/util/app_error_weak.c \
  $(SDK_ROOT)/components/libraries/timer/app_timer.c \
  $(SDK_ROOT)/components/libraries/util/app_util_platform.c \
  $(SDK_ROOT)/components/libraries/hardfault/hardfault_implementation.c \
  $(SDK_ROOT)/components/libraries/util/nrf_assert.c \
  $(SDK_ROOT)/components/libraries/util/sdk_errors.c \
  $(PROJ_DIR)/main.c \
  $(PROJ_DIR)/lvr_drivers/lvrsoc_hw/lvr_gpio/lvr_gpio.c \
  $(PROJ_DIR)/lvr_drivers/lvrsoc_hw/lvr_uart/lvr_uart.c \
  $(PROJ_DIR)/lvr_drivers/lvrsoc_hw/lvr_rtc/lvr_rtc.c \
  $(PROJ_DIR)/lvr_drivers/lvrsoc_hw/lvr_tim/lvr_tim.c \
  $(PROJ_DIR)/lvr_drivers/lvrsoc_hw/lvr_adc/lvr_adc.c \
  $(PROJ_DIR)/lvr_ble/lvr_services/batt_level/lvr_batt.c \
  $(PROJ_DIR)/lvr_ble/lvr_services/alive_wd/lvr_alive.c \
  $(PROJ_DIR)/lvr_ble/lvr_services/gercon_sens/lvr_gercon.c \
  $(PROJ_DIR)/lvr_ble/lvr_services/relay/lvr_relay.c \
  $(PROJ_DIR)/syscalls.c \
  $(PROJ_DIR)/terminal/terminal.c \
  $(PROJ_DIR)/tests/intrpreter_test/intrpreter_test.c \
  $(PROJ_DIR)/lvr_ble/lvr_ble_api.c \
  $(PROJ_DIR)/lvr_ble/lvr_ble_low.c \
  $(PROJ_DIR)/lvr_ble/lvr_errh/lvr_errh.c \
  $(PROJ_DIR)/lvr_ble/lvr_evth/lvr_evth.c \
  $(PROJ_DIR)/app/cmd_line/cmd_line.c \
  $(PROJ_DIR)/app/cmd_line/cmd_line_start.c \
  $(PROJ_DIR)/app/stand_alone/stand_alone.c \
  $(SDK_ROOT)/components/libraries/util/sdk_mapped_flags.c \
  $(SDK_ROOT)/components/toolchain/gcc/gcc_startup_nrf51.S \
  $(SDK_ROOT)/components/toolchain/system_nrf51.c \
  $(SDK_ROOT)/components/ble/common/ble_conn_state.c \
  $(SDK_ROOT)/components/ble/common/ble_conn_params.c \
  $(SDK_ROOT)/components/ble/peer_manager/peer_manager.c \
  $(SDK_ROOT)/components/ble/ble_advertising/ble_advertising.c \
  $(SDK_ROOT)/components/ble/common/ble_srv_common.c \
  $(SDK_ROOT)/components/ble/common/ble_advdata.c \
  #$(SDK_ROOT)/components/softdevice/common/softdevice_handler/softdevice_handler.c \#

# Include folders common to all targets
INC_FOLDERS += \
  $(SDK_ROOT)/components/drivers_nrf/comp \
  $(SDK_ROOT)/components/softdevice/s130/headers \
  $(SDK_ROOT)/components/libraries/log \
  $(SDK_ROOT)/components/libraries/fstorage \
  $(PROJ_DIR) \
  $(PROJ_DIR)/lvr_ble/lvr_services/gercon_sens\
  $(PROJ_DIR)/lvr_ble/lvr_services/prox_sens\
  $(PROJ_DIR)/lvr_ble/lvr_services/relay\
  $(PROJ_DIR)/lvr_drivers/lvrsoc_hw/lvr_adc\
  $(PROJ_DIR)/lvr_drivers/lvrsoc_hw/lvr_gpio\
  $(PROJ_DIR)/lvr_drivers/lvrsoc_hw/lvr_rtc\
  $(PROJ_DIR)/lvr_drivers/lvrsoc_hw/lvr_uart\
  $(PROJ_DIR)/lvr_drivers/lvrsoc_hw/lvr_tim\
  $(PROJ_DIR)/lvr_ble/lvr_services/batt_level\
  $(PROJ_DIR)/lvr_ble/lvr_services/alive_wd\
  $(PROJ_DIR)/lvr_ble/lvr_services/gercon_sens\
  $(PROJ_DIR)/terminal\
  $(PROJ_DIR)/app/cmd_line\
  $(PROJ_DIR)/app/stand_alone\
  $(PROJ_DIR)/tests/intrpreter_test\
  $(PROJ_DIR)/lvr_ble \
  $(PROJ_DIR)/lvr_ble/lvr_errh\
  $(PROJ_DIR)/lvr_ble/lvr_evth\
  $(SDK_ROOT)/components/libraries/gpiote \
  $(SDK_ROOT)/components/boards \
  $(SDK_ROOT)/components/drivers_nrf/common \
  $(SDK_ROOT)/components/ble/ble_advertising \
  $(SDK_ROOT)/components/softdevice/s130/headers/nrf51 \
  $(SDK_ROOT)/components/libraries/queue \
  $(SDK_ROOT)/components/ble/ble_dtm \
  $(SDK_ROOT)/components/toolchain/cmsis/include \
  $(SDK_ROOT)/components/drivers_nrf/wdt \
  $(SDK_ROOT)/components/libraries/bsp \
  $(SDK_ROOT)/components/libraries/experimental_section_vars \
  $(SDK_ROOT)/components/libraries/slip \
  $(SDK_ROOT)/components/libraries/mem_manager \
  $(SDK_ROOT)/external/segger_rtt \
  $(SDK_ROOT)/components/libraries/csense_drv \
  $(SDK_ROOT)/components \
  $(SDK_ROOT)/components/libraries/scheduler \
  $(SDK_ROOT)/components/drivers_nrf/delay \
  $(SDK_ROOT)/components/libraries/crc16 \
  $(SDK_ROOT)/components/libraries/util \
  ./config \
  $(SDK_ROOT)/components/ble/common \
  $(SDK_ROOT)/components/libraries/usbd/class/cdc \
  $(SDK_ROOT)/components/libraries/csense \
  $(SDK_ROOT)/components/drivers_nrf/rng \
  $(SDK_ROOT)/components/libraries/low_power_pwm \
  $(SDK_ROOT)/components/libraries/hardfault \
  $(SDK_ROOT)/components/ble/ble_services/ble_cscs \
  $(SDK_ROOT)/components/libraries/uart \
  $(SDK_ROOT)/components/libraries/hci \
  $(SDK_ROOT)/components/drivers_nrf/spi_slave \
  $(SDK_ROOT)/components/drivers_nrf/lpcomp \
  $(SDK_ROOT)/components/libraries/timer \
  $(SDK_ROOT)/components/drivers_nrf/power \
  $(SDK_ROOT)/components/libraries/usbd/config \
  $(SDK_ROOT)/components/toolchain \
  $(SDK_ROOT)/components/libraries/led_softblink \
  $(SDK_ROOT)/components/drivers_nrf/qdec \
  $(SDK_ROOT)/components/ble/ble_services/ble_cts_c \
  $(SDK_ROOT)/components/drivers_nrf/spi_master \
  $(SDK_ROOT)/components/ble/ble_services/ble_nus \
  $(SDK_ROOT)/components/ble/ble_services/ble_hids \
  $(SDK_ROOT)/components/drivers_nrf/pdm \
  $(SDK_ROOT)/components/libraries/crc32 \
  $(SDK_ROOT)/components/libraries/usbd/class/audio \
  $(SDK_ROOT)/components/ble/peer_manager \
  $(SDK_ROOT)/components/drivers_nrf/swi \
  $(SDK_ROOT)/components/ble/ble_services/ble_tps \
  $(SDK_ROOT)/components/ble/ble_services/ble_dis \
  $(SDK_ROOT)/components/device \
  $(SDK_ROOT)/components/ble/nrf_ble_qwr \
  $(SDK_ROOT)/components/libraries/button \
  $(SDK_ROOT)/components/libraries/usbd \
  $(SDK_ROOT)/components/drivers_nrf/saadc \
  $(SDK_ROOT)/components/ble/ble_services/ble_lbs_c \
  $(SDK_ROOT)/components/ble/ble_racp \
  $(SDK_ROOT)/components/toolchain/gcc \
  $(SDK_ROOT)/components/libraries/fds \
  $(SDK_ROOT)/components/libraries/twi \
  $(SDK_ROOT)/components/drivers_nrf/clock \
  $(SDK_ROOT)/components/ble/ble_services/ble_rscs \
  $(SDK_ROOT)/components/drivers_nrf/usbd \
  $(SDK_ROOT)/components/ble/ble_services/ble_hrs \
  $(SDK_ROOT)/components/libraries/log/src \
  #$(SDK_ROOT)/components/softdevice/common/softdevice_handler \#

# Libraries common to all targets
LIB_FILES += \

# C flags common to all targets
CFLAGS += -DBOARD_CUSTOM
CFLAGS += -DSOFTDEVICE_PRESENT
CFLAGS += -DNRF51
CFLAGS += -DS130
CFLAGS += -DBLE_STACK_SUPPORT_REQD
CFLAGS += -DSWI_DISABLE0
CFLAGS += -DBSP_DEFINES_ONLY
CFLAGS += -DNRF51822
CFLAGS += -DNRF_SD_BLE_API_VERSION=2
CFLAGS += -mcpu=cortex-m0
CFLAGS += -mthumb -mabi=aapcs
CFLAGS +=  -Wall -Werror -O3 -g3
CFLAGS += -mfloat-abi=soft
# keep every function in separate section, this allows linker to discard unused ones
CFLAGS += -ffunction-sections -fdata-sections -fno-strict-aliasing
CFLAGS += -fno-builtin --short-enums 

# C++ flags common to all targets
CXXFLAGS += \

# Assembler flags common to all targets
ASMFLAGS += -x assembler-with-cpp
ASMFLAGS += -DBOARD_CUSTOM
ASMFLAGS += -DSOFTDEVICE_PRESENT
ASMFLAGS += -DNRF51
ASMFLAGS += -DS130
ASMFLAGS += -DBLE_STACK_SUPPORT_REQD
ASMFLAGS += -DSWI_DISABLE0
ASMFLAGS += -DBSP_DEFINES_ONLY
ASMFLAGS += -DNRF51822
ASMFLAGS += -DNRF_SD_BLE_API_VERSION=2

# Linker flags
LDFLAGS += -mthumb -mabi=aapcs -L $(TEMPLATE_PATH) -Tperiph_dev_gcc_nrf51.ld  
LDFLAGS += -mcpu=cortex-m0
# let linker to dump unused sections
LDFLAGS += -Wl,--gc-sections
# use newlib in nano version
LDFLAGS += --specs=nano.specs -lc -lnosys


.PHONY: $(TARGETS) default all clean help flash flash_softdevice listing

# Default target - first one defined
default: nrf51822_periph


# Print all targets that can be built
help:
	@echo following targets are available:
	@echo 	nrf51822_periph

TEMPLATE_PATH := $(SDK_ROOT)/components/toolchain/gcc

include $(TEMPLATE_PATH)/Makefile.common

$(foreach target, $(TARGETS), $(call define_target, $(target)))

listing: $(OUTPUT_DIRECTORY)/nrf51822_periph.out
	@echo Listing: 
	arm-none-eabi-objdump --source --all-headers --demangle --line-numbers --wide "$(OUTPUT_DIRECTORY)/nrf51822_periph.out" > "$(OUTPUT_DIRECTORY)/nrf51822_periph.lst"
	@echo ' '
#interface_mcu.lst: interface_mcu.elf
#	@echo 'Invoking: GNU ARM Cross Create Listing'
#	arm-none-eabi-objdump --source --all-headers --demangle --line-numbers --wide "interface_mcu.elf" > "interface_mcu.lst"
#	@echo 'Finished building: $@'
#	@echo ' '

# Flash the program
flash: $(OUTPUT_DIRECTORY)/nrf51422_xxac.hex
	@echo Flashing: $<
	nrfjprog --program $< -f nrf51 --sectorerase
	nrfjprog --reset -f nrf51

# Flash softdevice
flash_softdevice:
	@echo Flashing: s130_nrf51_2.0.1_softdevice.hex
	nrfjprog --program $(SDK_ROOT)/components/softdevice/s130/hex/s130_nrf51_2.0.1_softdevice.hex -f nrf51 --sectorerase 
	nrfjprog --reset -f nrf51

erase:
	nrfjprog --eraseall -f nrf51
