
# mcu level build rules pull in the architecture specific build rules
# and also add MCU level defines or compiler flags to the build
include arm/$(CONFIG_ARM_ARCH)/build_rules.mk

ifeq ($(CONFIG_GD32F450),y)
CFLAGS+=-DGD32F450
else ifeq ($(CONFIG_GD32F405),y)
CFLAGS+=-DGD32F405
else ifeq ($(CONFIG_GD32F407),y)
CFLAGS+=-DGD32F407
else ifeq ($(CONFIG_GD32F470),y)
CFLAGS+=-DGD32F470
else ifeq ($(CONFIG_GD32F425),y)
CFLAGS+=-DGD32F425
else ifeq ($(CONFIG_GD32F427),y)
CFLAGS+=-DGD32427
endif

CFLAGS+=-Imcu/$(CONFIG_MCU)/include
CFLAGS+=-Imcu/$(CONFIG_MCU)/include/device
CFLAGS+=-Iinclude/CMSIS

CFLAGS+=-DUSE_STDPERIPH_DRIVER
CFLAGS+=-DHXTAL_VALUE=$(CONFIG_HXTAL_VALUE) -DHXTAL_STARTUP_TIMEOUT=$(CONFIG_HXTAL_STARTUP_TIMEOUT) -DIRC16M_VALUE=$(CONFIG_IRC16M_VALUE)

ifeq ($(CONFIG_IRC16M),y)
CFLAGS+=-D__SYSTEM_CLOCK_IRC16M=$(CONFIG_IRC16M_VALUE)
else ifeq ($(CONFIG_HXTAL),y)
CFLAGS+=-D__SYSTEM_CLOCK_IRC16M=$(CONFIG_IRC16M_VALUE)

else ifeq ($(CONFIG_120M_PLL_ICR16M),y)
CFLAGS+=-D__SYSTEM_CLOCK_120M_PLL_IRC16M=$(CONFIG_SYSTEM_CLOCK_VALUE)
else ifeq ($(CONFIG_120M_PLL_8M_HXTAL),y)
CFLAGS+=-D__SYSTEM_CLOCK_120M_PLL_8M_HXTAL=$(CONFIG_SYSTEM_CLOCK_VALUE)
else ifeq ($(CONFIG_120M_PLL_25M_HXTAL),y)
CFLAGS+=-D__SYSTEM_CLOCK_120M_PLL_25M_HXTAL=$(CONFIG_SYSTEM_CLOCK_VALUE)

else ifeq ($(CONFIG_168M_PLL_ICR16M),y)
CFLAGS+=-D__SYSTEM_CLOCK_168M_PLL_IRC16M=$(CONFIG_SYSTEM_CLOCK_VALUE)
else ifeq ($(CONFIG_168M_PLL_8M_HXTAL),y)
CFLAGS+=-D__SYSTEM_CLOCK_168M_PLL_8M_HXTAL=$(CONFIG_SYSTEM_CLOCK_VALUE)
else ifeq ($(CONFIG_168M_PLL_25M_HXTAL),y)
CFLAGS+=-D__SYSTEM_CLOCK_168M_PLL_25M_HXTAL=$(CONFIG_SYSTEM_CLOCK_VALUE)

else ifeq ($(CONFIG_200M_PLL_ICR16M),y)
CFLAGS+=-D__SYSTEM_CLOCK_200M_PLL_IRC16M=$(CONFIG_SYSTEM_CLOCK_VALUE)
else ifeq ($(CONFIG_200M_PLL_8M_HXTAL),y)
CFLAGS+=-D__SYSTEM_CLOCK_200M_PLL_8M_HXTAL=$(CONFIG_SYSTEM_CLOCK_VALUE)
else ifeq ($(CONFIG_200M_PLL_25M_HXTAL),y)
CFLAGS+=-D__SYSTEM_CLOCK_200M_PLL_25M_HXTAL=$(CONFIG_SYSTEM_CLOCK_VALUE)

else ifeq ($(CONFIG_240M_PLL_ICR16M),y)
CFLAGS+=-D__SYSTEM_CLOCK_240M_PLL_IRC16M=$(CONFIG_SYSTEM_CLOCK_VALUE)
else ifeq ($(CONFIG_240M_PLL_8M_HXTAL),y)
CFLAGS+=-D__SYSTEM_CLOCK_240M_PLL_8M_HXTAL=$(CONFIG_SYSTEM_CLOCK_VALUE)
else ifeq ($(CONFIG_240M_PLL_25M_HXTAL),y)
CFLAGS+=-D__SYSTEM_CLOCK_240M_PLL_25M_HXTAL=$(CONFIG_SYSTEM_CLOCK_VALUE)

endif

