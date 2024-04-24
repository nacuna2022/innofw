
# board-level build rules is where we choose the MCU to include
# and we also add board level compiler flags and/or defines here.

include mcu/$(CONFIG_MCU)/build_rules.mk

CFLAGS+=-Iboard/$(CONFIG_BOARD_NAME)/include/

LINKERSCRIPT=board/$(CONFIG_BOARD_NAME)/linkerscript.ld

