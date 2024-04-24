export TOPDIR=$(shell echo "$(CURDIR)" | sed -e "s/ /\\\ /g")

MAKE:=$(MAKE) -s --no-print-directory 

$(shell ./scripts/init_version.py)

%.o: %.c
%.ddc: %.c

include .config
include scripts/util.mk

# de-quote some variables we will be using inside this makefile
#CONFIG_BOARD_NAME:=$(patsubst "%",%,$(CONFIG_BOARD_NAME))
#CONFIG_MCU:=$(patsubst "%",%,$(CONFIG_MCU))
#CONFIG_ARM_ARCH:=$(patsubst "%",%,$(CONFIG_ARM_ARCH))
#CONFIG_IMAGE_NAME:=$(patsubst "%",%,$(CONFIG_IMAGE_NAME))

ELF:=$(CONFIG_IMAGE_NAME).elf
BIN:=$(CONFIG_IMAGE_NAME).bin
HEX:=$(CONFIG_IMAGE_NAME).hex

# pull in the board build rules, which will pull in MCU and ARCH build 
# rules too
include board/$(CONFIG_BOARD_NAME)/build_rules.mk

MODULE_DIRS:=kernel\
	     board/$(CONFIG_BOARD_NAME)\
	     mcu/$(CONFIG_MCU)\
	     device\
	     lib


.PHONY: prebuild_autogenerate tags

all: prebuild_autogenerate
	@$(MAKE) $(ELF)

ifeq ($(CONFIG_RAW_BINARY),y)
	@echo "BIN $(BIN)"
	@$(OBJCOPY) -O binary $(ELF) $(BIN)
endif

ifeq ($(CONFIG_INTEL_HEX),y)
	@echo "HEX $(HEX)"
	@$(OBJCOPY) -O ihex $(ELF) $(HEX)
endif


prebuild_autogenerate: include/config.h 
.PHONY: include/config_version.h always_build

include/config.h: .config
	$(call mkconfig, $<, $@, $(CONFIG_BOARD_NAME))

include $(addsuffix /module.def, $(MODULE_DIRS))

$(ELF): always_build
	@$(MAKE) -C arm/$(CONFIG_ARM_ARCH) MODULES="$(MODULE_SRCS:.c=.o)" LINKER_SCRIPT=$(LINKERSCRIPT) TARGET=$@

always_build: $(MODULE_SRCS:.c=.o)

clean: 
	@find . -name "*.ddc" -exec rm {} +
	@find . -name "*.o" -exec rm {} +
	@rm -rf $(ELF)
	@rm -rf $(BIN)
	@rm -rf $(HEX)

menuconfig:
	@kconfig-mconf Kconfig

tags:
	@rm -rf tags
	@find . -name "*.[ch]" -exec ctags --append {} +

